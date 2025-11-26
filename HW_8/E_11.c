// E_11.c
// Отсортировать по последней цифре
// Считать массив из 10 элементов и отсортировать его по последней цифре.
// Input format
//     10 целых чисел через пробел
// Output format
//     Этот же массив отсортированный по последней цифре
// Examples
// Input
//     14  25  13  30  76  58  32  11  41  97
// Output
//     30  11  41  32  13  14  25  76  97  58
// Input
//     109 118 100 51 62 73 1007 16 4 555
// Output
//     100 51 62 73 4 555 16 1007 118 109

#include <stdio.h>
#define SIZE 10

void swap(int *a, int *b);
void revers_array(int size, int ar[]);
void buble_max_sort_array(int size, int ar[]);
void buble_min_sort_array(int size, int ar[]);
void buble_sort_array_end_num(int size, int ar[]);
void print_array(int size, int ar[]);

int main(int args, char **argv)
{
    int var[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        if (scanf("%d", &var[i]) != 1)
        {
            fprintf(stderr, "Input error!\n");
            return 0;
        }
    }
    buble_min_sort_array(sizeof(var) / sizeof(var[0]), var);
    print_array(sizeof(var) / sizeof(var[0]), var);
    return 0;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void revers_array(int size, int ar[])
{
    for (int i = 0; i < SIZE / 2; ++i)
    {
        swap(&ar[i], &ar[size - 1 - i]);
    }
    return;
}

void buble_max_sort_array(int size, int ar[])
{
    int i = 0;
    _Bool flag;
    do
    {
        flag = 0;
        for (int j = size - 2; j >= i; j--)
        {
            if (ar[j] > ar[j + 1])
            {
                swap(&ar[j], &ar[j + 1]);
                flag = 1;
            }
        }
        i++;
    } while (flag);
}

void buble_min_sort_array(int size, int ar[])
{
int i = 0;
    _Bool flag;
    do
    {
        flag = 0;
        for (int j = size - 2; j >= i; j--)
        {
            if (ar[j] < ar[j + 1])
            {
                swap(&ar[j], &ar[j + 1]);
                flag = 1;
            }
        }
        i++;
    } while (flag);
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

void buble_sort_array_end_num(int size, int ar[])
{
    int i = 0;
    _Bool flag;
    do
    {
        flag = 0;
        for (int j = size - 2; j >= i; j--)
        {
            if (ar[j]%10 > ar[j + 1]%10)
            {
                swap(&ar[j], &ar[j + 1]);
                flag = 1;
            }
        }
        i++;
    } while (flag);
}