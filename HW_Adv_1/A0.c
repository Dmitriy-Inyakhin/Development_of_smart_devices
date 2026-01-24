// Сколько раз встречается максимум
// На стандартном потоке ввода задаётся натуральное число N (N > 0),
// после которого следует последовательность из N целых чисел.На
// стандартный поток вывода напечатайте, сколько раз в этой
// последовательности встречается максимум. Указание: использовать
// массивы запрещается.
// Input
// 6 1 2 3 2 0 3
// Output
// 2
// Input
// 3 5 2 -1
// Output
// 1

#include <stdio.h>

int main(int argc, char **argv)
{
    int number = 0;
    int var_max = -2147483648;
    int count_max = 0;

    if (scanf("%d", &number) != 1)
    {
        printf("Input error.");
        return 0;
    }

    for (int i = 0; i < number; ++i)
    {
        int var_scan = 0;
        scanf("%d", &var_scan);

        if (var_scan > var_max)
        {
            var_max = var_scan;
            count_max = 1;
        }
        else if (var_scan == var_max)
        {
            count_max++;
        }
    }
    printf("%d\n", count_max);

    return 0;
}