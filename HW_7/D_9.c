/*
D_9.c
Дано натуральное число N. Вычислите сумму его цифр. Необходимо составить 
рекурсивную функцию.
int sum_digits(int n)

Формат входных данных
    Одно натуральное число.
Формат результата
    Целое число - сумма цифр введенного числа.
*/

#include <stdio.h>

int sum_digits(int);

int main(int argc, char **argv)
{
    int n = 0;
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Input error.");
        return 0;
    }

    printf("%d\n", sum_digits(n));
    return 0;
}

int sum_digits(int n)
{
      
    if (n < 10) {          // базовый случай: одна цифра
        return n;
    }
    return (n % 10) + sum_digits(n / 10);
}

   

#include <stdio.h>

int main() {
    int a, b, c;
    
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        fprintf(stderr, "Ошибка: ожидалось три целых числа.\n");
        return 1; // Ненулевой код возврата — означает ошибку
    }

    int sum = a + b + c;
    int prod = a * b * c;
    double avg = (double)sum / 3.0;

    printf("%d+%d+%d=%d\n", a, b, c, sum);
    printf("%d*%d*%d=%d\n", a, b, c, prod);
    printf("(%d+%d+%d)/3=%.2f\n", a, b, c, avg);

    return 0;
}
