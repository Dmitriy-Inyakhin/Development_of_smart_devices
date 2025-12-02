/*
D_4.c
В прямом порядке
Дано натуральное число N. Выведите все его цифры по одной, в прямом порядке, 
разделяя их пробелами
или новыми строками. Необходимо реализовать рекурсивную функцию.
void print_num(int num)
Формат входных данных
    Одно целое неотрицательное число
Формат результата
    Все цифры числа через пробел в прямом порядке
*/
#include <stdio.h>

void print_num(int);

int main(int argc, char **argv)
{
    int n = 0;
    if (scanf("%d", &n) != 1 || n < 0)
    {
        printf("Input error.");
        return 0;
    }

    print_num(n);
    printf("\n");
    return 0;
}

void print_num(int num)
{
    if (num < 10)
    {
        printf("%d ", num);
    }
    else
    {
        print_num(num / 10);
        printf("%d ", num % 10);
    }
}