// E_4.c
// Два максимума
// Считать массив из 10 элементов и найти в нем два максимальных
// элемента и напечатать их сумму.
// Input format
//     10 целых чисел через пробел.
// Output format
//     Сумма двух максимальных элементов.
// Examples
// Input
// 4 -5 3 10 -4 -6 8 -10 1 0
// Output
// 18
// Input
// 1 2 3 4 5 6 7 8 9 10
// Output
// 19

#include <stdio.h>
#define SIZE 10

int main(int args, char **argv)
{
    int var[SIZE] = {0};
    int max_1;
    int max_2;

    for (int i = 0; i < SIZE; i++)
    {
        if (scanf("%d", &var[i]) != 1)
        {
            fprintf(stderr, "Input error!\n");
            return 0;
        }
    }

    // Инициализация: пусть max1 >= max2
    if (var[0] > var[1])
    {
        max_1 = var[0];
        max_2 = var[1];
    }
    else
    {
        max_1 = var[1];
        max_2 = var[0];
    }

    // Проход по остальным элементам
    for (int i = 2; i < SIZE; i++)
    {
        if (var[i] > max_1)
        {
            max_2 = max_1;  // старый максимум → второй
            max_1 = var[i]; // новый максимум
        }
        else if (var[i] > max_2)
        {
            max_2 = var[i]; // обновляем второй максимум
        }
    }

    printf("%d\n", max_1 + max_2);
    return 0;
}
