#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{

    int number = 0;
    int variable = 0;
    int count = 0;
    int priznak = 0;

    if (scanf("%d", &number) != 1)
    {
        printf("Input error.");
        return 0;
    }
    int ar[number];
    variable = number;
    while (number > 0)
    {
        number /= 10;
        count++;
    }
    number = variable;

    // printf("%d\n", count);

    for (int i = 0; i < count; i++)
    {
        ar[i] = number % 10;
        // printf("a[%d] = %d\n", i, ar[i]);
        number /= 10;
    }

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (i != j && ar[i] == ar[j])
            {
                priznak++;
            }
        }
    }

    printf("%s\n", (priznak > 0) ? ("YES") : ("NO"));

    return 0;
}