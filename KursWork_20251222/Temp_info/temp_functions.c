// temp_functions.c

#include <stdlib.h>
#include "temp_functions.h"

#define MAX_RECORDS 650000

// === Функции работы с файлами ===

// Функция safe_fopen - это "безопасная" обертка над стандартной функцией fopen из языка C
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

// функция чтения из файла
int load_data_from_file(sensor_data *d, const char *filename)
{
    if (!d || !filename)
        return -1;

    FILE *f = safe_fopen(filename, "r");
    if (!f)
        return -2;

    d->number = 0;

    char line[256];

    while (fgets(line, sizeof(line), f) != NULL && d->number < MAX_RECORDS)
    {
        // Инициализируем запись как испорченную по умолчанию
        sensor *current = &d->info[d->number];
        memset(current, 0, sizeof(sensor));
        current->is_valid = 1; // По умолчанию считаем испорченной

        // Пытаемся распарсить строку
        int year, month, day, hour, minute, t;
        int result = sscanf(line, "%d; %d; %d; %d; %d; %d",
                            &year, &month, &day, &hour, &minute, &t);

        if (result == 6)
        {
            // Проверяем корректность диапазонов
            if (year >= 0 && year <= 65535 &&
                month >= 1 && month <= 12 &&
                day >= 1 && day <= 31 &&
                hour >= 0 && hour <= 23 &&
                minute >= 0 && minute <= 59 &&
                t >= -99 && t <= 99)
            {
                // Все корректно - сохраняем данные
                current->year = (uint16_t)year;
                current->month = (uint8_t)month;
                current->day = (uint8_t)day;
                current->hour = (uint8_t)hour;
                current->minute = (uint8_t)minute;
                current->t = (int8_t)t;
                current->is_valid = 0; // Отмечаем как корректную
            }
            // Если диапазоны неверны, запись останется помеченной как испорченная
        }
        // Если sscanf не вернул 6, запись останется помеченной как испорченная

        d->number++;
    }

    fclose(f);

    if (d->number == 0)
        return -3; // Файл пуст

    // Проверяем, есть ли хотя бы одна корректная запись
    int has_valid = 0;
    for (uint32_t i = 0; i < d->number; i++)
    {
        if (d->info[i].is_valid == 0)
        {
            has_valid = 1;
            break;
        }
    }

    if (!has_valid)
        return -4; // Нет ни одной корректной записи

    return 0;
}

// Функция для очистки памяти
void cleanup_filename(char *filename)
{
    if (filename)
    {
        free(filename);
    }
}

// === Функции  статистики ===

// Выводим статистику за месяц года
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

    int counter = 0;            // счетчик корректных записей
    int invalid_counter = 0;    // счетчик не корректных записей
    double avg_temp = 0.0;      // средняя температура
    int8_t min_temp = INT8_MAX; // минимальная температура
    int8_t max_temp = INT8_MIN; // максимальная температура

    // Проходим по всем записям в структуре
    for (uint32_t i = 0; i < data->number; i++)
    {
        const sensor *r = &data->info[i];

        // Пропускаем испорченные записи (is_valid != 0)
        if (r->is_valid != 0)
        {
            invalid_counter++;
            continue;
        }

        // Проверяем соответствие указанному году и месяцу
        if (r->year != year || r->month != month)
        {
            continue;
        }
        // // Дополнительная проверка корректности данных (опционально)
        // // Хотя is_valid уже указывает на корректность, можно проверить и диапазоны
        // if (r->month < 1 || r->month > 12 ||
        //     r->day < 1 || r->day > 31 ||
        //     r->hour > 23 ||
        //     r->minute > 59 ||
        //     r->t < -99 || r->t > 99)
        // {
        //     // Даже если is_valid = 0, но данные не в диапазоне - считаем испорченной
        //     invalid_counter++;
        //     continue;
        // }

        // Собираем статистику только по корректным записям и в соответствии с запросом по году / месяцу
        avg_temp += (double)r->t;

        if (r->t < min_temp)
            min_temp = r->t;

        if (r->t > max_temp)
            max_temp = r->t;

        counter++;
    }

    // Выводим информацию о пропущенных записях
    if (invalid_counter > 0)
    {
        printf("[Info] Внимание: в файле пропущено %d испорченных записей\n", invalid_counter);
    }

    // Проверяем, есть ли корректные данные за указанный период
    if (counter == 0)
    {
        printf("\n[Статистика за %04d-%02d]\n", year, month);
        printf("Нет корректных данных за указанный период.\n");

        if (invalid_counter > 0)
        {
            printf("(Всего обработано %u записей, из них %d помечены как испорченные)\n",
                   data->number, invalid_counter);
        }
        else if (data->number > 0)
        {
            printf("(Обработано %u записей, но ни одна не соответствует периоду %04d-%02d)\n",
                   data->number, year, month);
        }

        return -2; // нет записей за указанный месяц указанного года
    }

    // Рассчитываем среднюю температуру
    avg_temp /= counter;

    // Выводим результаты
    printf("\n[Статистика за %04d-%02d]\n", year, month);
    printf("Обработано корректных записей: %d\n", counter);

    if (invalid_counter > 0)
    {
        printf("Пропущено испорченных записей: %d\n", invalid_counter);
        printf("Всего записей в файле: %u\n", data->number);
    }

    printf("Средняя температура: %+.2f\n", avg_temp);
    printf("Минимальная температура: %+d\n", min_temp);
    printf("Максимальная температура: %+d\n", max_temp);

    // Рассчитываем и выводим амплитуду температур
    int8_t amplitude = max_temp - min_temp;
    printf("Амплитуда температур: %+d\n", amplitude);

    return 0;
}

