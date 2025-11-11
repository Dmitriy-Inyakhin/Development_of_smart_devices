// Наименьшая и наибольшая цифра

// Организовать ввод натурального числа с клавиатуры. Программа
// должна определить наименьшую и наибольшую цифры, которые входят
// в состав данного натурального числа.
// Input format
// Целое неотрицательное число
// Output format
// Две цифры через пробел. Сначала наименьшая цифра числа, затем наибольшая.

#include <stdio.h>

int main(int argc, char **argv)
{
    int number;
    int min = 1000;
    int max = 0;

    if (scanf("%d", &number) != 1)
    {
        printf("Input error.\n");
        return 0;
    }

    while (number > 0)
    {
        int tmp = number % 10;
        if (tmp > max)
        {
            max = tmp;
        }
        if (tmp < min)
        {
            min = tmp;
        }
        number /= 10;
    }

    printf("%d %d\n", min, max);
    return 0;
}
