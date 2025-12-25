// temp_info.c

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "temp_functions.h"

// функция парсинга вводимых параметров
static int parse_arguments(int argc, char *argv[], uint16_t *p_year, uint8_t *p_month, char **filename);

int main(int argc, char *argv[])
{
    // Отключаем буферизацию
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    // Установка кодировки UTF-8 для Windows
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    sensor_data data = {0};
    data.info = malloc(600000 * sizeof(sensor));  // 4.58 МБ в куче

    uint16_t year = 0;
    uint8_t month = 0;
    char *filename = NULL;

    // Парсим аргументы командной строки
    int parse_result = parse_arguments(argc, argv, &year, &month, &filename);

    if (parse_result == 1)
    {
        // Был вызван -h, программа завершается
        fprintf(stderr, "Help requested, exiting...\n");
        return 0;
    }
    else if (parse_result != 0)
    {
        // Ошибка парсинга
        fprintf(stderr, "Failed to parse arguments (error code: %d)\n", parse_result);
        fprintf(stderr, "Use -h for help\n");
        return 1;
    }

    // Проверяем, что имя файла получено
    if (!filename)
    {
        fprintf(stderr, "No filename provided\n");
        return 1;
    }

    printf("Parameters: year=%u, month=%u, file=%s\n", year, month, filename);
    fflush(stdout);

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
    fflush(stdout);

    // Определяем, какую статистику выводить
    int stat_result;

    if (month == 0)
    {
        // Если месяц не указан или равен 0 - выводим годовую статистику
        printf("\n=== Yearly statistics ===\n");
        fflush(stdout);
        stat_result = print_yearly_stats(&data, year);
    }
    else
    {
        // Выводим месячную статистику
        printf("\n=== Monthly statistics ===\n");
        fflush(stdout);
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

    // Очистка памяти
    free(filename);

    printf("\n=== PROGRAM END ===\n");

    // Пауза только в Windows
    #ifdef _WIN32
        system("pause");
    #endif

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
    month = 0;   // месяц по умолчанию (0 = не указан)

    // ВАЖНО: убрано ::
    while ((rez = getopt(argc, argv, "hf:y:m:")) != -1)
    {
        switch (rez)
        {
        case 'h':
            print_help();
            return 1; // ВОЗВРАЩАЕМ 1!

        case 'f':
            if (optarg)
            {
                if (strlen(optarg) > 0)
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
                    fprintf(stderr, "File specified: %s\n", file);
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
                fprintf(stderr, "Year argument default - 2025\n");
                year = 2025;
            }
            else
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
                    fprintf(stderr, "Year: %u (from %s)\n", year, optarg);
                }
                else if (y >= 2000 && y <= 2100)
                {
                    year = (uint16_t)y;
                    fprintf(stderr, "Year: %u\n", year);
                }
                else
                {
                    fprintf(stderr, "Warning: year %ld out of range, using 2025\n", y);
                    year = 2025;
                }
            }
            break;
        }

        case 'm':
        {
            if (optarg == NULL)
            {
                fprintf(stderr, "Month argument default - 0 (yearly stats)\n");
                month = 0;
            }
            else
            {
                char *endptr;
                long tmp = strtol(optarg, &endptr, 10);

                if (*endptr != '\0')
                {
                    fprintf(stderr, "Warning: invalid month format '%s', using 0\n", optarg);
                    month = 0;
                }
                else if (tmp < 1 || tmp > 12)
                {
                    fprintf(stderr, "Warning: month %ld out of range [1..12], using 0\n", tmp);
                    month = 0;
                }
                else
                {
                    month = (uint8_t)tmp;
                    fprintf(stderr, "Month: %u\n", month);
                }
            }
            break;
        }

        case '?':
            fprintf(stderr, "Error: unknown option\n");
            return -1;
        }
    }

    // Проверяем обязательные параметры
    if (file == NULL)
    {
        fprintf(stderr, "Error: -f <filename> is required\n");
        fprintf(stderr, "Use -h for help\n");
        return -1;
    }

    // Возвращаем результаты через указатели
    if (p_year)
        *p_year = year;
    if (p_month)
        *p_month = month;
    if (filename)
        *filename = file;

    return 0;
}