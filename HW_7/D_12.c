// D_12.c
// Монотонная последовательность
// Дана монотонная последовательность, в которой каждое
// натуральное число k встречается ровно k раз: 1, 2, 2, 3, 3, 3, 4, 4, 4, 4,…
// Выведите первые n членов этой последовательности.
// Input format
//     Натуральное число.
// Output format
//     Последовательность целых чисел.

#include <stdio.h>

void print_n(int);

int main(int argc, char **argv)
{
    int n = 0;
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        fprintf(stderr, "Input error.\n");
        return 1;
    }

    print_n(n);
    printf("\n");
    return 0;
}

void print_n(int n)
{
    static int count = 0;
    static int predel = 0;
    predel = n;
    if (n > 1)
    {
        print_n(n - 1);
    }
    for (int i = 1; i <= n; i++)
    {
        if (count++ < predel)
        {
            return;
        }
        printf("%d ", n);
    }
}