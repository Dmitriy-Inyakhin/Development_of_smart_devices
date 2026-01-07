// main.c

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> // для setlocale

#ifdef _WIN32
#include <windows.h>
#endif

#include "temp_functions.h"

// Функция парсинга вводимых параметров (объявление)
static int parse_arguments(int argc, char *argv[], uint16_t *p_year, uint8_t *p_month, char **filename);

// Главная функция программы
int main(int argc, char *argv[])
{
    // Установка кодировки UTF-8
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#elif defined(__APPLE__)
    setlocale(LC_ALL, "en_US.UTF-8");
    // Альтернатива: setlocale(LC_CTYPE, ""); — но может не дать UTF-8 в консоли
#endif

    sensor_data data = {0};                      // инициализуруем нулями, чтоб не попался мусор
    data.info = malloc(600000 * sizeof(sensor)); // ~ 4.58 МБ в куче

    uint16_t year = 0;
    uint8_t month = 0;
    char *filename = NULL;

    // Парсим аргументы командной строки
    int parse_result = parse_arguments(argc, argv, &year, &month, &filename);

    if (parse_result == 1)
    {
        // Был вызван -h, программа завершается
        fprintf(stdout, "=== ПРОГРАММА ЗАВЕРШЕНА ===\n");
        return 0;
    }
    else if (parse_result == -2)
    {
        fprintf(stderr, "=== ПРОГРАММА ЗАВЕРШЕНА ===\n");
        return 1;
    }
    else if (parse_result != 0)
    {
        // Ошибка парсинга
        fprintf(stderr, "Используйте -h для вызова help\n");
        fprintf(stderr, "=== ПРОГРАММА ЗАВЕРШЕНА ===\n");
        return 1;
    }

    // Проверяем, что имя файла получено
    if (!filename)
    {
        fprintf(stderr, "Нет указанного файла в текущей директории\n");
        return 1;
    }

    printf("Полученные параметры: год=%u, месяц=%u, имя файла=%s\n", year, month, filename);
    fflush(stdout);

    // Загрузка данных из файла
    int load_result = load_data_from_file(&data, filename);

    if (load_result != 0)
    {
        fprintf(stderr, "Ошибка загрузки данных из файла %s (код ошибки: %d)\n",
                filename, load_result);
        free(filename);
        return 1;
    }

    printf("Успешно загружено %u записи (ей) из файла\n", data.number);
    fflush(stdout); // принудительно сбрасывает (очищает) буфер стандартного потока вывода stdout,
                    // то есть выводит всё, что накопилось в буфере, на терминал (или в файл/канал)
                    // немедленно.

    // Определяем, какую статистику выводить
    int stat_result;

    if (month == 0)
    {
        // Если месяц не указан или равен 0 - выводим годовую статистику
        printf("\n=== Статистика за год ===\n");
        fflush(stdout);
        stat_result = print_yearly_stats(&data, year);
    }
    else
    {
        // Выводим месячную статистику
        printf("\n=== Статистика за месяц ===\n");
        fflush(stdout);
        stat_result = print_monthly_stats(&data, year, month);
    }

    // Обрабатываем результат вывода статистики
    if (stat_result == -2)
    {
        printf("Нет данных за указанный период\n");
    }
    else if (stat_result != 0)
    {
        fprintf(stderr, "Ошибка обработки статстики (код ошибки: %d)\n", stat_result);
    }

    // Очистка памяти
    free(filename);

    printf("\n=== ПРОГРАММА ЗАВЕРШЕНА ===\n");

    return 0;
}

// Функция парсинга вводимых параметров (реализация)
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
    year = 2021; // год по умолчанию
    month = 0;   // месяц по умолчанию (0 = не указан)

    // Определяем аргументы для передачи в программу
    while ((rez = getopt(argc, argv, "hf:y:m:")) != -1)
    {
        switch (rez)
        {
        case 'h':
            print_help();
            return 1; // Возвращаем 1

        case 'f':

            file = malloc(strlen(optarg) + 5);
            if (!file)
            {
                fprintf(stderr, "Ошибка: ошибка выделения памяти\n");
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

            break;

        case 'y':
        {
            if (optarg == NULL)
            {
                fprintf(stderr, "Выбран год по умолчанию - 2021\n");
                year = 2021;
            }
            else
            {
                char *endptr;
                long y = strtol(optarg, &endptr, 10);

                if (y >= 0 && y <= 100)
                {
                    year = 2000 + (uint16_t)y;
                }
                else if (y >= 2000 && y <= 2100)
                {
                    year = (uint16_t)y;
                }
                else
                {
                    fprintf(stderr, "Внимание: год %ld вне допустимого диапазона [2000...2100], используем 2021\n", y);
                    year = 2021;
                }
            }
            break;
        }

        case 'm':
        {
            if (optarg == NULL)
            {
                fprintf(stderr, "Значение месяца - 0 (проводим годовую статстику)\n");
                month = 0;
            }
            else
            {
                char *endptr;
                long tmp = strtol(optarg, &endptr, 10);

                if (*endptr != '\0')
                {
                    fprintf(stderr, "Внимание: неправильный формат месяца '%s', используем 0\n", optarg);
                    month = 0;
                }
                else if (tmp < 1 || tmp > 12)
                {
                    fprintf(stderr, "Внимание: месяц %ld вне диапазона [1..12], используем 0\n", tmp);
                    month = 0;
                }
                else
                {
                    month = (uint8_t)tmp;
                }
            }
            break;
        }

        case '?':
            if (optopt == 'f')
            {
                fprintf(stderr, "Ошибка: параметр -f требует имени файла\n");
                return -1;
            }
            else if (optopt == 'y' || optopt == 'm')
            {
                fprintf(stderr, "Ошибка: параметр -%c требует числового значения\n", optopt);
                return -1;
            }
            else
            {
                fprintf(stderr, "Ошибка: неизвестный параметр -%c\n", optopt);
                print_help();
                return -2;
            }
            break;
        }
    }

    // Проверяем обязательные параметры
    if (file == NULL)
    {
        fprintf(stderr, "Ошибка: -f <имя файла> это обязательно\n");
        return -1;
    }

    // Возвращаем результаты через указатели
    if (p_year)
        *p_year = year;
    *p_month = month;
    if (filename)
        *filename = file;

    return 0;
}