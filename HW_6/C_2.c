// функция возведения в степень
#include <stdio.h>

int power(int n, int p) 
    {
        int res =1;
        for(int i = 1; i<=p; i++) {
        res *= n;
    }
    printf("%d\n", res);
    return 0;
    }

int main(int argc, char **argv) {
    int number = 1;
    
    int pow =0;
    
    if(scanf("%d %d", &number, &pow) != 2) {
        printf("Input error.");
        return 0;
    }

    power(number, pow);

    return 0;
}