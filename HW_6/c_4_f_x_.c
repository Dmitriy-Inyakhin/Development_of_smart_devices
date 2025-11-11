// Описать функцию вычисления f(x) по формуле: 
// f(x)= x*x при -2 ≤ x < 2;
// x*x+4x+5 при x ≥ 2;
// 4 при x < -2.
// Используя эту функцию для n заданных чисел, вычислить f(x).
// Среди вычисленных значений найти наибольшее.
#include <stdio.h>

int f_x_(int x)
{
    if (x < -2)
    {
        return 4;
    }
    else if (x >= 2)
    {
        return (x * x + 4 * x + 5);
    }
    else
    {
        return x * x;
    }
    printf("Error.");
    return 0;
}

int max_x(int var[], int counter_x)
{
    int max = 0;
    for (int i = 0; i < counter_x; i++)
    {
        if (max < var[i])
        {
            max = var[i];
        }
    }
    return max;
}

int main(int argc, char **argv)
{
    int arg[15] = {0};
    int res[15] = {0};
    int count = 0;

    while (scanf("%d", &arg[count]) == 1 && arg[count] != 0 && count < 14)
    {
        count++;
    }

    for (int i = 0; i < count; i++)
    {
        res[i] = f_x_(arg[i]);
    }

    printf("%d\n", max_x(res, count));

    return 0;
}