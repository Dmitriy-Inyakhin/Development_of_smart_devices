/*
 * Файл: main.c
 * Описание: Точка входа в программу. Обработка аргументов и вывод результатов.
 */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "math_lib.h"



int main(int argc, char *argv[])
{
    // double xl = 0.5, xr = 1.5; /* Интервал содержит корень ~0.854 */
    // double xl = 3.0, xr = 3.5; /* Интервал содержит корень ~0.854 */
    double xl = 2.5, xr = 3.5; /* Интервал содержит корень ~0.854 */
    double eps = 0.0001;

    printf("=== Поиск корня уравнения f1(x) = f3(x) ===\n");
    printf("f1(x) = 0.6x + 3\n");
    printf("f3(x) = 3/x\n");
    printf("Интервал: [%.2f, %.2f], Точность: %.4f\n\n", xl, xr, eps);

    /* Проверка значений на границах */
    printf("Проверка границ:\n");
    printf("  f_diff(%.2f) = %.4f\n", xl, f_diff(xl));
    printf("  f_diff(%.2f) = %.4f\n\n", xr, f_diff(xr));

    /* Поиск корня разными методами */
    // double r1 = rootFindLineSearch(xl, xr, eps, f_diff);
    double r1 = rootFindLineSearch(xl, xr, eps, f2);
    verifyRoot("Line Search", r1, f_diff);

    // double r3 = rootFindDiv2(xl, xr, eps, f_diff);
    double r3 = rootFindDiv2(xl, xr, eps, f2);
    verifyRoot("Div2", r3, f_diff);

    // double r4 = rootFindChord(xl, xr, eps, f_diff);
    double r4 = rootFindChord(xl, xr, eps, f2);
    verifyRoot("Chord", r4, f_diff);

    /* Теоретическое значение корня */
    printf("\n=== Теоретическое значение ===\n");
    printf("0.6x + 3 = 3/x  →  0.6x² + 3x - 3 = 0\n");
    printf("x = (-3 + √(9 + 7.2)) / 1.2 ≈ 0.8541\n");

    return 0;
}
