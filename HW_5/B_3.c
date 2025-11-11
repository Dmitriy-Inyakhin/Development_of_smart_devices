#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{

    int number_1 = 0;
    int number_2 = 0;
    double result = 0;

    if (scanf("%d %d", &number_1, &number_2) != 2 && number_1 > number_2)
    {
        printf("Input error.");
        return 0;
    }

    for (int i = number_1; i <= number_2; i++)
    {
        result += pow(i, 2);
    }
    printf("%.0f ", result);
    printf("\n");

    return 0;
}