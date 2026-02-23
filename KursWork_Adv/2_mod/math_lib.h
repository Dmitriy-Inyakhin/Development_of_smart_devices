/*
 * Файл: math_lib.h
 * Описание: Заголовочный файл для математических функций и численных методов.
 * Автор: Студент (начинающий программист)
 */

#ifndef MATH_LIB_H
#define MATH_LIB_H

#include <math.h>

/*
 * Тип данных для указателя на функцию, принимающую double и возвращающую double.
 * Это нужно, чтобы передавать функции f1, f2 и т.д. как аргументы.
 */
typedef double (*func_ptr)(double);

/*
 * Функции самих уравнений (кривых)
 */
double f1(double x);
double f2(double x);
double f3(double x);

/*
 * Производные функций (нужны для метода касательных)
 */
double df1(double x);
double df2(double x);
double df3(double x);

/*
 * Функция поиска корня уравнения f(x) = g(x).
 * Параметры:
 *   f, g - функции, образующие уравнение
 *   df, dg - их производные (используются в методах Ньютона и комбинированном)
 *   a, b - границы отрезка поиска
 *   eps - требуемая точность
 *   method_id - номер метода (1-5)
 *   iter_count - указатель на переменную для записи числа итераций
 */
double root(func_ptr f, func_ptr g, func_ptr df, func_ptr dg,
            double a, double b, double eps, int method_id, int *iter_count);

/*
 * Функция вычисления определенного интеграла методом Симпсона.
 * Параметры:
 *   func - подынтегральная функция
 *   a, b - пределы интегрирования
 *   eps - требуемая точность
 */
double integral(func_ptr func, double a, double b, double eps);

/*
 * Функция запуска тестов. Возвращает 1, если все тесты пройдены.
 */
int run_tests();

#endif