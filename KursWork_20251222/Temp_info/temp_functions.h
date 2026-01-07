// temp_functions.h

#ifndef TEMP_FUNCTIONS_H
#define TEMP_FUNCTIONS_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#define MAX_RECORDS 650000 //ограничение максимального количества записей 

//=======================================================
//  === Объявление структур для хранения данных ===     |
//=======================================================

// Структура: показание с датчика ( с признаком корректной или испорченной записи)
typedef struct __attribute__((packed))
{
    uint16_t year;    // 2 байта
    uint8_t month;    // 1 байт (1–12)
    uint8_t day;      // 1 байт (1–31)
    uint8_t hour;     // 1 байт (0–23)
    uint8_t minute;   // 1 байт (0–59)
    int8_t t;         // 1 байт (−99…+99), диапазон укладывается в int8_t
    uint8_t is_valid; // 0 = запись корректна, 1 = испорчена
} sensor;

// Структура: хранения показаний с датчика
typedef struct
{
    uint32_t number;          // номер записи
    sensor *info;  // динамический массив показаний датчика
} sensor_data;

// Структура для хранения помесячной статистики за год
typedef struct
{
    uint8_t month;   // 1..12
    double avg_temp; // средняя температура
    int8_t min_temp; // минимальная
    int8_t max_temp; // максимальная
    uint32_t count;  // количество записей в этом месяце
} monthly_stats;

// Структура для годовой статистики
typedef struct
{
    uint16_t year;
    double avg_temp;
    int8_t min_temp;
    int8_t max_temp;
    uint32_t count;
} yearly_stats;

//=======================================================
//  === Функции работы с файлами ===                    |
//=======================================================

// Функция безопасного открытия файла
FILE *safe_fopen(const char *path, const char *mode);

// Функция чтения данных из файла
int load_data_from_file(sensor_data *d, const char *filename);

// Функция для очистки памяти 
void cleanup_filename(char *filename);

//=======================================================
// === Функции  статистики ===                          |
//=======================================================

// Функция вывода статистики за месяц года
int print_monthly_stats(const sensor_data *data, uint16_t year, uint8_t month);

// Функция вывода статистики за год
int print_yearly_stats(const sensor_data *data, uint16_t year);

//=======================================================
// === Дополнительные функции ===                       |
//=======================================================

// === Функция печати "хелпа" ===
void print_help();

#endif // TEMP_FUNCTIONS_H