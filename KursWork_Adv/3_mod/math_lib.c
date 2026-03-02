/*
 * Файл: math_lib.c
 * Описание: Реализация математических функций и численных методов.
 */

#include "math_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* --- Реализация функций уравнений --- */
double f1(double x)
{
    return 0.6 * x + 3.0;
}

double f2(double x)
{
    return pow(x - 2.0, 3.0) - 1.0;
}

double f3(double x)
{
    return 3.0 / x;
}

/* --- Реализация производных --- */
double df1(double x)
{
    (void)x;
    return 0.6;
}

double df2(double x)
{
    return 3.0 * pow(x - 2.0, 2.0);
}

double df3(double x)
{
    return -3.0 / (x * x);
}

/* === Разность функций для поиска пересечения === */
double f_diff(double x)
{
    return f1(x) - f3(x); /* Ищем где f1(x) = f3(x) */
}

/* === Знак функции (принимает функцию как параметр) === */
int signFunc(double x, function f)
{
    double val = f(x);
    return val == 0 ? 0 : (val < 0 ? -1 : 1);
}

/* --- Линейный поиск--- */
float rootFindLineSearch(double xl, double xr, double eps, function f)
{
    double x = xl;
    double step = eps;
    int stepcount = 0;

    while (x <= xr)
    {
        stepcount++;
        if (fabs(f(x)) < eps)
        { /* Нашли где функция близка к нулю */
            printf("Line Search: %d шагов\n", stepcount);
            return x;
        }
        x += step;
    }
    printf("Line Search: %d шагов (точное значение не найдено)\n", stepcount);
    return x;
}

/* === Метод деления отрезка пополам v2 (с проверкой границ) === */
double rootFindDiv2(double xl, double xr, double eps, function f)
{
    int stepcount = 0;
    double xm;

    if (fabs(f(xl)) < eps)
    {
        printf("Div2: %d шагов\n", stepcount);
        return xl;
    }
    if (fabs(f(xr)) < eps)
    {
        printf("Div2: %d шагов\n", stepcount);
        return xr;
    }

    while (fabs(xr - xl) > eps)
    {
        stepcount++;
        xm = (xl + xr) / 2.0;

        if (fabs(f(xm)) < eps)
        {
            printf("Div2: %d шагов\n", stepcount);
            return xm;
        }

        if (f(xl) * f(xm) < 0)
            xr = xm;
        else
            xl = xm;
    }
    printf("Div2: %d шагов\n", stepcount);
    return (xl + xr) / 2.0;
}

/* === Метод хорд (доработан) === */
double rootFindChord(double xl, double xr, double eps, function f)
{
    int stepcount = 0;
    double x_prev = xl;
    double x_curr = xr;

    while (fabs(x_curr - x_prev) > eps)
    {
        stepcount++;
        x_prev = x_curr;

        /* Формула хорды */
        x_curr = x_prev - f(x_prev) * (x_prev - xl) / (f(x_prev) - f(xl));

        if (stepcount > 1000)
        { /* Защита от бесконечного цикла */
            printf("Chord: превышено число итераций\n");
            break;
        }
    }
    printf("Chord: %d шагов\n", stepcount);
    return x_curr; /* ИСПРАВЛЕНО: было (xl - xr) / 2 */
}

/* === Проверка: подставляем найденный корень обратно === */
void verifyRoot(const char *methodName, double root, function f)
{
    printf("%s: x = %.6f, f(x) = %.6f\n", methodName, root, f(root));
}

/* --- Метод касательных (Ньютона) --- */
float rootFindTangent(float xn, float eps, function f, function df)
{
    float x1 = xn - f(xn) / df(xn);
    float x0 = xn;
    while (fabs(x0 - x1) > eps)
    {
        x0 = x1;
        x1 = x1 - f(x1) / df(x1);
    }
    return x1;
}

