// Вычислить sin

// Составить функцию, которая вычисляет синус как сумму ряда (с точностью 0.001)
// sin(x) = x - x3/3! + x5/5! - x7/7! + ...(x в радианах)
// float sinus(float x)
// Input format
// Одно число от 0 до 90
// Output format
// Вещественное число в формате "%.3f"

#include <stdio.h>
#include <math.h>

float sinus(float x_deg)
{
    // Перевод градусов в радианы
    const float PI = 3.14159265358979323846f;
    float x = x_deg * PI / 180.0f;

    float term = x;   // первый член ряда: x
    float sum = term; // сумма начинается с x
    int n = 1;        // номер текущего члена (начинаем со второго)

    // Пока |term| >= 0.001 — продолжаем
    while (fabsf(term) >= 0.001f)
    {
        // Вычисляем следующий член через предыдущий
        term = -term * x * x / ((2 * n) * (2 * n + 1));
        sum += term;
        n++;
    }

    return sum;
}

int main()
{
    float x_deg;
    scanf("%f", &x_deg);
    printf("%.3f\n", sinus(x_deg));
    return 0;
}