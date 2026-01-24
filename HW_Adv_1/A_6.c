// Инверсия старших

// На вход программе подается беззнаковое 32-битное целое
// число N. Требуется изменить значения всех битов старшего
// байта числа на противоположные и вывести полученное таким
// образом число.

// Input
// 1
// Output
// 4278190081
// Input
// 4278190081
// Output
// 1
// Input
// 2739690055
// Output
// 1548507719

#include <stdio.h>
#include <stdint.h>

void printBinary(int n)
{
    // Определяем количество бит (например, 32 для int)
    for (int i = 31; i >= 0; i--)
    {
        int k = n >> i; // Сдвигаем бит на позицию i
        if (k & 1)      // Проверяем, установлен ли бит
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    uint32_t old_number;
    uint32_t mask = 0xFF000000u;
    uint32_t new_number = 0;
    uint32_t old_bits;
    if (scanf("%d", &old_number) != 1)
    {
        printf("Input error.");
        return 0;
    }
    old_bits = ~(old_number & mask) & mask;
    new_number = old_number & ~mask;
    new_number |= old_bits;

    uint32_t result = (old_number & ~mask) | (~old_number & mask);

    printf("%u\n", new_number);
    printf("%u\n", result);

    return 0;
}