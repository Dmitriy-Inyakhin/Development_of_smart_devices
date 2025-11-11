// Простые множители

// Составить функцию, печать всех простых множителей числа.
// Использовать ее для печати всех простых множителей числа.
// void print_simple(int n)

// Input format
// Целое положительное число.
// Output format
// Последовательность всех простых множителей данного числа
// в порядке возрастания.

#include <stdio.h>

void print_simple(int n)
{
    int divide = 2;
    while (n > 1)
    {
        if (n % divide == 0)
        {
            printf("%d ", divide);
            n /= divide;
        }
        else
        {
            divide++;
        }
    }
}

int main(int argc, char **argv)
{
    int number;

    if (scanf("%d", &number) != 1 || number <= 0)
    {
        printf("Input error.\n");
        return 0;
    }

    print_simple(number);
    printf("\n");
    return 0;
}