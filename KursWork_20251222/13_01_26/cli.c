#include "cli.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_help(void) {
    printf("Использование: temp_stats -f <файл.csv> [-m <месяц>] [-h]\n");
    printf("Ключи:\n");
    printf("  -h          Показать эту справку\n");
    printf("  -f FILE     Указать входной CSV-файл\n");
    printf("  -m MONTH    Вывести статистику только за указанный месяц (1–12)\n");
}

int parse_arguments(int argc, char *argv[], char **filename, int *month_filter) {
    *filename = NULL;
    *month_filter = -1;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-h") == 0) {
            print_help();
            return 0;
        } else if (strcmp(argv[i], "-f") == 0) {
            if (++i >= argc) {
                fprintf(stderr, "Ошибка: не указано имя файла после -f\n");
                return -1;
            }
            *filename = argv[i];
        } else if (strcmp(argv[i], "-m") == 0) {
            if (++i >= argc) {
                fprintf(stderr, "Ошибка: не указан номер месяца после -m\n");
                return -1;
            }
            long m = strtol(argv[i], NULL, 10);
            if (m < 1 || m > 12) {
                fprintf(stderr, "Ошибка: номер месяца должен быть от 1 до 12\n");
                return -1;
            }
            *month_filter = (int)m;
        } else {
            fprintf(stderr, "Неизвестный аргумент: %s\n", argv[i]);
            return -1;
        }
    }

    if (*filename == NULL) {
        fprintf(stderr, "Ошибка: необходимо указать входной файл с помощью -f\n");
        return -1;
    }

    return 1;
}