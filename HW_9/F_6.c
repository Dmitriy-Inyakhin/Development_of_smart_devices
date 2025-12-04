// F_6.c
// Два одинаковых
// Написать только одну логическую функцию, которая определяет,
// верно ли, что среди элементов массива есть два одинаковых.
// Если ответ «да», функция возвращает 1; если ответ «нет», то 0.
// Строго согласно прототипу:
// int is_two_same(int size, int a[]);
// Input format
//     Массив из целых чисел
// Output format
// Функция возвращает 1 или 0
// Examples
// Input
//     1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100
// Output
//     NO
// Input
//     1 2 1 4 5
// Output
//     YES

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

// Возвращает количество успешно распарсенных целых чисел.
// out — выходной массив, out_size — его размер (в элементах).
// Поддерживает знаки, пропускает пробелы, проверяет переполнение и некорректный ввод.
int parse_ints_with_strtol(const char *str, int *out, int out_size)
{
    if (!str || !out || out_size <= 0)
    {
        return 0;
    }

    int count = 0;
    const char *p = str;

    while (*p && count < out_size)
    {
        // 1. Пропускаем пробельные символы
        while (isspace((unsigned char)*p))
        {
            ++p;
        }
        if (*p == '\0')
            break;

        // 2. Сохраняем errno перед вызовом strtol
        errno = 0;
        char *endptr;
        long val = strtol(p, &endptr, 10);

        // 3. Проверяем, было ли вообще преобразование
        if (p == endptr)
        {
            // Нет цифр — пропускаем один символ (защита от зацикливания)
            ++p;
            continue;
        }

        // 4. Проверка переполнения/underflow
        if (errno == ERANGE || val < INT_MIN || val > INT_MAX)
        {
            // Некорректное число — пропускаем его часть
            p = endptr;
            continue;
        }

        // 5. Успешное преобразование
        out[count++] = (int)val;
        p = endptr; // двигаем указатель дальше
    }

    return count;
}

void print_array(int size, int ar[])
{
    for (int i = 0; i < size; ++i)
    {
        if (i > 0)
        {
            putchar(' ');
        }
        printf("%d", ar[i]);
    }
    putchar('\n');
}

int is_two_same(int size, int a[])
{
    int count = 0;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (a[i] == a[j] && i != j)
            {
                count++;
                //printf("_+%d+_\n", count);
            }
        }
    }
    return (count/2 == 1) ? (1) : (0);
}

int main()
{

    char line[1005]; // буфер под строку до ~1000 чисел (достаточно: 1000*5 ≈ 5000 байт → берём с запасом 4K)

    if (fgets(line, sizeof(line), stdin) == NULL)
    {
        fprintf(stderr, "Input error!\n");
        return 1;
    }

    int arr[150];
    int n = parse_ints_with_strtol(line, arr, 150);

    printf("Успешно распарсено %d чисел:\n", n);
    printf("%lu\n", strlen(line));

    print_array(n, arr);
    putchar('\n');
    printf("%d\n", is_two_same(n, arr));

    return 0;
}