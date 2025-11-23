// D_1.c
// Среднее арифметическое чисел
// Ввести c клавиатуры массив из 5 элементов, найти среднее
// арифметическое всех элементов массива.
// Input format
//     5 целых не нулевых чисел через пробел
// Output format
//     Одно число в формате "%.3f"

#include <stdio.h>
#define SIZE 5

int main(int args, char **argv)
{
    int var[SIZE] = {0};
    double res = 0;

    for (int i = 0; i < SIZE; i++)
    {
        if (scanf("%d", &var[i]) != 1)
        {
            fprintf(stderr, "Input error!\n");
            return 0;
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        res += var[i];
    }

    printf("%.3f\n", res / (double)SIZE);
    return 0;
}