#include <stdio.h>

int main(int args, char ** argv) {
    int var_1=0, var_2=0, var_3=0;
    
    if (scanf("%d %d %d", &var_1, &var_2, &var_3)!=3) {
        printf("Input error!");
        return 0;
    }

    printf("%d+%d+%d=%d\n", var_1, var_2, var_3, var_1+var_2+var_3);
    return 0;
}