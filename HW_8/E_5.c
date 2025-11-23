// E_5.c
// Сумма положительных элементов
// Считать массив из 10 элементов и посчитать сумму положительных
// элементов массива.
// Input format
//     10 целых чисел через пробел
// Output format
//     Одно целое число - сумма положительных элементов массива
// Examples
// Input
//     4 -5 3 10 -4 -6 8 -10 1 0
// Output
//     26
// Input
//     1 -2 3 -4 5 -6 7 -8 9 0
// Output
//     25

#include <stdio.h>
#define SIZE 10

int main(int args, char **argv)
{
    int var[SIZE] = {0};
    int res = 0;

    for (int i = 0; i < SIZE; i++)
    {
        if (scanf("%d", &var[i]) != 1)
        {
            fprintf(stderr, "Input error!\n");
            return 1;
        }
    }
    
    for (int i = 0; i < SIZE; i++)
    {
        if (var[i] > 0)
        {
            res += var[i];
        }
    }
    printf("%d\n", res);

    return 0;
}