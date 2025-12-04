// F_17.c
// След матрицы
// Составить функцию которая находит след матрицы в двумерном
// массиве. Показать пример ее работы на матрице из 5 на 5 элементов.
// След матрицы - это сумма элементов на главной диагонали.
// Формат входных данных
//     25 целых чисел через пробел.
// Формат результата
//     Одно целое число.
// Примеры
// Входные данные
/*
    1 1 1 1 1
    2 2 2 2 2
    3 3 3 3 3
    4 4 4 4 4
    5 5 5 5 5
*/
// Результат работы
//     15

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> // для exit()

int read_integers_line(int a[], int max_size);
int print_array(int size, int ar[]);
int read_integers_NULL(int a[], int MAX_N);

#define SIZE 25

int main(int args, char **argv)
{
    int var[SIZE] = {0};

    int count = SIZE - read_integers_NULL(var, SIZE);

    // sort_array(sizeof(var) / sizeof(var[0]) - count, var);
    printf("%d\n", print_array(sizeof(var) / sizeof(var[0]) - count, var));
    // print_num_array(sizeof(var) / sizeof(var[0]) - count, var);
    // print_array(sizeof(var) / sizeof(var[0]) - count, var);
    return 0;
}

int print_array(int size, int ar[])
{
    int counter = 0;
    int res = 0;
    for (int i = 0; i < size / 5; ++i)
    {
        for (int j = 0; j < size / 5; ++j)
        {
            counter++;
            if(i == j)
            {
                res += ar[counter-1];
            }
        }
    }
    return res;
}

// функция принимает любое количество целых чисел, ввод оканчивается символом "0"
int read_integers_NULL(int a[], int MAX_N)
{
    int count = 0;
    int x;

    while (count < MAX_N)
    {
        int result = scanf("%d", &x);
        if (result == EOF)
        {
            // Достигнут конец ввода (например, Ctrl+D / Ctrl+Z) без 0
            fprintf(stderr, "Input error\n");
            exit(1);
        }
        if (result != 1)
        {
            // Не удалось прочитать целое число (введена буква и т.п.)
            fprintf(stderr, "Input error\n");
            exit(1);
        }

        if (x == 0)
        {
            // Успешное завершение по нулю — выходим нормально
            break;
        }

        a[count++] = x;
    }

    // Опционально: "съедаем" остаток строки после 0 (необязательно при scanf %d)
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // пропускаем
    }

    return count;
}

void print_num_array(int size, int ar[])
{
    int count = ar[0];
    int*ptr = ar;
    for (int i = ar[0]; i < ar[size-1]; i++)
    {
        if (count != *ptr)
        {
            printf("%d\n", i);
            return;
        }
        count++;
        ptr++;
    }
    putchar('\n');
}
