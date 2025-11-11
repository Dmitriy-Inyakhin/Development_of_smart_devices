// Сумма от 1 до N
// Составить функцию, которая определяет сумму всех чисел от 1 до N и привести
// пример ее использования.
// Input format
// Одно целое положительное число N
// Output format
// Целое число - сумма чисел от 1 до N
#include <stdio.h>

int main(int argc, char **argv)
{
    int number = 0;
    int res = 0;

    if (scanf("%d", &number) != 1)
    {
        printf("Input error.");
        return 0;
    }

    for (int i = 0; i <= number; i++)
    {
        res += i;
    }
    printf("%d\n", res);
    return 0;
}