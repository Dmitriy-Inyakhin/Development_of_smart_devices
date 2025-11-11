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

    while (number > 0)
    {
        if ((number % 10) % 2 == 0)
        {
            priznak++;
        }

        number /= 10;
        count++;
    }

    printf("%s\n", (priznak == count) ? ("YES") : ("NO"));

    return 0;
}