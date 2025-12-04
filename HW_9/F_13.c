// F_13.c
// В заданном интервале
// Составить функцию которая возвращает количество элементов на заданном 
// отрезке [from, to] для массива.
// Прототип функции int count_between(int from, int to, int size, int a[])
// Формат входных данных
//     Функция принимает значения концов отрезка from и to, размер массива, 
// массив целых чисел.
// Формат результата
//     Функция возвращает целое число - количество числе в интервале [from, to]
// Примеры
// Входные данные
//     4 6 1 2 3 4 5 6 7 8 9 10
// Результат работы
//     3

#include <stdio.h>
#include <limits.h>

#define MAX_SIZE 12
int count_between(int from, int to, int size, int a[]) {
    // Нормализуем границы интервала: from ≤ to
    if (from > to) {
        int temp = from;
        from = to;
        to = temp;
    }

    int res = 0;
    for (int i = 0; i < size; ++i) {
        if (a[i] >= from && a[i] <= to) {
            res++;
        }
    }
    return res;
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
    printf("%d\n", count_between(1, 2, MAX_SIZE, var));
    print_array(MAX_SIZE, var);
}
//  4 6 1 2 3 4 5 6 7 8 9 10