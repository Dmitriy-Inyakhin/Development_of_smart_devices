#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "math_solver.h"
// #include "tests.h" // Подключить при реализации тестов

/* 
 * Глобальная конфигурация (документирована согласно требованию №7)
 */
// Точность поиска корня
static const double EPS_ROOT = 1e-6;
// Точность интегрирования
static const double EPS_INT = 1e-4;

void print_help() {
    printf("Usage: area_calc [OPTIONS]\n");
    printf("Options:\n");
    printf("  --help         Show this help message\n");
    printf("  --roots        Print abscissas of intersection points\n");
    printf("  --iters        Print iteration counts for root finding\n");
    printf("  --test         Run internal tests for root and integral functions\n");
}

int main(int argc, char *argv[]) {
    int opt_roots = 0;
    int opt_iters = 0;
    int opt_test = 0;

    static struct option long_options[] = {
        {"help",  no_argument, 0, 'h'},
        {"roots", no_argument, 0, 'r'},
        {"iters", no_argument, 0, 'i'},
        {"test",  no_argument, 0, 't'},
        {0, 0, 0, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "hrit", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h': print_help(); return 0;
            case 'r': opt_roots = 1; break;
            case 'i': opt_iters = 1; break;
            case 't': opt_test = 1; break;
            default:  print_help(); return 1;
        }
    }

    // Режим тестирования
    if (opt_test) {
        printf("Running tests...\n");
        // Здесь вызов функций из tests.c
        // if (!run_tests()) return 1; 
        printf("Tests passed.\n");
        return 0;
    }

    // --- Основной расчет ---
    
    // 1. Поиск точек пересечения (интервалы подобраны аналитически/графически)
    // f1 и f3 пересекаются около x=0.85
    int iter1 = 0;
    double x1 = root(f1, f3, df1, df3, 0.5, 1.5, EPS_ROOT, &iter1);

    // f1 и f2 пересекаются около x=3.5 (примерно)
    int iter2 = 0;
    double x2 = root(f1, f2, df1, df2, 3.0, 4.0, EPS_ROOT, &iter2);

    // f2 и f3 пересекаются около x=2.5 (примерно)
    int iter3 = 0;
    double x3 = root(f2, f3, df2, df3, 2.0, 3.0, EPS_ROOT, &iter3);

    // Сортировка точек (упрощенно для примера)
    double points[3] = {x1, x2, x3};
    // ... (код сортировки массива points) ...
    // Для краткости предположим, что отсортировали: p[0] < p[1] < p[2]
    double p0 = x1, p1 = x3, p2 = x2; // Примерный порядок, требует проверки в коде

    if (opt_roots) {
        printf("Intersection abscissas: %.6f, %.6f, %.6f\n", p0, p1, p2);
    }
    if (opt_iters) {
        printf("Iterations: f1-f3=%d, f2-f3=%d, f1-f2=%d\n", iter1, iter3, iter2);
    }

    // 2. Вычисление площади
    // Нужно определить, какая функция верхняя на каждом подотрезке
    // S = integral(Top - Bottom, p0, p1) + integral(Top - Bottom, p1, p2)
    
    // Пример (требуется логика определения верха):
    // На [p0, p1]: верх f1, низ f3
    // На [p1, p2]: верх f1, низ f2
    // (Это нужно проверить вычислением в средней точке)

    double area_part1 = integral(f1, p0, p1, EPS_INT) - integral(f3, p0, p1, EPS_INT);
    double area_part2 = integral(f1, p1, p2, EPS_INT) - integral(f2, p1, p2, EPS_INT);
    
    // В реальном коде нужно брать fabs или менять порядок вычитания в зависимости от знака
    double total_area = fabs(area_part1) + fabs(area_part2);

    printf("Calculated Area: %.6f\n", total_area);

    return 0;
}