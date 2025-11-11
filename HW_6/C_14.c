// Сумма цифр четна

// Составить логическую функцию, которая определяет, верно ли,
// что сумма его цифр – четное число. Используя эту функцию решить задачу.
// Input format
// Одно целое не отрицательное число
// Output format
// Ответ YES или NO

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool func_chet(int N)
{
    int count = 0;
    while (N > 0)
    {
        count += N % 10;
        N /= 10;
    }
    if (count % 2 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

int main(int argc, char **argv)
{

    int number = 0;
    if (scanf("%d", &number) != 1)
    {
        printf("Input error.");
        return 0;
    }

    printf("%s\n", (func_chet(number)) ? ("YES") : ("NO"));

    return 0;
}
