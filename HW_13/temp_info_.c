// main.c

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "temp_functions.h"

// функция парсинга вводимых параметров
static int parse_arguments(int argc, char *argv[], uint16_t *p_year, uint8_t *p_month, char **filename);

int main(int argc, char *argv[])
{
     // Вывод в stderr всегда виден
    fprintf(stderr, "=== PROGRAM START ===\n");
    fprintf(stderr, "argc=%d\n", argc);
    for (int i = 0; i < argc; i++) {
        fprintf(stderr, "argv[%d]=%s\n", i, argv[i]);
    }
	setbuf(stdout, NULL);  // Отключаем буферизацию stdout
    setbuf(stderr, NULL);  // Отключаем буферизацию stderr
	
	sensor_data data = {0}; // count = 0 - обязательная запись, иначе ни чего работать не будет!
	
	
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

    if (parse_result == 1)
    {
        // Был вызван -h, программа должна завершиться ?
        return 0;
    }
    else if (parse_result != 0) 
    {
        // Ошибка парсинга
        fprintf(stderr, "Failed to parse arguments (error code: %d)\n", parse_result);
        return 1;
    }

    // Проверяем, что имя файла получено
    if (!filename)
    {
        fprintf(stderr, "No filename provided\n");
        return 1;
    }

    // Загрузка данных из файла

    int load_result = load_data_from_file(&data, filename);

    if (load_result != 0)
    {
        fprintf(stderr, "Failed to load data from %s (error code: %d)\n",
                filename, load_result);
        cleanup_filename(filename);
        return 1;
    }

    printf("Successfully loaded %u records\n", data.number);
    
    // Определяем, какую статистику выводить
    int stat_result;
    
    if (month == 0) 
    {
        // Если месяц не указан или равен 0 - выводим годовую статистику
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
    

    int a = 0;
    scanf("%d", &a); // функция для того, чтоб панель cmd не закрывалась сразу

    // Очистка памяти
    cleanup_filename(filename);
    return 0;
}

// функция парсинга вводимых параметров
static int parse_arguments(int argc, char *argv[], uint16_t *p_year, uint8_t *p_month, char **filename)
{
    int rez = 0;
    uint16_t year = 0;
    uint8_t month = 0;
    char *file = NULL;

    // Инициализация выходных параметров
    if (filename)
        *filename = NULL;
    if (p_year)
        *p_year = 0;
    if (p_month)
        *p_month = 0;

    // Значения по умолчанию
    year = 2025; // год по умолчанию
    month = 1;   // месяц по умолчанию

    while ((rez = getopt(argc, argv, "hf:y::m::")) != -1)
    {
        switch (rez)
        {
        case 'h':
            print_help();
            // return 1; // Индикатор, что нужно завершить программу
            break;

        case 'f':
            if (optarg)
            {
                // Проверяем длину имени файла
                if (strlen(optarg) > 0)
                {
                    // Выделяем память для имени файла
                    file = malloc(strlen(optarg) + 5); // +5 для ".csv" и нуль-терминатора
                    if (!file)
                    {
                        fprintf(stderr, "Error: memory allocation failed\n");
                        return -1;
                    }

                    // Добавляем расширение .csv если его нет
                    if (strstr(optarg, ".csv") == NULL)
                    {
                        sprintf(file, "%s.csv", optarg);
                    }
                    else
                    {
                        strcpy(file, optarg);
                    }
                }
                else
                {
                    fprintf(stderr, "Error: filename cannot be empty\n");
                    return -1;
                }
            }
            else
            {
                fprintf(stderr, "Error: -f requires a filename argument\n");
                return -1;
            }
            break;

        case 'y':
        {
            if (optarg == NULL)
            {
                printf("argument \"y\" default - 2025\n");
                year = 2025;
            }
            else
            {
                // Более надежная проверка ввода
                char *endptr;
                long y = strtol(optarg, &endptr, 10);

                // Проверяем, что вся строка была конвертирована
                if (*endptr != '\0')
                {
                    fprintf(stderr, "Warning: invalid year format '%s', using default 2025\n", optarg);
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
                    fprintf(stderr, "Warning: year %ld out of reasonable range, using default 2025\n", y);
                    year = 2025;
                }
            }
            break;
        }

        case 'm':
        {
            if (optarg == NULL)
            {
                printf("argument \"m\" default - 01\n");
                month = 1;
            }
            else
            {
                char *endptr;
                long tmp = strtol(optarg, &endptr, 10);

                if (*endptr != '\0')
                {
                    fprintf(stderr, "Warning: invalid month format '%s', using default 1\n", optarg);
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
        }

        case '?':
            fprintf(stderr, "Error: unknown option or missing argument\n");
            //return -1;
            break;
        }
    }

    // Проверяем обязательные параметры
    if (file == NULL)
    {
        fprintf(stderr, "Error: -f <filename> is required\n");
        return -1;
    }

    // Возвращаем результаты через указатели
    if (p_year)
        *p_year = year;
    if (p_month)
        *p_month = month;
    if (filename)
        *filename = file;
    else
    {
        free(file); // Освобождаем, если указатель не был передан
    }

    return 0; // Успешное завершение
}

