#include <stdio.h>

int main(int args, char **argv)
{
    int var_1 = 0;
    int var[3] = {0};
    int max = 0;

    if (scanf("%d", &var_1) != 1)
    {
        printf("Input error!");
        return 0;
    }

    for (int i = 0; i < 3; i++)
    {
        var[i] = var_1 % 10;
        var_1 /= 10;
    }

    for (int i = 0; i < 3; i++)
    {
        if (var[i] > max)
        {
            max = var[i];
        }
    }

    printf("%d\n", max);
    return 0;
}