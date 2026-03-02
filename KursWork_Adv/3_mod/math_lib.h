/*
 * Файл: math_lib.h
 * Описание: Заголовочный файл для математических функций и численных методов.
 */

#ifndef MATH_LIB_H
#define MATH_LIB_H

#include <math.h>
#include <stdlib.h>

/* --- Реализация функций уравнений --- */
double f1(double x);
double f2(double x);
double f3(double x);

/* --- Реализация производных --- */
double df1(double x);
double df2(double x);
double df3(double x);

/* --- Определение ссылочной функции --- */
typedef double (*function)(double);

/* === Знак функции (принимает функцию как параметр) === */
int signFunc(double x, function f);

/* === Разность функций для поиска пересечения === */
double f_diff(double x);

/* --- Линейный поиск--- */
float rootFindLineSearch(double xl, double xr, double eps, function f);

/* === Метод деления отрезка пополам v2 (с проверкой границ) === */
double rootFindDiv2(double xl, double xr, double eps, function f);

/* === Метод хорд (доработан) === */
double rootFindChord(double xl, double xr, double eps, function f);

/* === Проверка: подставляем найденный корень обратно === */
void verifyRoot(const char *methodName, double root, function f);


/* --- Метод касательных (Ньютона) --- */
float rootFindTangent(float xn, float eps, function f, function df);

/* --- Комбинированный метод --- */
float rootFindCombine(float xl, float xr, float eps, function f, function df, function ddf);



/* --- Нахождение площадей фигур --- */

/* --- Вычисление интеграла методом прямоугольника --- */
/* --- Формула для сетки --- */
float calcIntegralSquare(double xl, double xr, size_t n, function f);

/* --- Вычисление интеграла методом трапеций --- */
double calcIntegralTrap(double xl, double xr, size_t n, function f);

/* --- Вычисление интеграла по методу Симпсона --- */
double calcIntegralSimpson(double xl, double xr, size_t n, function f);

/* --- Вычисление интеграла с помощью метода Монте-Карло --- */
double calcIntegralMonteCarlo(double xl, double xr, double fmax, size_t n, function f);

#endif
