// temp_functions.c

#include <stdlib.h>
#include "temp_functions.h"

//=======================================================
// === Вспомогательные функции ===                      |
//=======================================================

// Инициализация массива статистики по месяцам
// Приводит 12 элементов (январь..декабрь) в "нулевое" начальное состояние:
// - month = 1..12 (номер месяца)
// - count = 0 (пока нет записей)
// - avg_temp = 0.0 (сумма температур = 0, деление будет позже)
// - min_temp = максимально возможное значение (чтобы любая реальная температура была меньше)
// - max_temp = минимально возможное значение (чтобы любая реальная температура была больше)
static void init_monthly_stats(monthly_stats *stats)
{
    for (int m = 0; m < 12; m++)
    {
        stats[m].month = (uint8_t)(m + 1); // январь = 1, февраль = 2, ..., декабрь = 12
        stats[m].count = 0;                // счётчик записей — пока 0
        stats[m].avg_temp = 0.0;           // накопительная сумма температур (среднее = сумма / count)
        stats[m].min_temp = INT8_MAX;      // +127 — любая реальная t ([-99;+99]) будет меньше
        stats[m].max_temp = INT8_MIN;      // -128 — любая реальная t будет больше
    }
}

// Основная функция сбора помесячной статистики за указанный год
// Вход:
//   data       — указатель на структуру с сырыми данными
//   year       — год, за который нужно собрать статистику
//   good_stats — массив из 12 элементов monthly_stats (выход: статистика по корректным записям)
//   bad_count  — массив из 12 uint32_t (выход: количество испорченных записей по месяцам)
// Работает за один проход по данным
static void compute_monthly_stats(const sensor_data *data, uint16_t year,
                                  monthly_stats *good_stats, uint32_t *bad_count)
{
    // Шаг 1: инициализация выходных массивов
    init_monthly_stats(good_stats);              // обнулить good_stats
    memset(bad_count, 0, 12 * sizeof(uint32_t)); // обнулить bad_count (12 нулей)

    // Шаг 2: проход по всем записям в файле
    for (uint32_t i = 0; i < data->number; i++)
    {
        const sensor *r = &data->info[i]; // текущая запись

        // Пропускаем записи не за запрошенный год
        if (r->year != year)
            continue;

        // Пропускаем записи с некорректным месяцем (должен быть 1..12)
        if (r->month < 1 || r->month > 12)
            continue;

        // Определяем индекс месяца в массивах (0 = январь, 11 = декабрь)
        int idx = r->month - 1;

        // Если запись помечена как испорченная (is_valid != 0) — увеличиваем счётчик плохих
        if (r->is_valid != 0)
        {
            bad_count[idx]++;
            continue; // и пропускаем дальнейшую обработку
        }

        // --- Обработка КОРРЕКТНОЙ записи ---
        // 1. Увеличиваем счётчик записей за месяц
        good_stats[idx].count++;

        // 2. Добавляем температуру к накопительной сумме (среднее посчитаем позже)
        good_stats[idx].avg_temp += (double)r->t;

        // 3. Обновляем минимум и максимум для этого месяца
        if (r->t < good_stats[idx].min_temp)
            good_stats[idx].min_temp = r->t;
        if (r->t > good_stats[idx].max_temp)
            good_stats[idx].max_temp = r->t;
    }

    // Шаг 3: завершаем расчёт средних температур по месяцам
    // (деление суммы на количество записей, но только если записей > 0)
    for (int m = 0; m < 12; m++)
    {
        if (good_stats[m].count > 0)
        {
            good_stats[m].avg_temp /= good_stats[m].count;
        }
        // Если записей нет — avg_temp остаётся 0.0, но при выводе покажется как N/A
    }
}


