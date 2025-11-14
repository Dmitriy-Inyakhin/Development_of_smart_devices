/*
D_3.c
В обратном порядке
Дано целое не отрицательное число N. Выведите все его цифры по одной, в обратном порядке, 
разделяя их пробелами или новыми строками.
Формат входных данных
    Одно не отрицательное целое число
Формат результата
    Последовательность цифр введенного числа в обратном порядке через пробел
*/
#include <stdio.h>

void print_reg(int);

int main(int argc, char **argv)
{
    int n =0;
    if(scanf("%d", &n) != 1 || n < 0)
    {
        printf("Input error.");
        return 0;
    }

    print_reg(n);
    printf("\n");
    return 0;
}

void print_reg(int n)
{
     if (n < 10) {
        printf("%d", n);
    } else {
        printf("%d ", n % 10);
        print_reg(n / 10);
    }
}