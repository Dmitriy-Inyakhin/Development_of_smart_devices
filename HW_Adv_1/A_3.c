// Извлечение бит

// На вход программе подается беззнаковое 32-битное целое число N и
// натуральное число K (1 ≤ K ≤ 31). Требуется взять K младших битов
// числа N и вывести полученное таким образом число.
// Examples
// Input
// 2 1
// Output
// 0
// Input
// 12 3
// Output
// 4
// Input
// 3 5
// Output
// 3
// Input
// 1024 3
// Output
// 0

#include <stdio.h>
void printBinary(int n) {
    // Определяем количество бит (например, 32 для int)
    for (int i = 31; i >= 0; i--) {
        int k = n >> i; // Сдвигаем бит на позицию i
        if (k & 1) // Проверяем, установлен ли бит
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}


int main(int argc, char **argv)
{
    int old_number;
    int new_number = 1;
    int lenght = 0;
    int mask = 1;

    if (scanf("%d %d", &old_number, &lenght) != 2)
    {
        printf("Input error.");
        return 0;
    }
    // printBinary(old_number);


    for (int i = 0; i < lenght-1; ++i)
    {
        mask <<= 1;
        mask |= 1;
    }
    // printBinary(mask);
    new_number = old_number & mask;

    printf("%d\n", new_number);
    return 0;
}