// находим среднее арифметическое
#include <stdio.h>

int arifm_mean(int a, int b) 
    {
        int res = 0;
        res = (a+b)/2;
       
    
    printf("%d\n", res);
    return 0;
    }

int main(int argc, char **argv) {
    int number_1;
    int number_2;
    
    if(scanf("%d %d", &number_1, &number_2) != 2) {
        printf("Input error.");
        return 0;
    }

    arifm_mean(number_1, number_2);

    return 0;
}