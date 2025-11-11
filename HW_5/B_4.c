#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{

    int number = 0;
    int count = 0;

    if (scanf("%d", &number) != 1)
    {
        printf("Input error.");
        return 0;
    }

    while (number > 0)
    {
        number /= 10;
        count++;
    }

    printf("%s\n", (count == 3) ? ("YES") : ("NO"));

    return 0;
}