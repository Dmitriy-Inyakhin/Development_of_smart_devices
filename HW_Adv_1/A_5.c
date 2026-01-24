// Подсчет битов
// На вход программе подается беззнаковое 32-битное целое число N. 
// Требуется найти количество единичных битов в двоичном представлении 
// данного числа.
// Input
// 15
// Output
// 4
// Input
// 16
// Output
// 1
// Input
// 17
// Output
// 2

#include <stdio.h>

int main(int argc, char **argv)
{
    int number;
    int count = 0;
    if (scanf("%d", &number) != 1)
    {
        printf("Input error.");
        return 0;
    }
    
    if(number == 0)
    {
        printf("0\n");
        return 0;
    }

    // for(int i = 0; i < 32; ++i)
    // {
    //     if(number & 1)
    //     {
    //         count++;
    //     }
    //     number >>=1;
    // }

    while (number) {
        number &= number - 1;
        count++;
    }

    printf("%d\n", count);
    return 0;
}
