// temp_api.h

#ifndef TEMP_API_H
#define TEMP_API_H

#include <stdio.h>
#include <stdint.h>

#define MAX_RECORDS 30

// Обновлённая структура: год, месяц, день, час, минута, температура [-99..+99]
typedef struct __attribute__((packed)) {
    uint16_t year;   // 2 байта
    uint8_t  month;  // 1 байт (1–12)
    uint8_t  day;    // 1 байт (1–31)
    uint8_t  hour;   // 1 байт (0–23)
    uint8_t  minute; // 1 байт (0–59)
    int8_t   t;      // 1 байт (−99…+99), диапазон укладывается в int8_t
} sensor;

typedef struct {
    uint32_t number;
    sensor info[MAX_RECORDS];
} sensor_data;

// === Прототипы функций ===

// Инициализация примера
int init_sample_data(sensor_data *d);

// Вывод всех записей
void print_data(const sensor_data *d);

// Сравнения для qsort (объявлены, но можно перенести в .c при желании)
int compare_by_date(const void *a, const void *b);
int compare_by_temp(const void *a, const void *b);

// Работа с файлами
FILE *safe_fopen(const char *path, const char *mode);
int save_data_to_file(const sensor_data *d, const char *filename);
int load_data_from_file(sensor_data *d, const char *filename);

// === Статистика (заглушки) ===

// Структура для хранения статистики за месяц
typedef struct {
    uint8_t month;            // 1..12
    double  avg_temp;         // средняя температура
    int8_t  min_temp;         // минимальная
    int8_t  max_temp;         // максимальная
    uint32_t count;           // количество записей в этом месяце
} monthly_stats;

// Структура для годовой статистики
typedef struct {
    uint16_t year;
    double  avg_temp;
    int8_t  min_temp;
    int8_t  max_temp;
    uint32_t count;
} yearly_stats;

// Получить статистику по конкретному месяцу и году
int get_monthly_stats(const sensor_data *d, uint16_t year, uint8_t month, monthly_stats *out);

// Получить статистику по году
int get_yearly_stats(const sensor_data *d, uint16_t year, yearly_stats *out);

// Вывести статистику по всем месяцам (в порядке возрастания даты первого появления)
void print_monthly_stats(const sensor_data *d);

// Вывести статистику по году
void print_yearly_stats(const sensor_data *d);

#endif // TEMP_API_H