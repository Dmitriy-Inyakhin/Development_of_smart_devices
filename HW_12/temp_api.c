// temp_api.c

#include "temp_api.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Функция добавления записи
int add_record(sensor_data *data, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, int8_t t)
{
    if (!data)
    {
        return -1;
    }
    if (data->number >= MAX_RECORDS)
    {
        return -2;
    }

    sensor *r = &data->info[data->number];
    r->year = year;
    r->month = month;
    r->day = day;
    r->hour = hour;
    r->minute = minute;
    r->t = t;
    data->number++;

    return 0;
}

// Функция печати всех записей
void print_all(const sensor_data *data)
{
    printf("===================================\n");
    printf("Vsego zapisey: %d\n", data->number);
    for (int i = 0; i < data->number && i < MAX_RECORDS; i++)
    {
        sensor r = data->info[i];
        printf("%04d-%02d-%02d %02d:%02d  t = %+d\n",
               r.year, r.month, r.day, r.hour, r.minute, r.t);
    }
    printf("===================================\n");
}

// функция замены для использования в сортировке
static inline int swap_sensor(sensor *a, sensor *b)
{
    if (!a || !b)
        return -1; // ошибка
    sensor tmp = *a;
    *a = *b;
    *b = tmp;
    return 0; // успех
}

// === Функции  СТАТИСТИКИ ===

// Выводим статистику за месяц года
int print_monthly_stats(const sensor_data *data, int year, int month)
{
    if (!data)
    {
        return -1;
    }
    int counter = 0;
    double avg_temp = 0.0;
    int8_t min_temp = INT8_MAX;
    int8_t max_temp = INT8_MIN;
    for (int i = 0; i < data->number; i++)
    {
        sensor r = data->info[i];
        if (r.year != year || r.month != month)
        {
            continue;
        }
        avg_temp += (double)r.t;
        if (r.t < min_temp)
            min_temp = r.t;
        if (r.t > max_temp)
            max_temp = r.t;
        counter++;
    }
    if (counter == 0)
    {
        printf("\n[Statistika za %04d-%02d]\n", year, month);
        printf("Net dannih za ukazannyy period.\n");
        return -2; //  если нет записей за указанный месяц указаного года
    }
    avg_temp /= counter;
    printf("\n[Statistika za %04d-%02d]\n", year, month);
    printf("Srednyaya temperatura: %+.2f\n", avg_temp);
    printf("Minimal'naya: %+d\n", min_temp);
    printf("Maksimal'naya: %+d\n", max_temp);
    return 0;
}

// Выводим статистику за год
int print_yearly_stats(const sensor_data *data, int year)
{
    if (!data)
    {
        return -1;
    }
    int counter = 0;
    double avg_temp = 0.0;
    int8_t min_temp = INT8_MAX;
    int8_t max_temp = INT8_MIN;
    for (int i = 0; i < data->number; i++)
    {
        sensor r = data->info[i];
        if (r.year != year)
        {
            continue;
        }
        avg_temp += (double)r.t;
        if (r.t < min_temp)
            min_temp = r.t;
        if (r.t > max_temp)
            max_temp = r.t;
        counter++;
    }
    if (counter == 0)
    {
        printf("\n[Statistika za %04d]\n", year);
        printf("Net dannih za ukazannyy period.\n");
        return -2; //  если нет записей за указанный год
    }
    avg_temp /= counter;

    printf("\n[Godovaya statistika za %04d]\n", year);
    printf("Srednyaya temperatura: %+.2f\n", avg_temp);
    printf("Minimal'naya: %+d\n", min_temp);
    printf("Maksimal'naya: %+d\n", max_temp);
    return 0;
}

// === Функции  сравнения и сортировки ===

// функция сравнения по дате
int compare_by_date(const void *a, const void *b)
{
    const sensor *sa = (const sensor *)a;
    const sensor *sb = (const sensor *)b;
    if (sa->year != sb->year)
        return (int)sa->year - (int)sb->year;
    if (sa->month != sb->month)
        return (int)sa->month - (int)sb->month;
    if (sa->day != sb->day)
        return (int)sa->day - (int)sb->day;
    if (sa->hour != sb->hour)
        return (int)sa->hour - (int)sb->hour;
    return (int)sa->minute - (int)sb->minute;
}

// Функция сравнения по температуре
int compare_by_temp(const void *a, const void *b)
{
    const sensor *sa = (const sensor *)a;
    const sensor *sb = (const sensor *)b;
    return (sa->t > sb->t) - (sa->t < sb->t);
}

// Функция сортировки по температуре
int sorByTemp(sensor_data *data)
{
    if (!data)
    {
        return -1; // ошибка: NULL
    }

    // Если записей 0 или 1 — сортировка не нужна
    if (data->number <= 1)
    {
        return 0; // успешно (ничего делать не надо)
    }

    // Используем стандартную qsort — она эффективна (обычно quicksort или introsort)
    // Размер одного элемента — sizeof(sensor)
    // Указатель на начало массива — data->info
    qsort(data->info, (size_t)data->number, sizeof(sensor), compare_by_temp);

    return 0; // успех
}

// Функция сортировки по дате
int sorByDate(sensor_data *data)
{
    if (!data || data->number <= 1)
        return 0;

    qsort(data->info, (size_t)data->number, sizeof(sensor), compare_by_date);

    return 0;
}

// функция печати "хелпа"
void print_help()
{
    printf("===================================\n");
    printf("Ispol'zovanie: sensor_app.exe [klyuch]...\n");
    printf("Klyuchi:\n");
    printf("  -h        etot help\n");
    printf("  -f        nazvanie fayla, iz kotorogo berutsya dannye s datchika\n");
    printf("  -y        god, za kotoryy proizvoditsya statistika\n");
    printf("            esli vvoditsya YY, to avtomaticheski formiruetsya god 20 + vvedennoe chislo\n");
    printf("            esli vvoditsya YYYY, to ispol'zuetsya vvedennoe chislo\n");
    printf("            Esli ukazan, to default 2025\n");
    printf("  -m        mesyats, za kotoryy proizvoditsya statistika\n");
    printf("            Ne obyazatel'nyy argument. Esli ne ukazan, to privoditsya statistika za god\n");
    printf("            Esli ukazan, to privoditsya statistika za ukazannyy mesyats ukazannogo goda\n");
    printf("\n");
    printf("This program built for GNU Make 3.81");
    printf("Report bugs to <010302@rambler.ru>\n");
    printf("===================================\n");
}

