// E_8.c
// Инверсия каждой трети
// Считать массив из 12 элементов и выполнить инверсию для каждой трети массива.
// Input format
//     12 целых чисел через пробел
// Output format
//     12 целых чисел через пробел
// Examples
// Input
//     4 -5 3 10 -4 -6 8 -10 1 0 5 7
// Output
//     10 3 -5 4 -10 8 -6 -4 7 5 0 1
// Input
//     1 2 3 4 5 6 7 8 9 10 11 12
// Output
//     4 3 2 1 8 7 6 5 12 11 10 9

// Инверсия каждой трети

#include <stdio.h>
#define SIZE 12

// Вспомогательная функция: развернуть подмассив [l, r] включительно
void reverse(int arr[], int l, int r)
{
    while (l < r)
    {
        int tmp = arr[l];
        arr[l] = arr[r];
        arr[r] = tmp;
        l++;
        r--;
    }
}

int main()
{
    int var[SIZE];

    // Ввод
    for (int i = 0; i < SIZE; i++)
    {
        if (scanf("%d", &var[i]) != 1)
        {
            fprintf(stderr, "Input error!\n");
            return 1;
        }
    }

    // Инвертируем каждую треть (по 4 элемента)
    reverse(var, 0, 3);  // 1-я треть: индексы 0..3
    reverse(var, 4, 7);  // 2-я треть: индексы 4..7
    reverse(var, 8, 11); // 3-я треть: индексы 8..11

    // Вывод
    for (int i = 0; i < SIZE; i++)
    {
        if (i > 0)
            printf(" ");
        printf("%d", var[i]);
    }
    printf("\n");

    return 0;
}