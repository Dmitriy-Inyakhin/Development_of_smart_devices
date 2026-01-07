// temp_functions.c
#include <stdlib.h>
#include "temp_functions.h"

//=======================================================
// === Вспомогательные функции ===                      |
//=======================================================
// Функция сравнения двух времён.
// Возвращает: -1 — t1 < t2, 0 — t1 == t2, +1 — t1 > t2
static int compare_time(const sensor *t1, const sensor *t2)
{
    if (t1->year != t2->year)   return (t1->year < t2->year) ? -1 : +1;
    if (t1->month != t2->month) return (t1->month < t2->month) ? -1 : +1;
    if (t1->day != t2->day)     return (t1->day < t2->day) ? -1 : +1;
    if (t1->hour != t2->hour)   return (t1->hour < t2->hour) ? -1 : +1;
    if (t1->minute != t2->minute) return (t1->minute < t2->minute) ? -1 : +1;
    return 0; // равны
}

// Инициализация массива статистики по месяцам
static void init_monthly_stats(monthly_stats *stats)
{
    for (int m = 0; m < 12; m++) {
        stats[m].month = (uint8_t)(m + 1);
        stats[m].count = 0;
        stats[m].avg_temp = 0.0;
        stats[m].min_temp = INT8_MAX;
        stats[m].max_temp = INT8_MIN;
    }
}

// Основная функция сбора помесячной статистики за указанный год
static void compute_monthly_stats(const sensor_data *data, uint16_t year,
                                  monthly_stats *good_stats, uint32_t *bad_count)
{
    init_monthly_stats(good_stats);
    memset(bad_count, 0, 12 * sizeof(uint32_t));

    for (uint32_t i = 0; i < data->number; i++) {
        const sensor *r = &data->info[i];
        // ★ ВАЖНО: пропускаем НЕ только по году, но и считаем bad_count ТОЛЬКО для нужного года
        if (r->year != year) continue;
        if (r->month < 1 || r->month > 12) continue;

        int idx = r->month - 1;

        if (r->is_valid != 0) {
            bad_count[idx]++;
            continue;
        }

        good_stats[idx].count++;
        good_stats[idx].avg_temp += (double)r->t;
        if (r->t < good_stats[idx].min_temp)
            good_stats[idx].min_temp = r->t;
        if (r->t > good_stats[idx].max_temp)
            good_stats[idx].max_temp = r->t;
    }

    for (int m = 0; m < 12; m++) {
        if (good_stats[m].count > 0) {
            good_stats[m].avg_temp /= good_stats[m].count;
        }
    }
}

// Функция вывода одной строки таблицы помесячной статистики
static void print_monthly_row(uint32_t row_num, uint16_t year, const monthly_stats *mstat, uint32_t bad)
{
    printf("%u", row_num);
    printf("\t%04u", year);
    printf("\t%02u", mstat->month);
    printf("\t%u", mstat->count);
    printf("\t%u", bad);
    if (mstat->count > 0) {
        printf("\t%.2f",    mstat->avg_temp);
        printf("\t%+d",     mstat->min_temp);
        printf("\t%+d",     mstat->max_temp);
    } else {
        printf("\tN/A\tN/A\tN/A");
    }
    printf("\n");
}

// Функция расчёта общей годовой статистики
static void compute_yearly_stats(const monthly_stats *months, yearly_stats *ystat, uint16_t year)
{
    ystat->year = year;
    ystat->count = 0;
    ystat->avg_temp = 0.0;
    ystat->min_temp = INT8_MAX;
    ystat->max_temp = INT8_MIN;
    double total_sum = 0.0;

    for (int m = 0; m < 12; m++) {
        ystat->count += months[m].count;
        total_sum += months[m].avg_temp * months[m].count;
        if (months[m].count > 0) {
            if (months[m].min_temp < ystat->min_temp)
                ystat->min_temp = months[m].min_temp;
            if (months[m].max_temp > ystat->max_temp)
                ystat->max_temp = months[m].max_temp;
        }
    }

    if (ystat->count > 0) {
        ystat->avg_temp = total_sum / ystat->count;
    }
}

//=======================================================
//  === Функции работы с файлами ===                    |
//=======================================================
FILE *safe_fopen(const char *path, const char *mode)
{
    FILE *f = fopen(path, mode);
    if (!f) {
        fprintf(stderr, "Ошибка открытия файла '%s' в режиме '%s': ", path, mode);
        perror("");
    }
    return f;
}

