// Числа Фибоначчи

// Вывести на экран ряд чисел Фибоначчи, состоящий из n элементов.
// Числа Фибоначчи – это элементы числовой последовательности
// 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, …, в которой каждое
// последующее число равно сумме двух предыдущих.
// Input format
// Одно натуральное число
// Output format
// Ряд чисел Фибоначчи через пробел

#include <stdio.h>

int main(int argc, char **argv)
{
    int number;
    int new = 0;
    int old = 1;
    int count = 0;

    if (scanf("%d", &number) != 1)
    {
        printf("Imput error.\n");
        return 0;
    }

    for (int i = 0; i < number; i++)
    {
        count = new + old;
        old = new;
        new = count;

        printf("%d ", count);
    }
    printf("\n");
    return 0;
}