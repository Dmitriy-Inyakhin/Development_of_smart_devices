/* 
 * Файл: math_lib.c
 * Описание: Реализация математических функций и численных методов.
 */

#include "math_lib.h"
#include <stdlib.h>
#include <stdio.h>

/* --- Реализация функций уравнений --- */
double f1(double x) {
    return 0.6 * x + 3.0;
}

double f2(double x) {
    return pow(x - 2.0, 3.0) - 1.0;
}

double f3(double x) {
    return 3.0 / x;
}

/* --- Реализация производных --- */
double df1(double x) {
    (void)x; 
    return 0.6;
}

double df2(double x) {
    return 3.0 * pow(x - 2.0, 2.0);
}

double df3(double x) {
    return -3.0 / (x * x);
}

/* --- Функция поиска корня --- */
double root(func_ptr f, func_ptr g, func_ptr df, func_ptr dg, 
            double a, double b, double eps, int method_id, int *iter_count) {
    
    double x = a; 
    double prev_x = 0.0;
    int iter = 0;
    int max_iter = 1000;

    *iter_count = 0;

    /* 
     * В Си нельзя создать функцию внутри функции.
     * Мы используем переданные указатели f и g напрямую.
     * Разность h(x) = f(x) - g(x) вычисляем в месте использования.
     */

    switch (method_id) {
        case 1: /* Линейный поиск */
            {
                double step = (b - a) / 10000.0;
                x = a;
                while (x <= b) {
                    iter++;
                    /* Вычисляем разность функций напрямую */
                    if (fabs(f(x) - g(x)) < eps) break;
                    x += step;
                    if (iter > max_iter) break;
                }
            }
            break;

        case 2: /* Метод деления пополам (Бисекция) */
            {
                double fa = f(a) - g(a);
                double fb = f(b) - g(b);
                x = a;
                
                if (fa * fb > 0) {
                    x = (a + b) / 2.0; 
                } else {
                    while ((b - a) / 2.0 > eps) {
                        iter++;
                        x = (a + b) / 2.0;
                        double fx = f(x) - g(x);
                        
                        if (fx == 0.0) break;
                        if (fa * fx < 0) {
                            b = x;
                            fb = fx;
                        } else {
                            a = x;
                            fa = fx;
                        }
                        if (iter > max_iter) break;
                    }
                }
            }
            break;

        case 3: /* Метод хорд (секущих) */
            {
                double x_prev = a;
                x = b;
                double f_prev = f(x_prev) - g(x_prev);
                double f_curr = f(x) - g(x);

                while (iter < max_iter) {
                    iter++;
                    if (fabs(f_curr - f_prev) < 1e-12) break;
                    
                    double x_next = x - f_curr * (x - x_prev) / (f_curr - f_prev);
                    
                    if (fabs(x_next - x) < eps) {
                        x = x_next;
                        break;
                    }
                    
                    x_prev = x;
                    f_prev = f_curr;
                    x = x_next;
                    f_curr = f(x) - g(x);
                }
            }
            break;

        case 4: /* Метод касательных (Ньютона) */
            {
                x = (a + b) / 2.0;
                while (iter < max_iter) {
                    iter++;
                    double fx = f(x) - g(x);
                    /* Используем переданные указатели на производные df и dg */
                    double dfx = df(x) - dg(x);
                    
                    if (fabs(dfx) < 1e-12) break;
                    
                    prev_x = x;
                    x = x - fx / dfx;
                    
                    if (fabs(x - prev_x) < eps) break;
                }
            }
            break;

        case 5: /* Комбинированный метод */
            {
                x = (a + b) / 2.0;
                while (iter < max_iter) {
                    iter++;
                    double fx = f(x) - g(x);
                    double dfx = df(x) - dg(x);
                    
                    if (fabs(dfx) < 1e-12) {
                        x = (a + b) / 2.0; 
                    } else {
                        prev_x = x;
                        x = x - fx / dfx;
                        if (x < a || x > b) x = (a + b) / 2.0;
                        if (fabs(x - prev_x) < eps) break;
                    }
                }
            }
            break;

        default:
            printf("Ошибка: Неизвестный метод %d\n", method_id);
            break;
    }

    *iter_count = iter;
    return x;
}

/* --- Функция вычисления интеграла (Метод Симпсона) --- */
double integral(func_ptr func, double a, double b, double eps) {
    int n = 2; 
    double h = (b - a) / n;
    double sum_old = 0.0;
    double sum_new = 0.0;

    sum_new = func(a) + func(b);
    for (int i = 1; i < n; i++) {
        if (i % 2 == 0) sum_new += 2 * func(a + i * h);
        else sum_new += 4 * func(a + i * h);
    }
    sum_new *= h / 3.0;

    do {
        sum_old = sum_new;
        n *= 2;
        h = (b - a) / n;
        sum_new = func(a) + func(b);
        for (int i = 1; i < n; i++) {
            if (i % 2 == 0) sum_new += 2 * func(a + i * h);
            else sum_new += 4 * func(a + i * h);
        }
        sum_new *= h / 3.0;
    } while (fabs(sum_new - sum_old) > eps && n < 10000);

    return sum_new;
}

/* --- Тесты --- */
int run_tests() {
    printf("Запуск тестов...\n");
    int passed = 1;
    int iter = 0;
    
    /* Тест интеграла: f1(x) = 0.6x + 3 на [0, 1] */
    /* Аналитически: 0.3*x^2 + 3x | от 0 до 1 = 0.3 + 3 = 3.3 */
    double res = integral(f1, 0.0, 1.0, 1e-4);
    if (fabs(res - 3.3) > 0.1) {
        printf("Тест интеграла НЕ пройден! Получено: %f (ожидалось 3.3)\n", res);
        passed = 0;
    } else {
        printf("Тест интеграла пройден (результат: %f).\n", res);
    }

    /* Тест поиска корня: f1 = f3 */
    double r = root(f1, f3, df1, df3, 0.5, 1.5, 1e-4, 2, &iter);
    if (r > 0.5 && r < 1.5) {
        printf("Тест поиска корня пройден (x = %f, итераций = %d).\n", r, iter);
    } else {
        printf("Тест поиска корня НЕ пройден (x = %f).\n", r);
        passed = 0;
    }

    return passed;
}