int load_data_from_file(sensor_data *d, const char *filename)
{
    if (!d || !filename) return -1;
    FILE *f = safe_fopen(filename, "r");
    if (!f) return -2;

    d->number = 0;
    d->invalid_count = 0; // ★ инициализируем
    char line[128]; // сокращено: max строка ~50 байт
    sensor prev_record = {0};

    while (fgets(line, sizeof(line), f) && d->number < MAX_RECORDS) {
        line[strcspn(line, "\r\n")] = '\0';

        sensor *cur = &d->info[d->number];
        memset(cur, 0, sizeof(sensor));
        cur->is_valid = 1; // по умолчанию — испорчена

        int y, mo, d_, h, m, t;
        int n = sscanf(line, "%d;%d;%d;%d;%d;%d", &y, &mo, &d_, &h, &m, &t);

        int all_fields_valid = (n == 6 &&
                                y >= 0 && y <= 65535 &&
                                mo >= 1 && mo <= 12 &&
                                d_ >= 1 && d_ <= 31 &&
                                h >= 0 && h <= 23 &&
                                m >= 0 && m <= 59 &&
                                t >= -99 && t <= 99);

        if (all_fields_valid) {
            cur->year = (uint16_t)y;
            cur->month = (uint8_t)mo;
            cur->day = (uint8_t)d_;
            cur->hour = (uint8_t)h;
            cur->minute = (uint8_t)m;
            cur->t = (int8_t)t;

            if (d->number == 0) {
                cur->is_valid = 0;
                prev_record = *cur;
            } else {
                if (compare_time(&prev_record, cur) < 0) {
                    cur->is_valid = 0;
                    prev_record = *cur;
                }
            }
        }

        if (cur->is_valid != 0)
            d->invalid_count++;

        d->number++;
    }
    fclose(f);

    if (d->number == 0) return -3;
    for (uint32_t i = 0; i < d->number; i++) {
        if (d->info[i].is_valid == 0) return 0;
    }
    return -4;
}

//=======================================================
// === Функции статистики ===                          |
//=======================================================
int print_monthly_stats(const sensor_data *data, uint16_t year, uint8_t month)
{
    if (!data || data->number == 0) return -1;

    // ★ используем ЕДИНСТВЕННЫЙ источник: data->invalid_count
    if (data->invalid_count > 0) {
        printf("В файле всего испорчено записей: %u\n", data->invalid_count);
    }

    monthly_stats good_stats[12];
    uint32_t bad_count[12];
    compute_monthly_stats(data, year, good_stats, bad_count);

    const monthly_stats *mstat = &good_stats[month - 1];
    uint32_t bad = bad_count[month - 1];

    // ★ явно считаем плохие за месяц (для проверки и вывода)
    uint32_t bad_in_month = 0;
    for (uint32_t i = 0; i < data->number; i++) {
        const sensor *r = &data->info[i];
        if (r->year == year && r->month == month && r->is_valid != 0)
            bad_in_month++;
    }
    // Согласованность: bad должно равняться bad_in_month
    if (bad != bad_in_month) {
        fprintf(stderr, "[WARN] bad_count[%u]=%u ≠ bad_in_month=%u\n", month-1, bad, bad_in_month);
    }

    if (mstat->count == 0 && bad_in_month == 0) {
        printf("\n[Статистика за %04u-%02u]\n", year, month);
        printf("Нет записей (корректных и испорченных) за указанный период.\n");
        return -2;
    }

    printf("Испорченных записей за %04u-%02u: %u\n", year, month, bad_in_month);

    printf("#\tГод\tМесяц\tКолЗап\tПлохЗап\tСрдТемп\tМинТемп\tМаксТемп\n");
    print_monthly_row(1, year, mstat, bad);
    return 0;
}

int print_yearly_stats(const sensor_data *data, uint16_t year)
{
    if (!data || data->number == 0) return -1;

    if (data->invalid_count > 0) {
        printf("В файле всего испорчено записей: %u\n", data->invalid_count);
    }

    monthly_stats good_stats[12];
    uint32_t bad_count[12];
    compute_monthly_stats(data, year, good_stats, bad_count);

    // ★ явно считаем плохие за год
    uint32_t bad_in_year = 0;
    for (uint32_t i = 0; i < data->number; i++) {
        const sensor *r = &data->info[i];
        if (r->year == year && r->is_valid != 0)
            bad_in_year++;
    }

    uint32_t sum_bad = 0;
    for (int m = 0; m < 12; m++) sum_bad += bad_count[m];
    if (sum_bad != bad_in_year) {
        fprintf(stderr, "[WARN] sum(bad_count)=%u ≠ bad_in_year=%u\n", sum_bad, bad_in_year);
    }

    printf("Испорченных записей за %04u год: %u\n", year, bad_in_year);

    printf("#\tГод\tМесяц\tКолЗап\tПлохЗап\tСрдТемп\tМинТемп\tМаксТемп\n");
    for (int m = 0; m < 12; m++) {
        print_monthly_row((uint32_t)(m + 1), year, &good_stats[m], bad_count[m]);
    }

    yearly_stats ystat;
    compute_yearly_stats(good_stats, &ystat, year);

    printf("\n[Годовая статистика за %04u]\n", ystat.year);
    printf("Обработано корректных записей за год: %u\n", ystat.count);
    if (bad_in_year > 0) {
        printf("Пропущено испорченных записей за запрошенный год: %u\n", bad_in_year);
    }

    if (ystat.count == 0) {
        printf("Нет корректных данных за указанный год.\n");
        return -2;
    }

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
void print_help()
{
    printf("======================================================================\n");
    printf("Применение: sensor_app [ключ]...\n");
    printf("Ключи:\n");
    printf("  -h        этот хэлп\n");
    printf("  -f        название файла (без .csv или с .csv)\n");
    printf("  -y        год (YY => 20YY, YYYY => как есть; по умолчанию 2021)\n");
    printf("  -m        месяц (1–12; если не указан — годовая статистика)\n");
    printf("\n");
    printf("О всех ошибках — на <010302@rambler.ru>\n");
    printf("======================================================================\n");
}