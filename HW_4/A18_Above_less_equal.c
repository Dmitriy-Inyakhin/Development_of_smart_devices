#include <stdio.h>
int main(int args, char **argv) {
    int var_1, var_2;

    if(scanf("%d %d", &var_1, &var_2)!=2) {
        printf("Input error.");
        return 0;
    }

    if(var_1 == var_2) {
        printf("Equal\n");
    }else if(var_1 >var_2) {
        printf("Above\n");
    } else {
        printf("Less\n");
    }



    return 0;
}