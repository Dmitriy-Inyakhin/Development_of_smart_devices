/* 
D_7.c
От N до 1
Составить рекурсивную функцию, печать всех чисел от N до 1.
Формат входных данных
    Одно натуральное число
Формат результата
    Последовательность целых чисел от введенного числа до 1, через пробел.
*/

#include <stdio.h>

void print_n(int);

int main(int argc, char **argv)
{
    int n =0;
    if(scanf("%d", &n) != 1 || n < 0)
    {
        printf("Input error.");
        return 0;
    }

    print_n(n);
    printf("\n");
    return 0;
}

void print_n(int n)
{
    if(n>0)
    {
        printf("%d ", n);
        print_n(n-1);
    }
    
    
}