// Выводим статистику за год
int print_yearly_stats(const sensor_data *data, uint16_t year)
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

    int counter = 0;
    int invalid_counter = 0;
    double avg_temp = 0.0;
    int8_t min_temp = INT8_MAX;
    int8_t max_temp = INT8_MIN;

    // Проходим по всем записям в структуре
    for (uint32_t i = 0; i < data->number; i++)
    {
        const sensor *r = &data->info[i];

        // Пропускаем испорченные записи (is_valid != 0)
        if (r->is_valid != 0)
        {
            invalid_counter++;
            continue;
        }

        // Проверяем соответствие указанному году
        if (r->year != year)
        {
            continue;
        }

        // Дополнительная проверка корректности данных
        if (r->month < 1 || r->month > 12 ||
            r->day < 1 || r->day > 31 ||
            r->hour > 23 ||
            r->minute > 59 ||
            r->t < -99 || r->t > 99)
        {
            // Даже если is_valid = 0, но данные не в диапазоне - считаем испорченной
            invalid_counter++;
            continue;
        }

        // Собираем статистику только по корректным записям
        avg_temp += (double)r->t;

        if (r->t < min_temp)
            min_temp = r->t;

        if (r->t > max_temp)
            max_temp = r->t;

        counter++;
    }

    // Выводим информацию о пропущенных записях
    if (invalid_counter > 0)
    {
        printf("[Info] Внимание: пропущено %d испорченных записей\n", invalid_counter);
    }

    // Проверяем, есть ли корректные данные за указанный год
    if (counter == 0)
    {
        printf("\n[Статистика за %04d]\n", year);
        printf("Нет корректных данных за указанный год.\n");

        if (invalid_counter > 0)
        {
            printf("(Всего обработано %u записей, из них %d помечены как испорченные)\n",
                   data->number, invalid_counter);
        }
        else if (data->number > 0)
        {
            printf("(Обработано %u записей, но ни одна не соответствует году %04d)\n",
                   data->number, year);
        }

        return -2; // нет записей за указанный год
    }

    // Рассчитываем среднюю температуру
    avg_temp /= counter;

    // Выводим результаты
    printf("\n[Годовая статистика за %04d]\n", year);
    printf("Обработано корректных записей: %d\n", counter);

    if (invalid_counter > 0)
    {
        printf("Пропущено испорченных записей: %d\n", invalid_counter);
        printf("Всего записей в файле: %u\n", data->number);
    }

    printf("Средняя температура за год: %+.2f\n", avg_temp);
    printf("Минимальная температура за год: %+d\n", min_temp);
    printf("Максимальная температура за год: %+d\n", max_temp);

    // Рассчитываем и выводим амплитуду температур
    int8_t amplitude = max_temp - min_temp;
    printf("Амплитуда температур за год: %+d\n", amplitude);

    return 0;
}

// === Дополнительные функции ===

// функция печати "хелпа"

void print_help()
{
    printf("======================================================================\n");
    printf("Применение: sensor_app.exe [ключ]...\n");
    printf("Ключи:\n");
    printf("  -h        этот хэлп\n");
    printf("  -f        название файла, из которого берутся данные с датчика для анализа\n");
    printf("  -y        год, за который производится статистика\n");
    printf("            если вводится YY, то автоматически формируется год 20 + введенное число\n");
    printf("            если вводится YYYY, то используется введенное число\n");
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

