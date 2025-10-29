#include <stdio.h>
#include <math.h>

int main(int argc, char **argv) {

    int number = 0;
    int variable = 0;
    int count = 0;
    int priznak = 0;

    if(scanf("%d", &number) != 1) {
        printf("Input error.");
        return 0;
    }
    if(number ==0) {
        printf("%d", 0);
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

    for(int i = 0; i<count; i++)
    {
        ar[i] = number % 10;
        printf("%d", ar[i]);
        // printf("a[%d] = %d\n", i, ar[i]);
        number /= 10;
    }
    printf("\n");

    return 0;
}