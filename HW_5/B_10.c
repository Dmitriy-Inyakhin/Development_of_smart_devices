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
    if (number == 0)
    {
        printf("YES");
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

    for (int i = count - 1; i >= 0; i--)
    {
        ar[i] = number % 10;
        // printf("a[%d] = %d\n", i, ar[i]);
        number /= 10;
    }

    for (int i = 0; i < count - 1; i++)
    {
        if (ar[i + 1] > ar[i])
        {
            priznak++;
        }
    }

    printf("%s\n", (priznak == count - 1) ? ("YES") : ("NO"));
    // printf("%d %d\n", priznak, count);

    return 0;
}