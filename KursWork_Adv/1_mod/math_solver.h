#ifndef MATH_SOLVER_H
#define MATH_SOLVER_H

#include <math.h>

/* 
 * Тип указателя на функцию одной переменной 
 */
typedef double (*func_t)(double);

/*
 * Вычисляет корень уравнения f(x) = g(x) на отрезке [a, b].
 * Использует комбинированный метод (Ньютон + половинное деление).
 * 
 * @param f    Левая часть уравнения
 * @param g    Правая часть уравнения
 * @param df   Производная f (для метода Ньютона)
 * @param dg   Производная g (для метода Ньютона)
 * @param a    Левая граница отрезка
 * @param b    Правая граница отрезка
 * @param eps1 Требуемая точность
 * @param iter_count Указатель на переменную для записи числа итераций
 * @return     Приближенное значение корня x
 */
double root(func_t f, func_t g, func_t df, func_t dg, 
            double a, double b, double eps1, int *iter_count);

/*
 * Вычисляет определенный интеграл от функции func на [a, b].
 * Использует адаптивное правило Симпсона.
 *
 * @param func Подынтегральная функция
 * @param a    Нижний предел
 * @param b    Верхний предел
 * @param eps2 Требуемая точность
 * @return     Значение интеграла
 */
double integral(func_t func, double a, double b, double eps2);

/* 
 * Функции кривых и их производные 
 */
double f1(double x);
double f2(double x);
double f3(double x);

double df1(double x);
double df2(double x);
double df3(double x);

#endif /* MATH_SOLVER_H */