// temp_api.c

#include "temp_api.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

// === Вспомогательные (уже известные) функции ===

FILE *safe_fopen(const char *path, const char *mode) {
    FILE *f = fopen(path, mode);
    if (!f) {
        fprintf(stderr, "Oshibka otkrytiya faila '%s' v rezhime '%s': ", path, mode);
        perror("");
    }
    return f;
}

int compare_by_date(const void *a, const void *b) {
    const sensor *sa = (const sensor *)a;
    const sensor *sb = (const sensor *)b;
    if (sa->year != sb->year) return (int)sa->year - (int)sb->year;
    if (sa->month != sb->month) return (int)sa->month - (int)sb->month;
    if (sa->day != sb->day) return (int)sa->day - (int)sb->day;
    if (sa->hour != sb->hour) return (int)sa->hour - (int)sb->hour;
    return (int)sa->minute - (int)sb->minute;
}

int compare_by_temp(const void *a, const void *b) {
    const sensor *sa = (const sensor *)a;
    const sensor *sb = (const sensor *)b;
    return (sa->t > sb->t) - (sa->t < sb->t);
}

void print_data(const sensor_data *d) {
    printf("===================================\n");
    printf("Vsego zapisey: %u\n", d->number);
    for (uint32_t i = 0; i < d->number && i < MAX_RECORDS; ++i) {
        printf("%04u-%02u-%02u %02u:%02u  t = %3d\n",
               d->info[i].year,
               d->info[i].month,
               d->info[i].day,
               d->info[i].hour,
               d->info[i].minute,
               d->info[i].t);
    }
    printf("===================================\n");
}

int init_sample_data(sensor_data *d) {
    if (!d) return 0;
    sensor sample[] = {
        {2021, 9, 16, 10, 30, 9},
        {2022, 9, 2, 8, 15, -9},
        {2022, 9, 2, 9, 0, -5},
        {2022, 9, 2, 12, 45, 0},
        {2021, 1, 7, 7, 20, 8},
        {2021, 1, 7, 14, 55, 9},
        {2021, 1, 7, 18, 10, 10},
        {2021, 1, 7, 22, 5, 18},
        {2021, 1, 7, 3, 30, 0},
        {2021, 9, 5, 15, 0, 1}
    };
    size_t n = sizeof(sample) / sizeof(sample[0]);
    if (n > MAX_RECORDS) n = MAX_RECORDS;
    memcpy(d->info, sample, n * sizeof(sensor));
    d->number = (uint32_t)n;
    return (int)n;
}

int save_data_to_file(const sensor_data *d, const char *filename) {
    if (!d || !filename) return -1;
    if (d->number > MAX_RECORDS) return -2;
    FILE *f = safe_fopen(filename, "wb");
    if (!f) return -3;
    size_t written = 0;
    written += fwrite(&d->number, sizeof(d->number), 1, f);
    written += fwrite(d->info, sizeof(sensor), d->number, f);
    fclose(f);
    return (written == 1 + d->number) ? 0 : -4;
}


int load_data_from_file(sensor_data *d, const char *filename) {
    if (!d || !filename) return -1;
    FILE *f = safe_fopen(filename, "rb");
    if (!f) return -2;

    if (fread(&d->number, sizeof(d->number), 1, f) != 1) {
        fclose(f);
        return -3;
    }
    if (d->number > MAX_RECORDS) {
        fclose(f);
        return -4;
    }

    size_t read = fread(d->info, sizeof(sensor), d->number, f);
    fclose(f);
    if (read != d->number) {
        d->number = (uint32_t)read;
        return -5;
    }
    return 0;
}

// === ЗАГЛУШКИ СТАТИСТИКИ ===

int get_monthly_stats(const sensor_data *d, uint16_t year, uint8_t month, monthly_stats *out) {
    if (!d || !out || month < 1 || month > 12) return -1;
    // Заглушка: возвращаем условные значения
    out->month = month;
    out->avg_temp = 5.5;     // заглушка
    out->min_temp = -10;
    out->max_temp = 25;
    out->count = 12;
    return 0;
}

int get_yearly_stats(const sensor_data *d, uint16_t year, yearly_stats *out) {
    if (!d || !out) return -1;
    out->year = year;
    out->avg_temp = 7.3;
    out->min_temp = -15;
    out->max_temp = 32;
    out->count = 145;
    return 0;
}

void print_monthly_stats(const sensor_data *d) {
    if (!d) return;
    printf("\n=== Statistika po mesyatsam (zaglushki) ===\n");
    for (int m = 1; m <= 12; ++m) {
        monthly_stats ms;
        if (get_monthly_stats(d, 2022, m, &ms) == 0 && ms.count > 0) {
            printf("Mesyats %02u: srednyaya = %5.1f, min = %3d, max = %3d, kol-vo = %u\n",
                   ms.month, ms.avg_temp, ms.min_temp, ms.max_temp, ms.count);
        }
    }
}

void print_yearly_stats(const sensor_data *d) {
    if (!d) return;
    printf("\n=== Godovaya statistika (zaglushka) ===\n");
    yearly_stats ys;
    if (get_yearly_stats(d, 2022, &ys) == 0) {
        printf("God %u: srednyaya = %5.1f, min = %3d, max = %3d, izmereniy = %u\n",
               ys.year, ys.avg_temp, ys.min_temp, ys.max_temp, ys.count);
    }
}