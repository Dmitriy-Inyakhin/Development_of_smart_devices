/*
D_2.c
Сумма чисел от 1 до N
    Составить рекурсивную функцию, которая определяет сумму всех чисел от 1 до N
Формат входных данных:
    Одно натуральное число
Формат результата:
    Сумма чисел от 1 до введенного числа
*/
#include <stdio.h>

int summ_n(int);

int main(int argc, char **argv)
{
    int n = 0;
    if (scanf("%d", &n) != 1 || n < 0)
    {
        printf("Input error.");
        return 0;
    }

    printf("%d\n", summ_n(n));
    return 0;
}

int summ_n(int n)
{
    int res = 0;
    if (n < 1)
    {
        return 0;
    }
    return n + summ_n(n-1);
}