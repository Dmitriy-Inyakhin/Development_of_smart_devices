//  Все счастливые числа

// Ввести натурально число и напечатать все числа от 10 до введенного
// числа - у которых сумма цифр равна произведению цифр
// Input format
// Одно натуральное число большее 10
// Output format
// Числа у которых сумма цифр равна произведению цифр через пробел
// в порядке возрастания. Не превосходящие введенное число.

#include <stdio.h>

int main(int argc, char **argv)
{
    int number;
    int count = 0;

    if (scanf("%d", &number) != 1 || number < 10)
    {
        printf("Imput error.\n");
        return 0;
    }

    for (int i = 10; i <= number; i++)
    {
        int summ = 0;
        int multipl = 1;
        count = i;
        while (count > 0)
        {
            summ += count % 10;
            multipl *= count % 10;
            count /= 10;
        }
        if (summ == multipl)
        {
            printf("%d ", i);
        }
    }
    printf("\n");
    return 0;
}