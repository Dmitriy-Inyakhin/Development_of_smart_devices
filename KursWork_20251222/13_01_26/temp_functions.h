#ifndef TEMP_FUNCTIONS_H
#define TEMP_FUNCTIONS_H

#include <stdint.h>
#include <stdio.h>

typedef struct __attribute__((packed))
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    int8_t t;
    uint8_t is_valid;
} sensor;

typedef struct
{
    uint32_t number;
    sensor *info;
} sensor_data;

typedef struct
{
    uint8_t month;
    double avg_temp;
    int8_t min_temp;
    int8_t max_temp;
    uint32_t count;
} monthly_stats;

typedef struct
{
    uint16_t year;
    double avg_temp;
    int8_t min_temp;
    int8_t max_temp;
    uint32_t count;
} yearly_stats;

// Функции обработки данных
sensor_data* read_csv_file(const char* filename, uint32_t *total_lines);
void free_sensor_data(sensor_data *data);
void compute_monthly_stats(const sensor_data *data, monthly_stats stats[12]);
void compute_yearly_stats(const sensor_data *data, yearly_stats *y_stats);
void print_monthly_stats(const monthly_stats stats[12], int month_filter);
void print_yearly_stats(const yearly_stats *y_stats);

// Вспомогательные функции
int is_valid_date(uint16_t y, uint8_t m, uint8_t d, uint8_t h, uint8_t min);
int parse_line(const char *line, uint32_t line_num, sensor *s);

#endif // TEMP_FUNCTIONS_H