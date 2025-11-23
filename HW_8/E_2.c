// E_2.c
// Найти минимум
// Ввести c клавиатуры массив из 5 элементов, найти минимальный из них.
// Input format
//     5 целых чисел через пробел
// Output format
//     Одно единственное целое число

#include <stdio.h>
#define SIZE 5

int main(int args, char **argv)
{
    int var[SIZE] = {0};
    int min = 0;

    for (int i = 0; i < SIZE; i++)
    {
        if (scanf("%d", &var[i]) != 1)
        {
            fprintf(stderr, "Input error!\n");
            return 0;
        }
    }
    min = var[0];
    for (int i = 0; i < SIZE; i++)
    {
        if (min > var[i])
        {
            min = var[i];
        }
    }

    printf("%d\n", min);
    return 0;
}