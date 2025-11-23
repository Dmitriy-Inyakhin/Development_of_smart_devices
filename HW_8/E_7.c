// E_7.c
// Инверсия половинок
// Считать массив из 10 элементов и выполнить инверсию
// отдельно для 1-ой и 2-ой половин массива. Необходимо
// изменить считанный массив и напечатать его одним циклом.
// Input format
//     10 целых элементов массива через пробел.
// Output format
//     10 целых элементов массива через пробел.
// Examples
// Input
//     4 -5 3 10 -4 -6 8 -10 1 0
// Output
//     -4 10 3 -5 4 0 1 -10 8 -6
// Input
//     1 2 3 4 5 6 7 8 9 10
// Output
//     5 4 3 2 1 10 9 8 7 6

#include <stdio.h>
#define SIZE 10

int main(int args, char **argv)
{
    int var[SIZE] = {0};
    int res = 0;
    int temp[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        if (scanf("%d", &var[i]) != 1)
        {
            fprintf(stderr, "Input error!\n");
            return 1;
        }
    }

    for (int i = 0; i < SIZE / 2; i++)
    {
        temp[SIZE / 2 - 1 - i] = var[i];
    }
    int count = 0;
    for (int i = SIZE - 1; i >= SIZE / 2; i--)
    {
        temp[SIZE / 2 + count++] = var[i];
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", temp[i]);
    }
    printf("\n");
    return 0;
}