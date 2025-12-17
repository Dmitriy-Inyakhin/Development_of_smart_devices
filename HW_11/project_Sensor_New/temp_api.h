// temp_api.h

#ifndef TEMP_API_H
#define TEMP_API_H

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>   // для getopt(), optarg, optind, и т.д.

// Максимальное количество записей
#define MAX_RECORDS 100

// Структура одной записи температуры
typedef struct
{
    uint16_t year;  // 2 байта
    uint8_t month;  // 1 байт (1–12)
    uint8_t day;    // 1 байт (1–31)
    uint8_t hour;   // 1 байт (0–23)
    uint8_t minute; // 1 байт (0–59)
    int8_t t;       // 1 байт (−99…+99), диапазон укладывается в int8_t

} sensor;

typedef struct
{
    uint32_t number;
    sensor info[MAX_RECORDS];
} sensor_data;

// === Прототипы функций (заглушки) ===

// Функция добавления записи
int add_record(sensor_data *data, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, int8_t temp);

// Функция печати всех записей
void print_all(const sensor_data *data);

// Выводим статистику за месяц года
int print_monthly_stats(const sensor_data *data, int year, int month);

// Выводим статистику за год
int print_yearly_stats(const sensor_data *data, int year);

// Функция сортировки по температуре
int sorByTemp(sensor_data *data);

// Функция сортировки по дате
int sorByDate(sensor_data *data);

// функция печати "хелпа"
void print_help();


#endif