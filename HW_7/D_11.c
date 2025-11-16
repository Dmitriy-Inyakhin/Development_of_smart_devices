// D_11.c
// Количество 1

// Дано натуральное число N. Посчитать количество «1» в двоичной записи числа.
// Input format
//     Натуральное число
// Output format
//     Целое число - количество единиц в двоичной записи числа.

#include <stdio.h>

int count_ones(int n);

int main(int argc, char **argv)
{
    int n = 0;
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        fprintf(stderr, "Input error.\n");
        return 1;
    }

    printf("%d\n", count_ones(n));
    return 0;
}

int count_ones(int n)
{
    if (n == 0)
    {
        return 0;
    }
    return (n & 1) + count_ones(n >> 1);
}