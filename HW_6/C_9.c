// Факториал

// Составить функцию вычисления N!. Использовать ее при вычислении
// факториала int factorial(int n)

// Input format
// Целое положительное число не больше 20
// Output format
// Целое положительное число

#include <stdio.h>

int factorial(int n)
{
    int res = 1;
    for (int i = 1; i <= n; i++)
    {
        res *= i;
    }
    return res;
}

int main(int argc, char **argv)
{
    int number;

    if (scanf("%d", &number) != 1 || number > 20 || number <= 0)
    {
        printf("Input error.\n");
        return 0;
    }

    printf("%d\n", factorial(number));
    return 0;
}