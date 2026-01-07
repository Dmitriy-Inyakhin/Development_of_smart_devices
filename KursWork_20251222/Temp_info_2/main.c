// main.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "temp_functions.h"

static int parse_arguments(int argc, char *argv[], uint16_t *p_year, uint8_t *p_month, char **p_filename);

int main(int argc, char *argv[])
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#elif defined(__APPLE__)
    setlocale(LC_ALL, "en_US.UTF-8");
#else
    setlocale(LC_ALL, "C.UTF-8");
#endif

    sensor_data data = {0};
    data.info = calloc(MAX_RECORDS, sizeof(sensor)); // ★ calloc → нули + защита
    if (!data.info)
    {
        fprintf(stderr, "Ошибка выделения памяти под данные\n");
        return 1;
    }

    uint16_t year = 2021;
    uint8_t month = 0;
    char *filename = NULL;

    int res = parse_arguments(argc, argv, &year, &month, &filename);
    if (res == 1)
    {
        free(data.info);
        return 0; // -h
    }
    else if (res != 0)
    {
        free(data.info);
        return 1;
    }

    printf("Параметры: год=%u, месяц=%u, файл=%s\n", year, month, filename);

    int load_res = load_data_from_file(&data, filename);
    free(filename); // ★ освобождаем сразу
    if (load_res)
    {
        fprintf(stderr, "Ошибка загрузки данных (код %d)\n", load_res);
        free(data.info);
        return 1;
    }

    printf("Загружено записей: %u (испорчено: %u)\n", data.number, data.invalid_count);

    int stat_res;
    if (month == 0)
    {
        puts("\n=== Статистика за год ===");
        stat_res = print_yearly_stats(&data, year);
    }
    else
    {
        puts("\n=== Статистика за месяц ===");
        stat_res = print_monthly_stats(&data, year, month);
    }

    if (stat_res == -2)
    {
        puts("Нет данных за указанный период");
    }
    else if (stat_res != 0)
    {
        fprintf(stderr, "Ошибка статистики (код %d)\n", stat_res);
    }

    free(data.info);
    fflush(stdout); // ★ единственный fflush
    return stat_res == -2 ? 0 : (stat_res ? 1 : 0);
}

static int parse_arguments(int argc, char *argv[], uint16_t *p_year, uint8_t *p_month, char **p_filename)
{
    optind = 0;
    opterr = 0; // ★ переносимость

    uint16_t year = 2021;
    uint8_t month = 0;
    char *file = NULL;

    int c;
    while ((c = getopt(argc, argv, "hf:y:m:")) != -1)
    {
        switch (c)
        {
        case 'h':
            print_help();
            return 1;
        case 'f':
            if (file)
                free(file);
            size_t len = strlen(optarg);
            file = malloc(len + 5);
            if (!file)
                return -1;
            strcpy(file, optarg);
            if (!strstr(optarg, ".csv"))
                strcat(file, ".csv");
            break;
        case 'y':
        {
            char *end;
            long y = strtol(optarg, &end, 10);
            if (*end || y < 0)
            {
                year = 2021;
            }
            else if (y < 100)
                year = 2000 + y;
            else if (y >= 2000 && y <= 2100)
                year = y;
            else
                year = 2021;
            break;
        }
        case 'm':
        {
            char *end;
            long m = strtol(optarg, &end, 10);
            month = (*end || m < 1 || m > 12) ? 0 : (uint8_t)m;
            break;
        }
        case '?':
            if (optopt == 'f')
                fputs("Ошибка: -f требует имени файла\n", stderr);
            else if (optopt == 'y' || optopt == 'm')
                fprintf(stderr, "Ошибка: -%c требует числа\n", optopt);
            else
                fprintf(stderr, "Неизвестный ключ: -%c\n", optopt);
            print_help();
            return -1;
        }
    }

    if (!file)
    {
        fputs("Ошибка: обязательный параметр -f <файл>\n", stderr);
        return -1;
    }

    *p_year = year;
    *p_month = month;
    *p_filename = file;
    return 0;
}