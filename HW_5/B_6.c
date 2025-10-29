#include <stdio.h>
#include <math.h>

int main(int argc, char **argv) {

    int number = 0;
    int count = 0;
    int priznak = 0;

    if(scanf("%d", &number) != 1) {
        printf("Input error.");
        return 0;
    }

    while (number > 0)
    {
        if(count == number %10) {
            priznak++;
        }
        count = number % 10;
        number /= 10;
    }
    
    printf("%s\n", (priznak > 0) ? ("YES") : ("NO"));

    return 0;
}