// Функция расчёта общей годовой статистики на основе помесячных данных
// Вход:
//   months — массив из 12 monthly_stats (уже заполнен)
//   ystat  — указатель на структуру для результата (заполняется функцией)
//   year   — год (копируется в результат)
// Расчёт:
//   - общее количество корректных записей = сумма count по месяцам
//   - средняя температура за год = (сумма всех средних * кол-во) / общее кол-во
//   - минимум/максимум за год = мин/макс по всем месяцам (только по месяцам с данными)
static void compute_yearly_stats(const monthly_stats *months, yearly_stats *ystat, uint16_t year)
{
    // Инициализация структуры результата
    ystat->year = year;
    ystat->count = 0;
    ystat->avg_temp = 0.0;
    ystat->min_temp = INT8_MAX; // начальное значение для поиска минимума
    ystat->max_temp = INT8_MIN; // начальное значение для поиска максимума

    double total_sum = 0.0;  // накопительная сумма (среднее_месяца * кол-во_в_месяце)
    uint32_t total_good = 0; // общее количество корректных записей за год

    // Проход по всем 12 месяцам
    for (int m = 0; m < 12; m++)
    {
        // Накапливаем общее количество и взвешенную сумму температур
        total_good += months[m].count;
        total_sum += months[m].avg_temp * months[m].count;

        // Обновляем глобальные минимум и максимум, но только если в месяце есть данные
        if (months[m].count > 0)
        {
            if (months[m].min_temp < ystat->min_temp)
                ystat->min_temp = months[m].min_temp;
            if (months[m].max_temp > ystat->max_temp)
                ystat->max_temp = months[m].max_temp;
        }
    }

    // Сохраняем общее количество корректных записей
    ystat->count = total_good;

    // Рассчитываем среднюю температуру за год (только если есть данные)
    if (total_good > 0)
    {
        ystat->avg_temp = total_sum / total_good;
    }
    // Если записей нет — avg_temp остаётся 0.0 (но функция вызывающая проверит count == 0)
}

// Функция вывода одной строки таблицы помесячной статистики
// Соответствует формату:
//   №   Год    Месяц  КолЗап  ПлохЗап  СрдТемп  МинТемп  МаксТемп
// Пример: 1   2021   01     3        1        -44.67   -47      -43
static void print_monthly_row(uint32_t row_num, uint16_t year, const monthly_stats *mstat, uint32_t bad)
{
    // Столбец 1: номер строки в таблице (1..12)
    printf("%u", row_num);

    // Столбец 2: год (с ведущими нулями до 4 цифр)
    printf("\t%04u", year);

    // Столбец 3: месяц (с ведущим нулём, 01..12)
    printf("\t%02u", mstat->month);

    // Столбец 4: количество КОРРЕКТНЫХ записей за месяц
    printf("\t%u", mstat->count);

    // Столбец 5: количество ИСПОРЧЕННЫХ записей за месяц (из bad_count)
    printf("\t%u", bad);

    // Столбцы 6-8: температурные показатели
    if (mstat->count > 0)
    {
        // Если есть корректные записи — выводим числа
        printf("\t%.2f", mstat->avg_temp); // средняя с 2 знаками после запятой
        printf("\t%+d", mstat->min_temp);  // %+d даёт знак: +5, -10
        printf("\t%+d", mstat->max_temp);
    }
    else
    {
        // Если записей нет — выводим N/A (Not Available)
        printf("\tN/A\tN/A\tN/A");
    }

    // Завершаем строку
    printf("\n");
}

// Функция сравнение двух времён Возвращает: -1 — t1 < t2, 0 — t1 == t2, +1 — t1 > t2
static int compare_time(const sensor *t1, const sensor *t2)
{
    if (t1->year != t2->year)
        return (t1->year < t2->year) ? -1 : +1;
    if (t1->month != t2->month)
        return (t1->month < t2->month) ? -1 : +1;
    if (t1->day != t2->day)
        return (t1->day < t2->day) ? -1 : +1;
    if (t1->hour != t2->hour)
        return (t1->hour < t2->hour) ? -1 : +1;
    if (t1->minute != t2->minute)
        return (t1->minute < t2->minute) ? -1 : +1;
    return 0; // равны
}

//=======================================================
//  === Функции работы с файлами ===                    |
//=======================================================

