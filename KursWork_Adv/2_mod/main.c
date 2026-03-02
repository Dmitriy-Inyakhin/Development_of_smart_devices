/*
 * Файл: main.c
 * Описание: Точка входа в программу. Обработка аргументов и вывод результатов.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "math_lib.h"

/*
 * Глобальная переменная для хранения выбранного метода.
 * По умолчанию метод половинного деления (2).
 */
static int g_method_id = 2;

/* Функция вывода справки */
void print_help()
{
    printf("Использование: ./area_calc [ОПЦИИ]\n");
    printf("Опции:\n");
    printf("  --help          Показать эту справку\n");
    printf("  --roots         Напечатать абсциссы точек пересечения\n");
    printf("  --iters         Напечатать число итераций поиска корней\n");
    printf("  --test          Запустить тесты функций\n");
    printf("  --method <N>    Выбрать метод поиска корня (1-5):\n");
    printf("                  1 - Линейный поиск\n");
    printf("                  2 - Деление пополам\n");
    printf("                  3 - Метод хорд\n");
    printf("                  4 - Метод касательных\n");
    printf("                  5 - Комбинированный\n");
}

int main(int argc, char *argv[])
{
    /*
     * Настройка локали для поддержки русского языка в консоли.
     * Пустая строка "" берет настройки из операционной системы.
     */
    if (setlocale(LC_ALL, "") == NULL)
    {
        /* Если не получилось, пробуем явно указать русскую */
        setlocale(LC_ALL, "ru_RU.UTF-8");
    }

    int opt_roots = 0;
    int opt_iters = 0;
    int opt_test = 0;

    /* Простой парсер аргументов (для новичка проще чем getopt) */
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--help") == 0)
        {
            print_help();
            return 0;
        }
        else if (strcmp(argv[i], "--roots") == 0)
        {
            opt_roots = 1;
        }
        else if (strcmp(argv[i], "--iters") == 0)
        {
            opt_iters = 1;
        }
        else if (strcmp(argv[i], "--test") == 0)
        {
            opt_test = 1;
        }
        else if (strcmp(argv[i], "--method") == 0)
        {
            if (i + 1 < argc)
            {
                g_method_id = atoi(argv[i + 1]);
                i++; /* Пропускаем следующий аргумент, так как мы его прочитали */
            }
            else
            {
                printf("Ошибка: после --method нужно указать число.\n");
                return 1;
            }
        }
    }

    /* Если выбран режим тестирования */
    if (opt_test)
    {
        if (run_tests())
        {
            printf("Все тесты успешно пройдены!\n");
            return 0;
        }
        else
        {
            printf("Тесты провалены!\n");
            return 1;
        }
    }

    printf("=== Расчет площади фигуры ===\n");
    printf("Используемый метод поиска корня: %d\n", g_method_id);

    /*
     * Переменные для хранения точек пересечения.
     * Я подобрал отрезки [a, b] заранее, зная график функций.
     */
    int iter1 = 0, iter2 = 0, iter3 = 0;
    double eps = 1e-6;

    /* 1. Пересечение f1 и f3 (примерно x = 0.85) */
    double x1 = root(f1, f3, df1, df3, 0.5, 1.5, eps, g_method_id, &iter1);

    /* 2. Пересечение f3 и f2 (примерно x = 3.0) */
    double x2 = root(f3, f2, df3, df2, 2.5, 3.5, eps, g_method_id, &iter2);

    /* 3. Пересечение f1 и f2 (примерно x = 3.6) */
    double x3 = root(f1, f2, df1, df2, 3.5, 4.5, eps, g_method_id, &iter3);

    /* Вывод абсцисс, если запрошено */
    if (opt_roots)
    {
        printf("Точки пересечения (абсциссы):\n");
        printf("  f1 и f3: x = %.6f\n", x1);
        printf("  f3 и f2: x = %.6f\n", x2);
        printf("  f1 и f2: x = %.6f\n", x3);
    }

    /* Вывод итераций, если запрошено */
    if (opt_iters)
    {
        printf("Затраченные итерации:\n");
        printf("  Корень 1: %d\n", iter1);
        printf("  Корень 2: %d\n", iter2);
        printf("  Корень 3: %d\n", iter3);
    }

    /*
     * Вычисление площади.
     * Фигура ограничена сверху f1, снизу слева f3, снизу справа f2.
     * Площадь = Интеграл(f1 - f3) от x1 до x2 + Интеграл(f1 - f2) от x2 до x3.
     */
    double eps_int = 1e-4;

    /* Разность функций для первого участка */
    double area1 = integral(f1, x1, x2, eps_int) - integral(f3, x1, x2, eps_int);

    /* Разность функций для второго участка */
    double area2 = integral(f1, x2, x3, eps_int) - integral(f2, x2, x3, eps_int);

    double total_area = area1 + area2;

    printf("Площадь фигуры: %.6f\n", total_area);

    return 0;
}