// Поиск последовательности бит

// На вход программе подается беззнаковое 32-битное целое число N и
// натуральное число K (1 ≤ K ≤ 31). Требуется взять K подряд идущих
// битов числа N так, чтобы полученное число было максимальным.
// Программа должна вывести полученное число.
// Input
// 2 1
// Output
// 1
// Input
// 12 3
// Output
// 6
// Input
// 3 5
// Output
// 3
// Input
// 1024 3
// Output
// 4

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
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
    uint32_t number;
    uint32_t max_values = 0;
    uint32_t lenght = 0;
    uint32_t mask = 0;

    if (scanf("%" SCNu32 " %" SCNu32, &number, &lenght) != 2)
    {
        printf("Input error.");
        return 0;
    }

    lenght %= 32;
    mask = (1U << lenght) - 1;
    // printBinary(mask);

    for (int i = 0; i <= (32 - lenght); ++i)
    {
        uint32_t var = (number>>i) & mask;
        if(var > max_values)
        {
            max_values = var;
        } 
    }

    printf("%u\n", max_values);
    return 0;
}