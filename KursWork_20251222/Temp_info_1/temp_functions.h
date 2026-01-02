// temp_functions.h
#ifndef TEMP_FUNCTIONS_H
#define TEMP_FUNCTIONS_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>  // для INT8_MIN/MAX в print_*_stats

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

// Работа с файлами
int load_data_from_file(sensor_data *d, const char *filename);
FILE *safe_fopen(const char *path, const char *mode);
void cleanup_filename(char *filename);

// Статистика
int print_monthly_stats(const sensor_data *data, uint16_t year, uint8_t month);
int print_yearly_stats(const sensor_data *data, uint16_t year);

// Help
void print_help();

#endif // TEMP_FUNCTIONS_H