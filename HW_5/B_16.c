// Наибольший общий делитель

// Составить программу для вычисления НОД с помощью алгоритма 
// Евклида. Даны два натуральных числа. Найти наибольший общий делитель.
// Input format
// Два неотрицательных целых числа
// Output format
// Одно целое число наибольший общий делитель

#include <stdio.h>

int main(int argc, char **argv) {
    int number_1, number_2;

if(scanf("%d %d", &number_1, &number_2) != 2 || number_1 <= 0 || number_2 <=0) {
        printf("Input error.\n");
        return 0;
    }

if(number_2>number_1) {
        int tmp = number_2;
        number_2=number_1;
        number_1=tmp;
    }
    int r = 1;
    while (r!=0)
    {
        r = number_1 % number_2;
        number_1 = number_2;
        number_2 = r;
    }
    printf("%d\n", number_1);

}