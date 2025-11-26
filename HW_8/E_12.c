// E_12.c
// По убыванию и по возрастанию
// Считать массив из 10 элементов и отсортировать первую 
// половину по возрастанию, а вторую – по убыванию.
// Input format
//     10 целых чисел через пробел
// Output format
//     Исходный массив. Первая часть отсортирована по 
//     возрастанию, вторая половина по убыванию.
// Examples
// Input
//     14  25  13  30  76  58  32  11  41  97
// Output
//     13  14  25  30  76  97  58  41  32  11
// Input
//     5 4 3 2 1 6 7 8 9 10
// Output
//     1 2 3 4 5 10 9 8 7 6

#include <stdio.h>
#define SIZE 10

void swap(int *a, int *b);
void revers_array(int size, int ar[]);
void buble_max_sort_array(int size, int ar[]);
void buble_min_sort_array(int size, int ar[]);
void buble_sort_array_end_num(int size, int ar[]);
void sort_half_asc_half_desc(int size, int ar[]);
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
    sort_half_asc_half_desc(sizeof(var) / sizeof(var[0]), var);
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

void sort_half_asc_half_desc(int size, int ar[]) {
    if (ar == NULL || size <= 0) {
        return;
    }

    int mid = size / 2;

    // Сортируем первую половину [0, mid) по возрастанию (сортировка выбором)
    for (int i = 0; i < mid; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < mid; ++j) {
            if (ar[j] < ar[min_idx]) {
                min_idx = j;
            }
        }
        swap(&ar[i], &ar[min_idx]);  
    }

    // Сортируем вторую половину [mid, size) по убыванию
    for (int i = mid; i < size; ++i) {
        int max_idx = i;
        for (int j = i + 1; j < size; ++j) {
            if (ar[j] > ar[max_idx]) {
                max_idx = j;
            }
        }
        swap(&ar[i], &ar[max_idx]);  
    }
}