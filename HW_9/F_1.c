// F_1.c
// Сортировка по взрастанию

// Написать только одну функцию, которая сортирует массив
// по возрастанию. Необходимо реализовать только одну функцию,
// всю программу составлять не надо.
// Строго согласно прототипу. Имя функции и все аргументы
// должны быть: void sort_array(int size, int a[]).
// Всю программу загружать не надо, только одну эту функцию.
// Можно просто закомментировать текст всей программы, кроме
// данной функции.
// Input format
//     Функция принимает на вход, первый аргумент - размер массива,
// второй аргумент - адрес нулевого элемента.
// Output format
//     Функция ничего не возвращает. Производит сортировку переданного
// ей массива по возрастанию.

#include <stdio.h>
#define SIZE 20
void print_array(int size, int ar[]);
void sort_array(int size, int ar[]);

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
    sort_array(sizeof(var) / sizeof(var[0]), var);
    print_array(sizeof(var) / sizeof(var[0]), var);
    return 0;
}

void sort_array(int size, int ar[])
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

