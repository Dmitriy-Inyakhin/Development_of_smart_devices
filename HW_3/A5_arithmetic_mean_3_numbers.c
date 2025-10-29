#include <stdio.h>

int main(int args, char ** argv) {
    int var_1=0, var_2=0, var_3=0;
    double result =0;
    
    if (scanf("%d %d %d", &var_1, &var_2, &var_3)!=3) {
        printf("Input error!");
        return 0;
    }
    result = ((double)var_1 + (double)var_2 + (double)var_3) / 3.0;

    printf("%.2f\n", result);
    return 0;
}