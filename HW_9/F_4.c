// F_4.c
// Цифры в строке
// Написать только одну функцию. Всю программу отправлять не надо.
// Вывести в порядке возрастания цифры, входящие в строку. Цифра -
// количество. Функция должно строго соответствовать прототипу:
// void print_digit(char s[])
// Input format
//     Строка из английских букв, пробелов, знаков препинания и цифр
// Output format
//     Функция должна принмать на вход строку и выводить на печать
// по формату: Цифра пробел количество.
// Examples
// Input
//     Hello123 world77.
// Output
// 1 1
// 2 1
// 3 1
// 7 2

#include <stdio.h>
#include <string.h>
#define MAX_SIZE 50 + 1
int safe_read_line(char *buf, size_t buf_size);

void print_digit(char s[])
{
    int count[10] = {0}; // счётчики для '0'..'9'

    // Подсчёт частот
    for (int i = 0; s[i] != '\0'; ++i)
    {
        char c = s[i];
        if (c >= '0' && c <= '9')
        {
            count[c - '0']++;
        }
        // (по условию — натуральное число, так что других символов быть не должно)
    }

    // Вывод: цифра (по возрастанию) + количество, только если > 0
    for (int digit = 0; digit <= 9; ++digit)
    {
        if (count[digit] > 0)
        {
            printf("%d %d\n", digit, count[digit]);
        }
    }
}

int main()
{
    char s[MAX_SIZE]; 

    safe_read_line(s, MAX_SIZE);

    print_digit(s);
    printf("%s\n", s);

    return 0;
}

// Возвращает:
//   0 — успешно, строка прочитана полностью
//   1 — успешно, но строка усечена (длиннее буфера)
//  -1 — ошибка ввода (выведено в stderr)
int safe_read_line(char *buf, size_t buf_size)
{
    if (!buf || buf_size == 0)
    {
        fprintf(stderr, "Input error!\n");
        return -1;
    }

    if (fgets(buf, (int)buf_size, stdin) == NULL)
    {
        *buf = '\0';
        fprintf(stderr, "Input error!\n");
        return -1;
    }

    // Удаляем '\n'
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n')
    {
        buf[len - 1] = '\0';
    }

    // Проверка усечения
    if (len == buf_size - 1 && buf[len - 1] != '\n')
    {
        // Считываем остаток строки
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
            // пропускаем
        }
        return 1; // усечение — не ошибка, просто предупреждение (не выводим в stderr)
    }

    return 0;
}