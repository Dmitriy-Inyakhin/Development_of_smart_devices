#include <stdio.h>

int main(int args, char ** argv) {
    int var[5] = {0};
    int min = 0;
    
    if (scanf("%d %d %d %d %d", &var[0], &var[1], &var[2], &var[3], &var[4])!=5) {
        printf("Input error!");
        return 0;
    }
    min = var[0];

    for( int i = 0; i<5 ; i++) {
        if (min > var[i]) {
            min = var[i];
        }
    }

    printf("%d\n", min);
    return 0;
}