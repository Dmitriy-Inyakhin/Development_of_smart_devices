#include "math_solver.h"
#include <stdlib.h>
#include <stdio.h>

/* --- Определение функций --- */
double f1(double x) { return 0.6 * x + 3.0; }
double f2(double x) { return pow(x - 2.0, 3.0) - 1.0; }
double f3(double x) { return 3.0 / x; }

/* --- Производные --- */
double df1(double x) { (void)x; return 0.6; }
double df2(double x) { return 3.0 * pow(x - 2.0, 2.0); }
double df3(double x) { return -3.0 / (x * x); }

/* --- Поиск корня (Комбинированный метод) --- */
double root(func_t f, func_t g, func_t df, func_t dg, 
            double a, double b, double eps1, int *iter_count) {
    
    // Локальная статическая переменная для отслеживания итераций внутри, 
    // но требование просит вывести их, поэтому используем переданный указатель.
    // Обнуляем счетчик
    if (iter_count) *iter_count = 0;

    double fa = f(a) - g(a);
    double fb = f(b) - g(b);

    // Проверка наличия корня на отрезке (теорема Больцано-Коши)
    if (fa * fb > 0.0) {
        // В реальной программе стоит вернуть ошибку или NaN, 
        // для задания предполагаем, что отрезок выбран верно.
        // Попытаемся найти корень методом Ньютона с середины
    }

    double x = (a + b) / 2.0; // Начальное приближение
    double prev_x = x;
    int max_iter = 1000;
    
    while (iter_count && *iter_count < max_iter) {
        (*iter_count)++;
        double y = f(x) - g(x);
        double dy = df(x) - dg(x);

        // Метод Ньютона
        if (fabs(dy) > 1e-12) {
            x = x - y / dy;
        } else {
            // Если производная мала, делаем шаг бисекции
            x = (a + b) / 2.0;
        }

        // Ограничение x пределами отрезка (защита от вылета)
        if (x < a || x > b) {
            x = (a + b) / 2.0;
        }

        // Уточнение отрезка для бисекции (гибридизация)
        double y_new = f(x) - g(x);
        if (fa * y_new <= 0) {
            b = x;
            fb = y_new;
        } else {
            a = x;
            fa = y_new;
        }

        if (fabs(x - prev_x) < eps1) {
            break;
        }
        prev_x = x;
    }
    return x;
}

/* --- Интеграл (Адаптивный Симпсон) --- */
static double simpson(func_t func, double a, double b) {
    double c = (a + b) / 2.0;
    return (b - a) / 6.0 * (func(a) + 4.0 * func(c) + func(b));
}

// Рекурсивная вспомогательная функция
static double adaptive_simpson(func_t func, double a, double b, double eps, double whole) {
    double c = (a + b) / 2.0;
    double left = simpson(func, a, c);
    double right = simpson(func, c, b);
    double delta = left + right - whole;

    if (fabs(delta) <= 15.0 * eps) {
        return left + right + delta / 15.0;
    }
    return adaptive_simpson(func, a, c, eps / 2.0, left) +
           adaptive_simpson(func, c, b, eps / 2.0, right);
}

double integral(func_t func, double a, double b, double eps2) {
    double whole = simpson(func, a, b);
    return adaptive_simpson(func, a, b, eps2, whole);
}