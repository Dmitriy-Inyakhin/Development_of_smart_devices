// E_9.c
// Циклический сдвиг массива вправо
// Считать массив из 10 элементов и выполнить циклический сдвиг ВПРАВО на 1.
// Input format
//     10 целых чисел через пробел
// Output format
//     10 целых чисел через пробел сдвинутых вправо на 1 элемент циклически
// Examples
// Input
//     4   -5   3  10  -4  -6  8  -10  1  0
// Output
//     0   4   -5   3  10  -4  -6  8  -10  1
// Input
//     1 2 3 4 5 6 7 8 9 10
// Output
//     10 1 2 3 4 5 6 7 8 9

#include <stdio.h>
#define SIZE 10

int main(int args, char **argv)
{
    int var[SIZE] = {0};
    int last=0;

    for (int i = 0; i < SIZE; i++)
    {
        if (scanf("%d", &var[i]) != 1)
        {
            fprintf(stderr, "Input error!\n");
            return 1;
        }
    }

    last = var[SIZE-1];
    for(int i = SIZE-1; i>0; i--)
    {
        var[i]=var[i-1];
    }
    var[0]=last;
    
    // Вывод
    for (int i = 0; i < SIZE; i++)
    {
        if (i > 0)
            putchar(' ');
        printf("%d", var[i]);
    }
    putchar('\n');

    return 0;
}
