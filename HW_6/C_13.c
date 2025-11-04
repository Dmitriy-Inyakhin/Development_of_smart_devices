// Вычислить cos

// Составить функцию, которая вычисляет косинус как сумму ряда (с точностью 0.001)
// cos(x) = 1 - x2/2! + x4/4! - x6/6! + ... (x в радианах)
// float cosinus(float x)
// Input format
// Целое число от 0 до 90
// Output format
// Вещественное число в формате "%.3f"

#include <stdio.h>
#include <math.h>

float cosinus(float x_deg) {
    const float PI = 3.14159265358979323846f;
    float x = x_deg * PI / 180.0f;  // перевод в радианы

    float term = 1.0f;  // первый член: 1
    float sum = term;
    int n = 0;          // номер текущего члена (начинаем с 0)

    // Пока |term| >= 0.001 — продолжаем
    while (fabsf(term) >= 0.001f) {
        n++;
        term = -term * x * x / ((2 * n - 1) * (2 * n));
        sum += term;
    }

    return sum;
}

int main() {
    int x_deg;
    scanf("%d", &x_deg);
    printf("%.3f\n", cosinus(x_deg));
    return 0;
}