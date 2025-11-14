/*D_8.c
От A до B
Составить рекурсивную функцию, Выведите все числа от A до B включительно, в
порядке возрастания, если A < B, или в порядке убывания в противном случае.
Формат входных данных
    Два целых числа через пробел.
Формат результата
    Последовательность целых чисел.
*/

#include <stdio.h>

void print_line(int, int);

int main(int args, char **argv)
{
    int A = 0, B = 0;

    if (scanf("%d %d", &A, &B) != 2)
    {
        printf("Input error!");
        return 0;
    }

    print_line(A, B);
    return 0;
}

void print_line(int A, int B)
{
    /* код от ИИ: */
    /*printf("%d ", A); // печатаем текущее A

    if (A < B)
    {
        print_line(A + 1, B); // вперёд
    }
    else if (A > B)
    {
        print_line(A - 1, B); // назад
    }
    // если A == B — просто завершаемся (базовый случай)
    */
    /* Это мой, не оптимальный код:  оба кода работают одинаково правильно! */
    if (A < B)
    {
        if (A != B)
        {
            printf("%d ", A++);
            print_line(A, B);
            return;
        }
        else if (A == B)
            printf("%d ", B);
    }
    else
    {
        if (A != B)
        {
            printf("%d ", A--);
            print_line(A, B);
            return;
        }
        else if (A == B)
            printf("%d ", B);
    }
    
}