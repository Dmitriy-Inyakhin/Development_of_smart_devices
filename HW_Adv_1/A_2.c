// Циклический сдвиг

// На вход программе подается беззнаковое 32-битное целое число N и 
// натуральное число K (1 ≤ K ≤ 31). Требуется циклически сдвинуть 
// битычисла N вправо на K битов и вывести полученное таким образом число.
// Input
// 2 1
// Output
// 1
// Input
// 1 2
// Output
// 1073741824
// Input
// 3 1
// Output
// 2147483649
// Input
// 12 2
// Output
// 3
// Input
// 19 3
// Output
// 1610612738
#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    uint32_t old_number;
    uint32_t new_number = 0;
    uint32_t lenght = 0;

    if (scanf("%d %d", &old_number, &lenght) != 2)
    {
        printf("Input error.");
        return 0;
    }
    lenght %= 32;
    new_number = (old_number >> lenght) | (old_number << (32 - lenght));
    printf("%u\n", new_number);
    return 0;
}