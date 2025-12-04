// F_12.c
// Поменять местами
// Составить функцию которая меняет в массиве минимальный и
// максимальный элемент местами.
// Прототип функции void change_max_min(int size, int a[])
// Input format
//     Функция принимает на вход размер массива и массив чисел типа int
// Output format
//     Функция не возвращает значения, измененный массив сохраняется на месте исходного.
// Examples
// Input
//     1 2 3 4 5 6 7 8 9 10
// Output
//     10 2 3 4 5 6 7 8 9 1

#include <stdio.h>
#include <limits.h>

#define MAX_SIZE 10
void change_max_min(int size, int a[])
{
    int max = INT_MIN;
    int min = INT_MAX;
    int count_max = -1;
    int count_min = -1;

    for (int i = 0; i < size; i++)
    {
        if (max < a[i])
        {
            max = a[i];
            count_max = i;
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (min > a[i])
        {
            min = a[i];
            count_min = i;
        }
    }
    if (count_max != -1)
    {
        int temp = a[count_max];
        a[count_max] = a[count_min];
        a[count_min] = temp;
    }
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
    change_max_min(MAX_SIZE, var);
    print_array(MAX_SIZE, var);
}
