#include <stdio.h>

int main(int args, char ** argv) {
    int var[5] = {0};
    int max = 0;
    
    if (scanf("%d %d %d %d %d", &var[0], &var[1], &var[2], &var[3], &var[4])!=5) {
        printf("Input error!");
        return 0;
    }

    for( int i = 0; i<5 ; i++) {
        if (var[i] > max) {
            max = var[i];
        }
    }

    printf("%d\n", max);
    return 0;
}