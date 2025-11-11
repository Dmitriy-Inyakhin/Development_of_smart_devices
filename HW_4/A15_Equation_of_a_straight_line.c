#include <stdio.h>

int main()
{
    double x1, y1, x2, y2;
    scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);

    // Проверка на вертикальную прямую
    if (x1 == x2)
    {
        // Уравнение y = k*x + b невозможно записать
        // Выводим, например, "NO" или специальное сообщение
        printf("The line is vertical\n");
        return 0;
    }

    double k = (y2 - y1) / (x2 - x1);
    double b = y1 - k * x1;

    printf("%.2f %.2f\n", k, b);
    return 0;
}
