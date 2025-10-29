#include <stdio.h>

int main(int args, char ** argv) {
    int var_1 = 0;
    int result =0;
    
    if (scanf("%d", &var_1)!=1) {
        printf("Input error!");
        return 0;
    }
    
    for (int i =0; i<3; i++) {
    result += var_1%10;
    var_1 /=10;
    }

    printf("%d\n", result);
    return 0;
}