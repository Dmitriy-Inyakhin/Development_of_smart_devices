// temp_api.h

#ifndef TEMP_API_H
#define TEMP_API_H

// Структура одной записи температуры
typedef struct {
    int year;     // 4 цифры, например: 2025
    int month;    // 1–12
    int day;      // 1–31
    int hour;     // 0–23
    int minute;   // 0–59
    int temp;     // от -99 до +99
} TempRecord;

// Массив записей (можно заменить на динамический при желании)
#define MAX_RECORDS 100

typedef struct {
    int count;
    TempRecord records[MAX_RECORDS];
} TempData;

// === Прототипы функций (заглушки) ===

// Добавить запись (для примера)
void add_record(TempData *data, int year, int month, int day, int hour, int minute, int temp);

// Вывод всех записей
void print_all(const TempData *data);

// Статистика по месяцу (заглушка)
void print_monthly_stats(const TempData *data, int year, int month);

// Статистика по году (заглушка)
void print_yearly_stats(const TempData *data, int year);

#endif