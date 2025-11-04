// Сумма цифр равна произведению

// Составить логическую функцию, которая определяет, верно ли,
// что в заданном числе сумма цифр равна произведению.
// int is_happy_number(int n)
// Input format
// Целое не отрицательное число
// Output format
// YES или NO

#include <stdio.h>
#include <stdbool.h>

int is_happy_number(int n)
{
    int summ = 0;
    int multipl = 1;
    int count = n;
    while (count > 0)
    {
        summ += count % 10;
        multipl *= count % 10;
        count /= 10;
    }
    if (summ == multipl)
    {
        return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    int number;
    if (scanf("%d", &number) != 1 || number < 0)
    {
        printf("Input error.\n");
        return 0;
    }
    if (number == 1 || number == 0)
    {
        printf("YES\n");
        return 0;
    }
    printf("%s\n", (is_happy_number(number)) ? ("YES") : ("NO"));
    return 0;
}