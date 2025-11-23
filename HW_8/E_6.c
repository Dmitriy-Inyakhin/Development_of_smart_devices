// E_6.c
// Среднее арифметическое массива
// Считать массив из 12 элементов и посчитать среднее 
// арифметическое элементов массива.
// Input format
//     12 целых чисел через пробел
// Output format
//     Среднее арифметическое в формате "%.2f"
// Examples
// Input
//     4 -5 3 10 -4 -6 8 -10 1 0 5 7
// Output
//     1.08
// Input
//     1 2 3 4 5 6 7 8 9 10 11 12
// Output
//     6.50

#include <stdio.h>
#define SIZE 12

int main(int args, char **argv)
{
    double var[SIZE] = {0};
    double res = 0;

    for (int i = 0; i < SIZE; i++)
    {
        if (scanf("%lf", &var[i]) != 1)
        {
            fprintf(stderr, "Input error!\n");
            return 1;
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
            res += var[i];
    }
    printf("%.2f\n", res/(double)SIZE);
    return 0;
}