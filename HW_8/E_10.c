// E_10.c
// Циклический сдвиг массива вправо на 4
// Считать массив из 12 элементов и выполнить циклический
// сдвиг ВПРАВО на 4 элемента.
// Input format
//     12 целых чисел через пробел
// Output format
//     12 целых чисел через пробел
// Examples
// Input
//     4  -5   3  10  -4  -6   8 -10   1   0   5   7
// Output
//     1   0   5   7   4  -5   3  10  -4  -6   8 -10
// Input
//     1 2 3 4 5 6 7 8 9 10 11 12
// Output
//     9 10 11 12 1 2 3 4 5 6 7 8

// E_10.c
// Циклический сдвиг массива вправо на 4

#include <stdio.h>

#define SIZE 12
#define SHIFT 4

// Циклический сдвиг вправо на k позиций
// Использует временный буфер размера k
void rotate_right(int arr[], int n, int k)
{
    if (n <= 1 || k % n == 0)
        return;
    k %= n; // обработка k > n

    int buffer[k]; // VLA (C99+), или можно static/alloca/alloca, или malloc

    // 1. Сохраняем последние k элементов
    for (int i = 0; i < k; ++i)
    {
        buffer[i] = arr[n - k + i];
    }

    // 2. Сдвигаем первые n-k элементов вправо на k
    for (int i = n - 1; i >= k; --i)
    {
        arr[i] = arr[i - k];
    }

    // 3. Копируем буфер в начало
    for (int i = 0; i < k; ++i)
    {
        arr[i] = buffer[i];
    }
}

int main(void)
{
    int a[SIZE];

    // Ввод
    for (int i = 0; i < SIZE; ++i)
    {
        if (scanf("%d", &a[i]) != 1)
        {
            fprintf(stderr, "Input error!\n");
            return 1;
        }
    }

    // Сдвигаем вправо на SHIFT
    rotate_right(a, SIZE, SHIFT);

    // Вывод
    for (int i = 0; i < SIZE; ++i)
    {
        if (i)
            putchar(' ');
        printf("%d", a[i]);
    }
    putchar('\n');

    return 0;
}