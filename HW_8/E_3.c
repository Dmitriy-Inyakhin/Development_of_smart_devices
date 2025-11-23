// E_3.c
// Максимум и минимум
// Считать массив из 10 элементов и найти в нем максимальный
// и минимальный элементы и их номера.
// Input format
//     10 целых чисел через пробел
// Output format
//     4 целых числа через пробел: номер максимума, максимум,
//     номер минимума, минимум.

#include <stdio.h>
#define SIZE 10

int main(int args, char **argv)
{
    int var[SIZE] = {0};
    int min;
    int count_min = 1;
    int max;
    int count_max = 1;

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
            count_min = i + 1;
        }
    }

    max = var[0];
    for (int i = 0; i < SIZE; i++)
    {
        if (max < var[i])
        {
            max = var[i];
            count_max = i + 1;
        }
    }

    // printf("%d %d\n", count_min, min);

    printf("%d %d %d %d\n", count_max, max, count_min, min);
    return 0;
}
