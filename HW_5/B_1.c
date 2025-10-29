#include <stdio.h>
#include <math.h>

int main(int argc, char **argv) {

    int number = 0;

    if(scanf("%d", &number) != 1) {
        printf("Input error.");
        return 0;
    }

    for (int i = 1; i<=number; i++) {
        printf("%d %d %.0f\n", i, i*i, pow(i, 3));
    }

    return 0;
}