// Функция безопасного открытия файла
FILE *safe_fopen(const char *path, const char *mode)
{
    FILE *f = fopen(path, mode);
    if (!f)
    {
        fprintf(stderr, "Ошибка открытия файла '%s' в режиме '%s': ", path, mode);
        perror("");
    }
    return f;
}

// Функция чтения данных из файла
int load_data_from_file(sensor_data *d, const char *filename)
{
    if (!d || !filename)
        return -1;

    FILE *f = safe_fopen(filename, "r");
    if (!f)
        return -2;

    d->number = 0;
    char line[256];
    sensor prev_record = {0}; // для хранения предыдущей корректной записи

    while (fgets(line, sizeof(line), f) != NULL && d->number < MAX_RECORDS)
    {
        line[strcspn(line, "\r\n")] = '\0';

        sensor *cur = &d->info[d->number];
        memset(cur, 0, sizeof(sensor));
        cur->is_valid = 1; // по умолчанию — плохая

        int y, mo, d_, h, m, t;
        int n = sscanf(line, "%d;%d;%d;%d;%d;%d", &y, &mo, &d_, &h, &m, &t);

        // Сохраняем ВСЁ, что удалось прочитать
        if (n >= 1 && y >= 0 && y <= 65535)
            cur->year = (uint16_t)y;
        if (n >= 2 && mo >= 1 && mo <= 12)
            cur->month = (uint8_t)mo;
        if (n >= 3 && d_ >= 1 && d_ <= 31)
            cur->day = (uint8_t)d_;
        if (n >= 4 && h >= 0 && h <= 23)
            cur->hour = (uint8_t)h;
        if (n >= 5 && m >= 0 && m <= 59)
            cur->minute = (uint8_t)m;
        if (n >= 6 && t >= -99 && t <= 99)
            cur->t = (int8_t)t;

        // Проверка 1: все 6 полей корректны?
        int all_fields_valid = (n == 6 &&
                                y >= 0 && y <= 65535 &&
                                mo >= 1 && mo <= 12 &&
                                d_ >= 1 && d_ <= 31 &&
                                h >= 0 && h <= 23 &&
                                m >= 0 && m <= 59 &&
                                t >= -99 && t <= 99);

        if (all_fields_valid)
        {
            // Проверка 2: время строго больше предыдущей корректной записи
            if (d->number == 0)
            {
                // Первая запись — принимаем, если поля валидны
                cur->is_valid = 0;
                prev_record = *cur; // сохраняем для следующей итерации
            }
            else
            {
                // Сравниваем с предыдущей КОРРЕКТНОЙ записью
                int cmp = compare_time(&prev_record, cur);
                if (cmp < 0)
                { // cur > prev_record → OK
                    cur->is_valid = 0;
                    prev_record = *cur; // обновляем "последнюю корректную"
                }
                // иначе: cur <= prev_record → остаётся is_valid = 1
            }
        }
        // Если not all_fields_valid — is_valid остаётся 1

        d->number++;
    }

    fclose(f);
    if (d->number == 0)
        return -3;

    // Проверяем, есть ли хотя бы одна корректная запись
    for (uint32_t i = 0; i < d->number; i++)
    {
        if (d->info[i].is_valid == 0)
        {
            return 0;
        }
    }

    return -4;
}

//=======================================================
// === Функции  статистики ===                          |
//=======================================================

// Функция вывода статистики за месяц года

int print_monthly_stats(const sensor_data *data, uint16_t year, uint8_t month)
{
    if (!data)
    {
        fprintf(stderr, "Ошибка: ошибка данных (NULL)\n");
        return -1;
    }

    if (data->number == 0)
    {
        fprintf(stderr, "Ошибка: пустой набор данных\n");
        return -1;
    }

    // Сбор статистики по месяцам
    monthly_stats good_stats[12];
    uint32_t bad_count[12];
    compute_monthly_stats(data, year, good_stats, bad_count);

    const monthly_stats *mstat = &good_stats[month - 1];
    uint32_t bad = bad_count[month - 1];

    // Выводим информацию о пропущенных записях
    if (bad > 0)
    {
        printf("Внимание: пропущено %u испорченных записей за %04u-%02u\n", bad, year, month);
    }

    // Проверка: есть ли корректные данные за месяц
    if (mstat->count == 0)
    {
        printf("\n[Статистика за %04d-%02d]\n", year, month);

        return -2;
    }

    // === Вывод в формате таблицы (как в годовой статистике) ===
    printf("#\tГод\tМесяц\tКолЗап\tПлохЗап\tСрдТемп\tМинТемп\tМаксТемп\n");
    print_monthly_row(1, year, mstat, bad);

    return 0;
}