/* --- Комбинированный метод --- */
float rootFindCombine(float xl, float xr, float eps, function f, function df, function ddf)
{
    while (fabs(xl - xr) > 2 * eps)
    {
        if (f(xl) * ddf(xl) < 0)
            xl = xl - (f(xl) * (xl - xr)) / (f(xl) - f(xr));
        else
            xl = xl - f(xl) / df(xl);
        if (f(xr) * ddf(xr) < 0)
            xr = xr - (f(xr) * (xr - xl)) / (f(xr) - f(xl));
        else
            xr = xr - f(xr) / df(xr);
    }
    return (xl + xr) / 2;
}

/* --- Нахождение площадей фигур --- */

/* --- Вычисление интеграла методом прямоугольника --- */
float calcIntegralSquare(double xl, double xr, size_t n, function f)
{
    double sum = 0.0;
    double h = (xr - xl) / n;

    for (size_t i = 0; i < n; i++)
    {
        double x = xl + i * h; // ✅ Не меняем xl, вычисляем текущую точку
        sum += f(x);
    }
    return sum * h;
}

/* --- Вычисление интеграла методом трапеций --- */
double calcIntegralTrap(double xl, double xr, size_t n, function f)
{
    double sum = 0.0;
    double h = (xr - xl) / n;

    /* Формула трапеций: h * (f(x0)/2 + f(x1) + f(x2) + ... + f(xn)/2) */
    sum += f(xl) / 2.0; // ✅ Первый коэффициент 1/2

    for (size_t i = 1; i < n; i++)
    {
        double x = xl + i * h;
        sum += f(x); // ✅ Средние точки с коэффициентом 1
    }

    sum += f(xr) / 2.0; // ✅ Последний коэффициент 1/2

    return sum * h;
}

/* --- Вычисление интеграла по методу Симпсона --- */
double calcIntegralSimpson(double xl, double xr, size_t n, function f)
{
    /* Метод Симпсона требует ЧЁТНОГО числа отрезков */
    if (n % 2 != 0)
    {
        n++; // ✅ Делаем n чётным
    }

    double sum = 0.0;
    double h = (xr - xl) / n;

    /* Формула Симпсона: h/3 * (f(x0) + 4f(x1) + 2f(x2) + 4f(x3) + ... + f(xn)) */
    sum += f(xl); // ✅ Первый коэффициент 1

    for (size_t i = 1; i < n; i++)
    {
        double x = xl + i * h;
        if (i % 2 == 0)
        {
            sum += 2.0 * f(x); // ✅ Чётные индексы: коэффициент 2
        }
        else
        {
            sum += 4.0 * f(x); // ✅ Нечётные индексы: коэффициент 4
        }
    }

    sum += f(xr); // ✅ Последний коэффициент 1

    return sum * h / 3.0;
}

/* --- Вычисление интеграла с помощью метода Монте-Карло --- */
double calcIntegralMonteCarlo(double xl, double xr, double fmax, size_t n, function f)
{
    if (n == 0) return 0.0; // Защита от деления на ноль

    size_t in_d = 0;
    double width = fabs(xr - xl); // fabs работает и с double, и с float
    
    for (size_t i = 0; i < n; i++)
    {
        // Генерация double в диапазоне [0, 1]
        // double rand_norm = (double)rand() / (double)RAND_MAX;
        double rand_norm = ((double)rand() * (RAND_MAX + 1.0) + (double)rand()) 
           / ((double)RAND_MAX * (RAND_MAX + 1.0) + (double)RAND_MAX);

        // ИСПРАВЛЕНО: xl + случайное смещение
        double x = xl + rand_norm * width;
        double y = ((double)rand() / (double)RAND_MAX) * fmax;
        
        // Проверка, что точка под графиком
        if (y < f(x))
            in_d++;
    }

    // Все вычисления в double, суффикс .0 не обязателен, но полезен для читаемости
    return (double)in_d / (double)n * width * fmax;
}
