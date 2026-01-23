#include <stdio.h>
#include <stdlib.h>
#include "cli.h"
#include "temp_functions.h"

#include <locale.h> // для setlocale

#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char *argv[])
{

    // Установка кодировки UTF-8 выборочно для винды и мака
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#elif defined(__APPLE__)
    setlocale(LC_ALL, "en_US.UTF-8");
    // Альтернатива: setlocale(LC_CTYPE, ""); — но может не дать UTF-8 в консоли
#endif

    char *filename = NULL;
    int month_filter = -1;

    int parse_result = parse_arguments(argc, argv, &filename, &month_filter);
    if (parse_result <= 0)
    {
        return (parse_result == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    uint32_t total_lines = 0;
    sensor_data *data = read_csv_file(filename, &total_lines);
    if (!data)
    {
        fprintf(stderr, "Ошибка при чтении файла\n");
        return EXIT_FAILURE;
    }

    if (data->number == 0)
    {
        fprintf(stderr, "Нет корректных записей в файле\n");
        free_sensor_data(data);
        return EXIT_FAILURE;
    }

    monthly_stats monthly[12];
    yearly_stats yearly;

    compute_monthly_stats(data, monthly);
    compute_yearly_stats(data, &yearly);

    if (month_filter != -1)
    {
        print_monthly_stats(monthly, month_filter);
    }
    else
    {
        print_monthly_stats(monthly, -1);
        printf("\n");
        print_yearly_stats(&yearly);
    }

    free_sensor_data(data);
    return EXIT_SUCCESS;
}