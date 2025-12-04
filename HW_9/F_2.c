// F_2.c
// Четные в начало

// Написать только одну функцию, которая ставит в начало массива 
// все четные элементы, а в конец – все нечетные. Не нарушайте 
// порядок следования чисел между собой. Строго согласно прототипу:.
// void sort_even_odd(int n, int a[])
// Input format
//     Функцийя принмате на вход целые числа
// Output format
//     Отсортированный исходный массив
// Examples
// Input
//     20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
// Output
//     20 18 16 14 12 10 8 6 4 2 19 17 15 13 11 9 7 5 3 1
// Input
//     1 0 1 0 1
// Output
//     0 0 1 1 1

#include <stdio.h>
#include <stdlib.h>
#define SIZE 21
void print_array(int size, int ar[]);
void sort_even_odd(int n, int ar[]);

int main(int args, char **argv)
{
    int var[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        if (scanf("%d", &var[i]) != 1)
        {
            fprintf(stderr, "Input error!\n");
            return 1;
        }
    }
    sort_even_odd(sizeof(var) / sizeof(var[0]), var);
    print_array(sizeof(var) / sizeof(var[0]), var);
    return 0;
}

void sort_even_odd(int n, int ar[])
{
    int i = 0;
    _Bool flag;
    do
    {
        flag = 0;
        for (int j = n - 2; j >= i; j--)
        {
            if (abs(ar[j])%2 > abs(ar[j + 1])%2)
            {
                int temp = ar[j];
                ar[j] = ar[j + 1];
                ar[j + 1] = temp;
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

