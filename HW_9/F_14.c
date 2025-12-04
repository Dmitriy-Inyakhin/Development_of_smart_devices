// F_14.c
// Сумма в интервале
// Составить функцию которая возвращает сумму элементов в заданном отрезке 
// [from, to] для массива (границы чисел от 4 до 6, не индексы массива).
// Прототип функции int sum_between_ab(int from, int to, int size, int a[])
// Input format
//     Функция принимает концы отрезка from и to, размер массива, массив целых чисел
// Output format
//     Функция возвращает сумму элементов в интервале [from, to]
// Examples
// Input
//     4 6 1 2 3 4 5 6 7 8 9 10
// Output
//     15
// Input
//     6 4 1 2 3 4 5 6 7 8 9 10
// Output
//     15

#include <stdio.h>
#include <limits.h>

#define MAX_SIZE 12
int sum_between_ab(int from, int to, int size, int a[]) {
    // Нормализуем границы интервала: from ≤ to
    if (from > to) {
        int temp = from;
        from = to;
        to = temp;
    }

    int sum = 0;
    for (int i = 0; i < size; ++i) {
        if (a[i] >= from && a[i] <= to) {
            sum += a[i];
        }
    }
    return sum;
}

void print_array(int size, int ar[])
{
    for (int i = 0; i < size; ++i)
    {
        if (i > 0)
        {
            putchar(' ');
        }
        printf("%d", ar[i]);
    }
    putchar('\n');
}

int main(int argc, char **argv)
{
    int var[MAX_SIZE] = {0};

    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (scanf("%d", &var[i]) != 1)
        {
            fprintf(stderr, "Input error!\n");
            return 1;
        }
    }

    print_array(MAX_SIZE, var);
    printf("%d\n", sum_between_ab(4, 6, MAX_SIZE, var));
    print_array(MAX_SIZE, var);
}
//  1 2 3 4 5 6 7 8 9 10