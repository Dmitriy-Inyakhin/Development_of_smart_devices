// main.c

#include <stdio.h>
#include <unistd.h>
#include "temp_api.h"
#include <stdlib.h>

// функция парсинга вводимых параметров
static void parse_arguments(int argc, char *argv[], uint16_t *p_yyyy, uint8_t *p_mm);

int main(int argc, char *argv[])
{
    sensor_data data = {0}; // count = 0 - обязательная запись, иначе ни чего работать не будет!

    uint16_t yyyy = 0;
    uint8_t mm = 0;
    parse_arguments(argc, argv, &yyyy, &mm);
    
    printf("%d, %02d\n", yyyy, mm);
    // Добавим несколько записей вручную (как пример)
    add_record(&data, 2024, 4, 10, 14, 45, 18);
    add_record(&data, 2024, 4, 11, 7, 15, 9);
    add_record(&data, 2024, 4, 10, 8, 30, 12);
    add_record(&data, 2024, 5, 10, 14, 45, 21);
    add_record(&data, 2024, 5, 11, 7, 15, 8);

    // add_record(&data, 2025, 2, 10, 8, 30, 12);
    // add_record(&data, 2025, 3, 10, 14, 45, 18);
    // add_record(&data, 2025, 3, 11, 7, 15, 9);
    // add_record(&data, 2025, 4, 5, 10, 0, -2);
    // add_record(&data, 2025, 4, 6, 16, 20, 21);

    // Выводим всё
    print_all(&data);

    // Статистика
    print_monthly_stats(&data, 2024, 4);

    // print_yearly_stats(&data, 2025);
    print_yearly_stats(&data, 2026);

    if (sorByDate(&data) != 0)
    {
        fprintf(stderr, "Error sorting by date\n");
        return 1;
    }
    // Выводим всё
    print_all(&data);

    if (sorByTemp(&data) != 0)
    {
        fprintf(stderr, "Error sorting by temperature\n");
        return 1;
    }
    // Выводим всё
    print_all(&data);

    int a = 0;
    scanf("%d", &a);

    return 0;
}

// функция парсинга вводимых параметров
static void parse_arguments(int argc, char *argv[], uint16_t *p_yyyy, uint8_t *p_mm)
{
    int rez = 0;
    uint16_t yyyy = 0;
    uint8_t mm = 0;

    while ((rez = getopt(argc, argv, "hf::y::m::")) != -1)
    {
        switch (rez)
        {
        case 'h':
            print_help();
            break;
        case 'f':
            printf("found argument \"f = %s.csv\"\n", optarg);
            break;
        case 'y':
        {
            if (optarg == NULL)
            {
                printf("argument \"y\" default - 2025\n");
                yyyy = 2025;
            }
            else
            {
                long y = strtol(optarg, NULL, 10);
                if (y >= 0 && y < 100)
                {
                    yyyy = 2000 + (uint16_t)y;
                }
                else
                {
                    yyyy = (uint16_t)y;
                }
            }
            break;
        }
        case 'm':
        {
            if (optarg == NULL)
            {
                // printf("argument \"m\" default - 01\n");
                mm = 1;
            }
            else
            {
                int tmp = atoi(optarg);
                if (tmp < 1 || tmp > 12)
                {
                    fprintf(stderr, "Warning: month %d out of range [1..12], using 1\n", tmp);
                    mm = 1;
                }
                else
                {
                    mm = (uint8_t)tmp;
                }
            }
            break;
        }
        case '?':
            printf("Error found !\n");
            break;
        }
    }

    // Возвращаем результаты через указатели
    if (p_yyyy)
        *p_yyyy = yyyy;
    if (p_mm)
        *p_mm = mm;
}
