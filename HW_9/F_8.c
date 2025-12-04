// F_8.c
// Пропущенное число
// В последовательности записаны целые числа от M до N 
// ( M меньше N, M больше или равно 1)в произвольном порядке,
//  но одно из чисел пропущено (остальные встречаются ровно по 
//     одному разу). N не превосходит 1000. Последовательность 
//     заканчивается числом 0. Определить пропущенное число.
// Формат входных данных
// Последовательность целых чисел от M до N. M, N не превосходит 1000.
// Формат результата
// Одно целое число
// Примеры
// Входные данные
//     2   3   1   4   7   6   9   8  10   0
// Результат работы
//     5
// Входные данные
//     41 40 39 38 37 36 34 33 32 31 50 49 48 47 46 45 44 43 42 30 0
// Результат работы
//     35

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> // для exit()

#define SIZE 1000

int read_integers_line(int a[], int max_size);
void print_array(int size, int ar[]);
void sort_array(int size, int ar[]);
int read_integers_NULL(int a[], int MAX_N);
void print_num_array(int size, int ar[]);

int main(int args, char **argv)
{
    int var[SIZE] = {0};

    int count = SIZE - read_integers_NULL(var, SIZE);

    sort_array(sizeof(var) / sizeof(var[0]) - count, var);
    // print_array(sizeof(var) / sizeof(var[0]) - count, var);
    print_num_array(sizeof(var) / sizeof(var[0]) - count, var);
    // print_array(sizeof(var) / sizeof(var[0]) - count, var);
    return 0;
}

void sort_array(int size, int ar[])
{
    int i = 0;
    _Bool flag;
    do
    {
        flag = 0;
        for (int j = size - 2; j >= i; j--)
        {
            if (ar[j] > ar[j + 1])
            {
                int temp = ar[j];
                ar[j] = ar[j + 1];
                ar[j + 1] = temp;
                flag = 1;
            }
        }
        i++;
    } while (flag);
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

// функция принимает любое количество целых чисел, ввод оканчивается символом "\n"
int read_integers_line(int a[], int max_size)
{
    int count = 0;
    int c;

    // Пропускаем начальные пробелы и табы (на случай, если строка начинается с них)
    while ((c = getchar()) != '\n' && c != EOF && isspace(c))
    {
        // только пропускаем
    }

    // Если первым символом была новая строка — пустая строка
    if (c == '\n' || c == EOF)
    {
        return 0;
    }

    // Вернём первый непробельный символ обратно в поток
    ungetc(c, stdin);

    // Теперь читаем числа через scanf, но останавливаемся на '\n'
    while (count < max_size)
    {
        // Проверяем следующий символ: если '\n' — выход
        c = getchar();
        if (c == '\n' || c == EOF)
        {
            break;
        }
        ungetc(c, stdin); // возвращаем, чтобы scanf его прочитал

        // Пытаемся прочитать целое число
        if (scanf("%d", &a[count]) != 1)
        {
            // Если не число — пропускаем один символ (защита от зацикливания)
            getchar();
            continue;
        }
        count++;
    }

    // "Съедаем" остаток строки (если вдруг scanf оставил что-то после последнего числа)
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // просто пропускаем
    }

    return count;
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
