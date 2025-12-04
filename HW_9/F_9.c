// F_9.c
// Поменять местами
// Составить только функцию которая в массиве находит максимальный из
// отрицательных элементов и меняет его местами с последним элементом
// массива. Гарантируется, что в массиве только один такой элемент или
// же такой элемент отсутствует. Если отрицательных элементов нет - массив
// не менять.
// Прототип функции: void swap_negmax_last(int size, int a[])
// Input format
//     Функция принимает на вход размер массива и указатель на начало массива. Массив состоит из целых чисел.
// Examples
// Input
//     1 -2 -3 -4 5 6 7 8 9 10
// Output
//     1 10 -3 -4 5 6 7 8 9 -2

#include <stdio.h>
#include <limits.h>

#define MAX_SIZE 10
void swap_negmax_last(int size, int a[])
{
    int max = INT_MIN;
    int count_max = -1;
    for (int i = 0; i < size; i++)
    {
        if (a[i] < 0)
        {
            if (max < a[i])
            {
                max = a[i];
                count_max = i;
            }
        }
    }

    if (count_max != -1)
    {
        int temp = a[count_max];
        a[count_max] = a[size - 1];
        a[size - 1] = temp;
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
    swap_negmax_last(MAX_SIZE, var);
    print_array(MAX_SIZE, var);
}
