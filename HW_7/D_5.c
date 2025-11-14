/*
D_5.c
В двоичную систему
Перевести натуральное число в двоичную систему счисления. Необходимо реализовать рекурсивную функцию.
Формат входных данных
    Целое не отрицательное число в десятичной системе счисления
Формат результата
    Целое число в двоичной системе счисления
*/
#include <stdio.h>

void num_to_bynary(int);

int main(int argc, char **argv)
{
    int n = 0;
    if (scanf("%d", &n) != 1 || n < 0)
    {
        printf("Input error.");
        return 0;
    }

    num_to_bynary(n);
    printf("\n");
    return 0;
}

void num_to_bynary(int num)
{
    if(num == 0)
    {
        printf("%d", 0);
        return;
    }
    if(num >0)
    {
        num_to_bynary(num/2);
        printf("%s", (num % 2) ? ("1") : ("0"));
    }
    
}