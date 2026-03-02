#include <stdio.h>
#include <math.h>

typedef double (*function)(double);

/* === Функции уравнений === */
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

/* === Разность функций для поиска пересечения === */
double f_diff(double x)
{
    return f1(x) - f3(x); /* Ищем где f1(x) = f3(x) */
}

/* === Знак функции (исправлено: принимает функцию как параметр) === */
int signFunc(double x, function f)
{
    double val = f(x);
    return val == 0 ? 0 : (val < 0 ? -1 : 1);
}

/* === Метод линейного поиска === */
double rootFindLineSearch(double xl, double xr, double eps, function f)
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

/* === Метод деления пополам (исправлено) === */
double rootFindDiv(double xl, double xr, double eps, function f)
{
    int stepcount = 0;
    double xm;

    /* Проверка: есть ли корень на отрезке */
    if (f(xl) * f(xr) > 0)
    {
        printf("ВНИМАНИЕ: На отрезке может не быть корня!\n");
    }

    while (fabs(xr - xl) > eps)
    {
        stepcount++;
        xm = (xl + xr) / 2.0;

        if (f(xm) == 0)
        {
            printf("Div: %d шагов\n", stepcount);
            return xm;
        }

        if (f(xl) * f(xm) < 0) /* Корень в левой половине */
            xr = xm;
        else /* Корень в правой половине */
            xl = xm;
    }
    printf("Div: %d шагов\n", stepcount);
    return (xl + xr) / 2.0;
}

/* === Метод деления пополам v2 (с проверкой границ) === */
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

/* === Метод хорд (исправлено) === */
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

int main()
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

    // double r2 = rootFindDiv(xl, xr, eps, f_diff);
    double r2 = rootFindDiv(xl, xr, eps, f2);
    verifyRoot("Div", r2, f_diff);

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