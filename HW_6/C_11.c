//  НОД

//  Составить функцию, которая определяет наибольший общий
//  делитель двух натуральных и привести пример ее использования.
//  int nod(int a, int b)

//  Input format
//  Два целых положительных числа
//  Output format
//  Одно целое число - наибольший общий делитель.

#include <stdio.h>

int nod(int a, int b)
{
    if (b > a)
    {
        int tmp = b;
        b = a;
        a = tmp;
    }
    int r = 1;
    while (r != 0)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main(int argc, char **argv)
{
    int number_1, number_2;

    if (scanf("%d %d", &number_1, &number_2) != 2 || number_1 <= 0 || number_2 <= 0)
    {
        printf("Input error.\n");
        return 0;
    }

    // print_simple(number);
    printf("%d\n", nod(number_1, number_2));
    return 0;
}