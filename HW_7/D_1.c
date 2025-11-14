/* 
D_1.c
Печать от 1 до N
    Составить рекурсивную функцию, печать всех чисел от 1 до N
Формат входных данных:
    Одно натуральное число
Формат результата:
    Последовательность чисел от 1 до введенного числа
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
    if(n>1)
    {
        print_n(n-1);
    }
    printf("%d ", n);
}