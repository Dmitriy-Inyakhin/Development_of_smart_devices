// D_10.c
// Проверка на простоту

// Дано натуральное число n ≥ 1. Проверьте, является ли оно простым.
// Программа должна вывести слово YES, если число простое или NO в
// противном случае. Необходимо составить рекурсивную функцию и использовать ее.
// int is_prime(int n, int delitel)

// Input format
//     Натуральное число
// Output format
//     YES или NO

#include <stdio.h>

int is_prime(int n, int delitel);

int main(int argc, char **argv)
{
    int n = 0;
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Input error.");
        return 0;
    }
    if (n == 1)
    {
        printf("NO\n");
        return 0;
    }
    if (n == 2)
    {
        printf("YES\n");
        return 0;
    }
    printf("%s\n", (is_prime(n, n-1)) ? ("YES") : ("NO"));
    return 0;
}

int is_prime(int n, int delitel)
{
    if ((delitel) == 1)
    {
        return 1;
    }
    if (n % delitel == 0)
    {
        return 0;
    }
    is_prime(n, delitel - 1);
}