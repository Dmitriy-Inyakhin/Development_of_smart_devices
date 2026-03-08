

#ifndef MATH_LIB_H
#define MATH_LIB_H

#include <stddef.h>
#include "run_menu.h"

/* ---- Тип функции для передачи в численные методы ---- */
typedef double (*function)(double);

/* ---- Прототипы базовых функций уравнений ---- */
double f1(double x);
double f2(double x);
double f3(double x);

/* ---- Функция f_zero -функция-заглушка, которая всегда возвращает 0.0.
*       Используется как безопасная альтернатива NULL для режима
*       "функции с нулем" (function_id = 3) ---- */
double f_zero(double x);

/* ---- Прототипы производных (для метода Ньютона) ---- */
double df1(double x);
double df2(double x);
double df3(double x);

/* ---- Вспомогательные функции ---- */

/* ---- Функция get_function_by_id возвращает указатель на целевую 
        функцию по её идентификатору из AppState. ---- */
function get_function_by_id(int id);     

/* ---- Функция get_derivative_by_id возвращает указатель на производную 
        функции по её идентификатору ---- */            
function get_derivative_by_id(int id);               
/* ---- Функция f_diff вычисляет разность значений двух функций 
*       в заданной точке: f1(x) - f2(x).
*       Используется для поиска точки пересечения графиков: корень уравнения
*       f_diff(f1, f2, x) = 0 соответствует решению f1(x) = f2(x). ---- */
double f_diff(function f_1, function f_2, double x); 

/* ---- Функция signFunc определяет знак значения функции в 
*       заданной точке ---- */ 
int signFunc(double x, function f);                  

/* ---- Численные методы: поиск корня (базовые) ---- */

/* ---- Функция rootFindLineSearch реализует метод линейного 
*       поиска корня функции на отрезке [xl, xr] ---- */ 
double rootFindLineSearch(double xl, double xr, double eps, function f_1, function f_2);

/* ---- Функция rootFindDiv2 реализует метод деления отрезка 
*       пополам (бисекции) для поиска корня ---- */ 
double rootFindDiv2(double xl, double xr, double eps, function f_1, function f_2);

/* ---- Функция rootFindChord реализует метод хорд (секущих) 
*       для поиска корня функции ---- */ 
double rootFindChord(double xl, double xr, double eps, function f_1, function f_2);

/* ---- Функция rootFindTangent реализует метод Ньютона 
*       (касательных) для поиска корня функции ---- */
double rootFindTangent(double xn, double eps, function f, function df);

/* ---- Численные методы: интегрирование (базовые) ---- */

/* ---- Функция calcIntegralSquare вычисляет определённый 
*       интеграл методом прямоугольников (левые) ---- */ 
double calcIntegralSquare(double xl, double xr, size_t n, function f);

/* ---- Функция calcIntegralTrap ычисляет определённый 
*       интеграл методом трапеций ---- */ 
double calcIntegralTrap(double xl, double xr, size_t n, function f);

/* ---- Функция calcIntegralSimpson вычисляет определённый 
*       интеграл методом Симпсона (парабол) ---- */
double calcIntegralSimpson(double xl, double xr, size_t n, function f);

/* ---- Функция calcIntegralMonteCarlo вычисляет определённый 
*       интеграл методом Монте-Карло ---- */ 
double calcIntegralMonteCarlo(double xl, double xr, double fmax, size_t n, function f);

/* ---- Универсальные обертки с использованием AppState ---- */

/* ---- Функция find_root_by_state универсальная обёртка 
*       для поиска корня с параметрами из AppState.
*       Автоматически выбирает метод расчёта на основе 
*       state->method_id ---- */ 
double find_root_by_state(AppState *state);                 /* Поиск корня с выбором метода из state */

/* ---- Функция calc_area_by_state универсальная обёртка 
*       для вычисления интеграла с параметрами из AppState.
*       Автоматически выбирает метод интегрирования на основе 
*       state->method_square ---- */ 
double calc_area_by_state(AppState *state); /* Интегрирование с выбором метода из state */

/* ---- Функция verify_root_by_state обёртка для verifyRoot 
*       с выводом имени метода из state ---- */ 
void verify_root_by_state(AppState *state, double root, function f);    /* Проверка найденного корня */

#endif /* MATH_LIB_H */
