#include <stdio.h>

int main(int args, char ** argv) {
    int var[3] = {0};
    int max = 0;
    
    if (scanf("%d %d %d %d %d", &var[0], &var[1], &var[2])!=3) {
        printf("Input error!");
        return 0;
    }

    for( int i = 0; i<3 ; i++) {
        if (var[i] > max) {
            max = var[i];
        }
    }

    printf("%d\n", max);
    return 0;
}