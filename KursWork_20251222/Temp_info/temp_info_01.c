// main.c

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "temp_functions.h"

// функция парсинга вводимых параметров
static int parse_arguments(int argc, char *argv[], uint16_t *p_year, uint8_t *p_month, char **filename);

// Добавьте эту функцию если её нет
static void print_help(void)
{
    printf("=== Temperature Statistics Program ===\n");
    printf("Usage: temp_info -f <filename.csv> [-y year] [-m month]\n");
    printf("Options:\n");
    printf("  -h          Show this help message\n");
    printf("  -f FILE     Input CSV filename (required)\n");
    printf("  -y [YEAR]   Year filter (default: 2025)\n");
    printf("              2-digit year: 21 -> 2021\n");
    printf("  -m [MONTH]  Month filter (1-12, default: 1)\n");
    printf("\nExamples:\n");
    printf("  temp_info -f data.csv -y 2021 -m 12\n");
    printf("  temp_info -f data.csv -y 21\n");
    printf("  temp_info -f data.csv -m 5\n");
}

int main(int argc, char *argv[])
{
    sensor_data data = {0}; // count = 0 - обязательная запись
	
	printf("DEBUG: Program started\n");
    printf("DEBUG: argc = %d\n", argc);
    
    for (int i = 0; i < argc; i++) {
        printf("DEBUG: argv[%d] = %s\n", i, argv[i]);
    }
	
    uint16_t year = 0;
    uint8_t month = 0;
    char *filename = NULL;

    // Парсим аргументы командной строки
    int parse_result = parse_arguments(argc, argv, &year, &month, &filename);

    if (parse_result == 1)  // -h был вызван
    {
        // Просто завершаем программу
        return 0;
    }
    else if (parse_result == -1)  // Ошибка парсинга
    {
        fprintf(stderr, "Failed to parse arguments. Use -h for help.\n");
        return 1;
    }

    // Проверяем, что имя файла получено
    if (!filename)
    {
        fprintf(stderr, "No filename provided. Use -h for help.\n");
        return 1;
    }

    printf("Parameters: year=%u, month=%u, file=%s\n", year, month, filename);

    // Загрузка данных из файла
    int load_result = load_data_from_file(&data, filename);

    if (load_result != 0)
    {
        fprintf(stderr, "Failed to load data from %s (error code: %d)\n",
                filename, load_result);
        free(filename);
        return 1;
    }

    printf("Successfully loaded %u records\n", data.number);
    
    // Определяем, какую статистику выводить
    int stat_result;
    
    if (month == 0 || month == 1)  // Если месяц не указан или равен 1
    {
        // Выводим годовую статистику
        printf("\n=== Yearly statistics ===\n");
        stat_result = print_yearly_stats(&data, year);
    }
    else 
    {
        // Выводим месячную статистику
        printf("\n=== Monthly statistics ===\n");
        stat_result = print_monthly_stats(&data, year, month);
    }
    
    // Обрабатываем результат вывода статистики
    if (stat_result == -2) 
    {
        printf("No data available for the specified period\n");
    }
    else if (stat_result != 0) 
    {
        fprintf(stderr, "Error calculating statistics (code: %d)\n", stat_result);
    }
    
    // Убираем scanf - он не нужен
    // int a = 0;
    // scanf("%d", &a); // функция для того, чтоб панель cmd не закрывалась сразу

    // Очистка памяти
    free(filename);
    return 0;
}

// функция парсинга вводимых параметров
static int parse_arguments(int argc, char *argv[], uint16_t *p_year, uint8_t *p_month, char **filename)
{
    int rez = 0;
    uint16_t year = 0;
    uint8_t month = 0;
    char *file = NULL;
    int help_requested = 0;  // флаг для -h

    // Инициализация выходных параметров
    if (filename)
        *filename = NULL;
    if (p_year)
        *p_year = 0;
    if (p_month)
        *p_month = 0;

    // Значения по умолчанию
    year = 2025; // год по умолчанию
    month = 0;   // месяц по умолчанию (0 = не указан)

    while ((rez = getopt(argc, argv, "hf:y:m:")) != -1)  // убрал ::
    {
        switch (rez)
        {
        case 'h':
            print_help();
            help_requested = 1;
            break;

        case 'f':
            if (optarg && strlen(optarg) > 0)
            {
                file = malloc(strlen(optarg) + 5);
                if (!file)
                {
                    fprintf(stderr, "Error: memory allocation failed\n");
                    return -1;
                }

                if (strstr(optarg, ".csv") == NULL)
                {
                    sprintf(file, "%s.csv", optarg);
                }
                else
                {
                    strcpy(file, optarg);
                }
                printf("Input file: %s\n", file);
            }
            else
            {
                fprintf(stderr, "Error: -f requires a filename argument\n");
                return -1;
            }
            break;

        case 'y':
            if (optarg)
            {
                char *endptr;
                long y = strtol(optarg, &endptr, 10);

                if (*endptr != '\0')
                {
                    fprintf(stderr, "Warning: invalid year format '%s', using 2025\n", optarg);
                    year = 2025;
                }
                else if (y >= 0 && y < 100)
                {
                    year = 2000 + (uint16_t)y;
                }
                else if (y >= 2000 && y <= 2100)
                {
                    year = (uint16_t)y;
                }
                else
                {
                    fprintf(stderr, "Warning: year %ld out of range, using 2025\n", y);
                    year = 2025;
                }
            }
            break;

        case 'm':
            if (optarg)
            {
                char *endptr;
                long tmp = strtol(optarg, &endptr, 10);

                if (*endptr != '\0')
                {
                    fprintf(stderr, "Warning: invalid month format '%s', using 1\n", optarg);
                    month = 1;
                }
                else if (tmp < 1 || tmp > 12)
                {
                    fprintf(stderr, "Warning: month %ld out of range [1..12], using 1\n", tmp);
                    month = 1;
                }
                else
                {
                    month = (uint8_t)tmp;
                }
            }
            break;

        case '?':
            fprintf(stderr, "Error: unknown option\n");
            return -1;
        }
    }

    // Если запрошена помощь, завершаем
    if (help_requested)
    {
        if (file) free(file);
        return 1;
    }

    // Проверяем обязательные параметры
    if (file == NULL)
    {
        fprintf(stderr, "Error: -f <filename> is required\n");
        fprintf(stderr, "Use -h for help\n");
        return -1;
    }

    // Возвращаем результаты
    if (p_year) *p_year = year;
    if (p_month) *p_month = month;
    if (filename) *filename = file;

    return 0;
}