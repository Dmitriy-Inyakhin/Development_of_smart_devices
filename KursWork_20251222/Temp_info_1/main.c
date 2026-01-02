// main.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>   // для setlocale

#ifdef _WIN32
    #include <windows.h>
#endif

#include "temp_functions.h"

// функция парсинга вводимых параметров
static int parse_arguments(int argc, char *argv[], uint16_t *p_year, uint8_t *p_month, char **filename);

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

    sensor_data data = {0};
    data.info = malloc(600000 * sizeof(sensor));
    if (!data.info) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 1;
    }

    uint16_t year = 0;
    uint8_t month = 0;
    char *filename = NULL;

    int parse_result = parse_arguments(argc, argv, &year, &month, &filename);
    if (parse_result == 1) {
        free(data.info);
        return 0;
    }
    if (parse_result != 0) {
        fprintf(stderr, "Неудача при парсинге аргументов (код: %d)\n", parse_result);
        fprintf(stderr, "Используйте -h для вызова help\n");
        free(data.info);
        if (filename) free(filename);
        return 1;
    }

    if (!filename) {
        fprintf(stderr, "Ошибка: требуется указать файл через -f\n");
        free(data.info);
        return 1;
    }

    printf("Полученные параметры: год=%u, месяц=%u, имя файла=%s\n", year, month, filename);
    fflush(stdout);

    int load_result = load_data_from_file(&data, filename);
    if (load_result != 0) {
        fprintf(stderr, "Ошибка загрузки данных из %s (код: %d)\n", filename, load_result);
        free(data.info);
        free(filename);
        return 1;
    }

    printf("Успешно загружено %u записи(ей)\n", data.number);
    fflush(stdout);

    int stat_result;
    if (month == 0) {
        printf("\n=== Статистика за год ===\n");
        fflush(stdout);
        stat_result = print_yearly_stats(&data, year);
    } else {
        printf("\n=== Статистика за месяц ===\n");
        fflush(stdout);
        stat_result = print_monthly_stats(&data, year, month);
    }

    if (stat_result == -2) {
        printf("Нет данных за указанный период\n");
    } else if (stat_result != 0) {
        fprintf(stderr, "Ошибка обработки статистики (код: %d)\n", stat_result);
    }

    free(data.info);
    free(filename);
    printf("\n=== ПРОГРАММА ЗАВЕРШЕНА ===\n");
    return 0;
}

// === parse_arguments (как в исходном, без изменений) ===
static int parse_arguments(int argc, char *argv[], uint16_t *p_year, uint8_t *p_month, char **filename)
{
    int rez = 0;
    uint16_t year = 2021;
    uint8_t month = 0;
    char *file = NULL;

    if (filename) *filename = NULL;
    if (p_year) *p_year = 0;
    if (p_month) *p_month = 0;

    while ((rez = getopt(argc, argv, "hf:y:m:")) != -1) {
        switch (rez) {
            case 'h':
                print_help();
                return 1;
            case 'f':
                if (!optarg) {
                    fprintf(stderr, "Ошибка: -f требует имени файла\n");
                    return -1;
                }
                if (strlen(optarg) == 0) {
                    fprintf(stderr, "Ошибка: имя файла не может быть пустым\n");
                    return -1;
                }
                file = malloc(strlen(optarg) + 5);
                if (!file) {
                    fprintf(stderr, "Ошибка выделения памяти\n");
                    return -1;
                }
                if (strstr(optarg, ".csv") == NULL) {
                    sprintf(file, "%s.csv", optarg);
                } else {
                    strcpy(file, optarg);
                }
                fprintf(stderr, "Статистика из файла: %s\n", file);
                break;
            case 'y':
                if (!optarg) {
                    year = 2021;
                    fprintf(stderr, "Выбран год по умолчанию - 2021\n");
                } else {
                    char *endptr;
                    long y = strtol(optarg, &endptr, 10);
                    if (*endptr != '\0') {
                        fprintf(stderr, "Ошибка: неправильный формат года '%s', используем 2021\n", optarg);
                        year = 2021;
                    }
                    else if (y >= 0 && y < 100) {
                        year = 2000 + (uint16_t)y;
                        fprintf(stderr, "Год: %u (from %s)\n", year, optarg);
                    }
                    else if (y >= 2000 && y <= 2100) {
                        year = (uint16_t)y;
                        fprintf(stderr, "Год: %u\n", year);
                    }
                    else {
                        fprintf(stderr, "Внимание: год %ld вне [2000..2100], используем 2021\n", y);
                        year = 2021;
                    }
                }
                break;
            case 'm':
                if (!optarg) {
                    month = 0;
                    fprintf(stderr, "Значение месяца - 0 (проводим годовую статистику)\n");
                } else {
                    char *endptr;
                    long tmp = strtol(optarg, &endptr, 10);
                    if (*endptr != '\0') {
                        fprintf(stderr, "Внимание: неправильный формат месяца '%s', используем 0\n", optarg);
                        month = 0;
                    }
                    else if (tmp < 1 || tmp > 12) {
                        fprintf(stderr, "Внимание: месяц %ld вне [1..12], используем 0\n", tmp);
                        month = 0;
                    }
                    else {
                        month = (uint8_t)tmp;
                        fprintf(stderr, "Месяц: %u\n", month);
                    }
                }
                break;
            case '?':
                fprintf(stderr, "Ошибка: неизвестный ключ\n");
                print_help();
                return -1;
        }
    }

    if (!file) {
        fprintf(stderr, "Ошибка: -f <имя файла> это обязательно\n");
        fprintf(stderr, "Используйте -h для вызова help\n");
        return -1;
    }

    if (p_year) *p_year = year;
    if (p_month) *p_month = month;
    if (filename) *filename = file;

    return 0;
}