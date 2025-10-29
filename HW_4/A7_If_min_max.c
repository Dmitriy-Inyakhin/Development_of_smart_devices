#include <stdio.h>

int main(int args, char ** argv) {
    int var_1=0, var_2=0;
    
    if (scanf("%d %d", &var_1, &var_2)!=2) {
        printf("Input error!");
        return 0;
    }
    (var_1 > var_2) ? (printf("%d %d\n", var_2, var_1)) : (printf("%d %d\n", var_1, var_2));
    return 0;
}