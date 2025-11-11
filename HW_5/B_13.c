// Количество четных и нечетных цифр

// Посчитать количество четных и нечетных цифр числа.
// Input format
// Одно целое неотрицательное число.
// Output format
// Два числа через пробел. Количество четных и нечетных цифр в числе.

#include <stdio.h>

int main(int argc, char **argv)
{
    int number;
    int count_n = 0;
    int count_ch = 0;

    if (scanf("%d", &number) != 1)
    {
        printf("Input error.\n");
        return 0;
    }

    while (number > 0)
    {
        int tmp = number % 10;
        if (tmp % 2 == 0)
        {
            count_ch++;
            ;
        }
        else
        {
            count_n++;
        }
        number /= 10;
    }

    printf("%d %d\n", count_ch, count_n);
    return 0;
}
