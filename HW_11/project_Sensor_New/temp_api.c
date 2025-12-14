// temp_api.c

#include "temp_api.h"
#include <stdio.h>

// Простая заглушка: добавляет запись (без проверок переполнения — для учебного примера)
void add_record(TempData *data, int year, int month, int day, int hour, int minute, int temp) {
    if (data->count < MAX_RECORDS) {
        TempRecord *r = &data->records[data->count];
        r->year = year;
        r->month = month;
        r->day = day;
        r->hour = hour;
        r->minute = minute;
        r->temp = temp;
        data->count++;
    }
}

// Вывод всех записей
void print_all(const TempData *data) {
    printf("Vsego zapisey: %d\n", data->count);
    for (int i = 0; i < data->count; i++) {
        TempRecord r = data->records[i];
        printf("%04d-%02d-%02d %02d:%02d  t = %+d\n",
               r.year, r.month, r.day, r.hour, r.minute, r.temp);
    }
}

// === ЗАГЛУШКИ СТАТИСТИКИ ===

void print_monthly_stats(const TempData *data, int year, int month) {
    // Реальная логика будет позже — пока просто текст
    printf("\n[Statistika za %04d-%02d]\n", year, month);
    printf("Srednyaya temperatura: +5.2\n");
    printf("Minimal'naya: -8\n");
    printf("Maksimal'naya: +18\n");
}

void print_yearly_stats(const TempData *data, int year) {
    printf("\n[Godovaya statistika za %04d]\n", year);
    printf("Srednegodovaya: +6.7\n");
    printf("Minimal'naya: -12\n");
    printf("Maksimal'naya: +28\n");
}