// Функция вывода статистики за год

int print_yearly_stats(const sensor_data *data, uint16_t year)
{
    if (!data)
    {
        fprintf(stderr, "Ошибка: данные NULL\n");
        return -1;
    }
    if (data->number == 0)
    {
        fprintf(stderr, "Ошибка: пустой набор данных\n");
        return -1;
    }

    // Сбор статистики
    monthly_stats good_stats[12];
    uint32_t bad_count[12];
    compute_monthly_stats(data, year, good_stats, bad_count);

    // Годовая статистика
    yearly_stats ystat;
    compute_yearly_stats(good_stats, &ystat, year);

    if (ystat.count == 0)
    {
        // printf("Нет корректных данных за указанный год.\n");
        return -2;
    }
    else
    {
        // Таблица
        printf("#\tГод\tМесяц\tКолЗап\tПлохЗап\tСрдТемп\tМинТемп\tМаксТемп\n");
        for (int m = 0; m < 12; m++)
        {
            print_monthly_row((uint32_t)(m + 1), year, &good_stats[m], bad_count[m]);
        }
    }
    // === Подсчёт ОБЩЕГО числа испорченных записей во всём файле ===
    uint32_t total_bad = 0;
    for (int m = 0; m < 12; m++)
        total_bad += bad_count[m];

    printf("\n[Годовая статистика за %04u]\n", ystat.year);
    printf("Обработано корректных записей: %u\n", ystat.count);

    // Выводим информацию о пропущенных записях
    if (total_bad > 0)
    {
        printf("Внимание: пропущено %u испорченных записей за %04u год\n", total_bad, year);
    }

    if (ystat.count != ystat.count + total_bad)
    {
        printf("Всего записей за год: %u\n", ystat.count + total_bad);
    }

    // Безопасный расчёт амплитуды температуры
    int16_t amplitude = (int16_t)ystat.max_temp - (int16_t)ystat.min_temp;

    printf("Средняя температура за год: %+.2f\n", ystat.avg_temp);
    printf("Минимальная температура за год: %+d\n", ystat.min_temp);
    printf("Максимальная температура за год: %+d\n", ystat.max_temp);
    printf("Амплитуда температур за год: %+d\n", (int)amplitude);

    return 0;
}

//=======================================================
// === Дополнительные функции ===                       |
//=======================================================

// функция печати "хелпа"
void print_help()
{
    printf("======================================================================\n");
    printf("Применение: sensor_app.exe [ключ]...\n");
    printf("Ключи:\n");
    printf("  -h        этот хэлп\n");
    printf("  -f        название файла, из которого берутся данные с датчика для анализа\n");
    printf("  -y        год, за который производится статистика\n");
    printf("            если вводится YY [0-100], то автоматически формируется год 20 + введенное число\n");
    printf("            если вводится YYYY [2000-2100], то используется введенное число\n");
    printf("            если не указан год, то по умолчанию 2021\n");
    printf("  -m        месяц, за который производится статистика\n");
    printf("            Если месяц не указан, то статистика приводится завесь указаный год\n");
    printf("            Если указан, то приводится статистика за указанный месяц указанного года\n");
    printf("  -?        Если указан неизвестный ключ, то программа выводит хелп и завершается\n");
    printf("\n");
    printf("Эта программа собрана в GNU Make 3.81\n");
    printf("О всех ошибках и сбоях сообщить на <010302@rambler.ru>\n");
    printf("======================================================================\n");
}
