// temp_functions.h

#ifndef TEMP_FUNCTIONS_H
#define TEMP_FUNCTIONS_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Структура: год, месяц, день, час, минута, температура [-99..+99]
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

typedef struct
{
    uint32_t number;          // номер записи
    // sensor info[MAX_RECORDS]; // значение датчика
    sensor *info;  // динамический массив
} sensor_data;

// Структура для хранения статистики за месяц
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

//  === Работа с файлами ===

//загрузка данных из файла
int load_data_from_file(sensor_data *d, const char *filename);

// Функция safe_fopen - это "безопасная" обертка над стандартной функцией fopen из языка C
FILE *safe_fopen(const char *path, const char *mode);

// Функция для очистки памяти 
void cleanup_filename(char *filename);

// === Статистика ===

// Выводим статистику за месяц года
int print_monthly_stats(const sensor_data *data, uint16_t year, uint8_t month);

// Выводим статистику за год
int print_yearly_stats(const sensor_data *data, uint16_t year);


// === Функция печати "хелпа" ===
void print_help();

#endif // TEMP_FUNCTIONS_H