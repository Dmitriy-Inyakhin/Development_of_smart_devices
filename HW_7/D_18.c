// D_18.c
// Цифры слева направо
// Написать рекурсивную функцию и используя ее решить задачу. 
// Напечатать цифры введенного натурального числа в порядке 
// следования(слева направо) через пробел.
// void print_digits(int n)

// Input format
//     Натуральное число
// Output format
//     Последовательность цифр в слева направо через пробел

#include <stdio.h>

void print_digits(int);

int main(int argc, char **argv)
{
    int n = 0;
    if (scanf("%d", &n) != 1 || n < 0)
    {
        printf("Input error.");
        return 0;
    }

    print_digits(n);
    printf("\n");
    return 0;
}

void print_digits(int n)
{
    if (n < 10)
    {
        printf("%d ", n);
    }
    else
    {
        print_digits(n / 10);
        printf("%d ", n % 10);
    }
}