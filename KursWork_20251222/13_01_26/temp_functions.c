#define _POSIX_C_SOURCE 200809L
#include "temp_functions.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

static inline int is_leap_year(uint16_t year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

static const uint8_t days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int is_valid_date(uint16_t y, uint8_t m, uint8_t d, uint8_t h, uint8_t min) {
    if (m < 1 || m > 12) return 0;
    if (d < 1) return 0;
    uint8_t max_days = days_in_month[m - 1];
    if (m == 2 && is_leap_year(y)) max_days = 29;
    if (d > max_days) return 0;
    if (h > 23 || min > 59) return 0;
    return 1;
}

int parse_line(const char *line, uint32_t line_num, sensor *s) {
    if (!line || !s) return 0;

    int y, mo, d, h, mi, t_val;
    //int fields = sscanf(line, "%d %d %d %d %d %d", &y, &mo, &d, &h, &mi, &t_val);
    int fields = sscanf(line, "%d;%d;%d;%d;%d;%d", &y, &mo, &d, &h, &mi, &t_val);

    if (fields != 6) {
        fprintf(stderr, "Ошибка в строке %u: неверное количество полей\n", line_num);
        s->is_valid = 1;
        return 0;
    }

    if (y < 1000 || y > 9999 ||
        mo < 1 || mo > 12 ||
        d < 1 || d > 31 ||
        h < 0 || h > 23 ||
        mi < 0 || mi > 59 ||
        t_val < -99 || t_val > 99) {
        fprintf(stderr, "Ошибка в строке %u: значение вне допустимого диапазона\n", line_num);
        s->is_valid = 1;
        return 0;
    }

    if (!is_valid_date((uint16_t)y, (uint8_t)mo, (uint8_t)d, (uint8_t)h, (uint8_t)mi)) {
        fprintf(stderr, "Ошибка в строке %u: некорректная дата/время\n", line_num);
        s->is_valid = 1;
        return 0;
    }

    s->year = (uint16_t)y;
    s->month = (uint8_t)mo;
    s->day = (uint8_t)d;
    s->hour = (uint8_t)h;
    s->minute = (uint8_t)mi;
    s->t = (int8_t)t_val;
    s->is_valid = 0;
    return 1;
}

sensor_data* read_csv_file(const char* filename, uint32_t *total_lines) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Не удалось открыть файл");
        return NULL;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    uint32_t capacity = 1024;
    sensor_data *data = malloc(sizeof(sensor_data));
    if (!data) goto fail;

    data->info = malloc(capacity * sizeof(sensor));
    if (!data->info) {
        free(data);
        goto fail;
    }

    data->number = 0;
    *total_lines = 0;

    // Пропускаем заголовок
    if ((read = getline(&line, &len, fp)) != -1) {
        (*total_lines)++;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        (*total_lines)++;
        if (data->number >= capacity) {
            capacity *= 2;
            sensor *tmp = realloc(data->info, capacity * sizeof(sensor));
            if (!tmp) {
                free(line);
                fclose(fp);
                free(data->info);
                free(data);
                return NULL;
            }
            data->info = tmp;
        }

        if (parse_line(line, *total_lines, &data->info[data->number])) {
            data->number++;
        }
    }

    free(line);
    fclose(fp);
    return data;

fail:
    fclose(fp);
    return NULL;
}

void free_sensor_data(sensor_data *data) {
    if (data) {
        free(data->info);
        free(data);
    }
}

void compute_monthly_stats(const sensor_data *data, monthly_stats stats[12]) {
    for (int i = 0; i < 12; ++i) {
        stats[i].month = (uint8_t)(i + 1);
        stats[i].min_temp = INT8_MAX;
        stats[i].max_temp = INT8_MIN;
        stats[i].avg_temp = 0.0;
        stats[i].count = 0;
    }

    for (uint32_t i = 0; i < data->number; ++i) {
        const sensor *s = &data->info[i];
        if (s->is_valid) continue;

        int idx = s->month - 1;
        monthly_stats *m = &stats[idx];

        m->count++;
        m->avg_temp += s->t;
        if (s->t < m->min_temp) m->min_temp = s->t;
        if (s->t > m->max_temp) m->max_temp = s->t;
    }

    for (int i = 0; i < 12; ++i) {
        if (stats[i].count > 0) {
            stats[i].avg_temp /= stats[i].count;
        } else {
            stats[i].min_temp = 0;
            stats[i].max_temp = 0;
            stats[i].avg_temp = 0.0;
        }
    }
}

void compute_yearly_stats(const sensor_data *data, yearly_stats *y_stats) {
    y_stats->min_temp = INT8_MAX;
    y_stats->max_temp = INT8_MIN;
    y_stats->avg_temp = 0.0;
    y_stats->count = 0;
    y_stats->year = 0;

    for (uint32_t i = 0; i < data->number; ++i) {
        const sensor *s = &data->info[i];
        if (s->is_valid) continue;

        if (y_stats->year == 0) y_stats->year = s->year;
        y_stats->count++;
        y_stats->avg_temp += s->t;
        if (s->t < y_stats->min_temp) y_stats->min_temp = s->t;
        if (s->t > y_stats->max_temp) y_stats->max_temp = s->t;
    }

    if (y_stats->count > 0) {
        y_stats->avg_temp /= y_stats->count;
    } else {
        y_stats->min_temp = 0;
        y_stats->max_temp = 0;
        y_stats->avg_temp = 0.0;
    }
}

void print_monthly_stats(const monthly_stats stats[12], int month_filter) {
    int start = (month_filter >= 1 && month_filter <= 12) ? month_filter - 1 : 0;
    int end = (month_filter >= 1 && month_filter <= 12) ? month_filter : 12;

    for (int i = start; i < end; ++i) {
        if (stats[i].count == 0) continue;
        printf("Месяц %d:\n", stats[i].month);
        printf("  Средняя: %.2f\n", stats[i].avg_temp);
        printf("  Минимум: %d\n", stats[i].min_temp);
        printf("  Максимум: %d\n", stats[i].max_temp);
        printf("  Записей: %u\n", stats[i].count);
        if (month_filter != -1) break;
    }
}

void print_yearly_stats(const yearly_stats *y_stats) {
    if (y_stats->count == 0) {
        printf("Нет корректных данных за год.\n");
        return;
    }
    printf("Годовая статистика (%u):\n", y_stats->year);
    printf("  Средняя: %.2f\n", y_stats->avg_temp);
    printf("  Минимум: %d\n", y_stats->min_temp);
    printf("  Максимум: %d\n", y_stats->max_temp);
    printf("  Записей: %u\n", y_stats->count);
}