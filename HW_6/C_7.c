// Перевести число N в систему счисления P
// Составить функцию, которая переводит число N из десятичной 
// системы счисления в P-ичную систему счисления.

// Input format
// Два целых числа. N ≥ 0 и 2 ≤ P ≤ 9
// Output format
// Одно целое число

#include <stdio.h>

unsigned long convertToBase(int N, int P) {
    if (N == 0) {
        return 0;
    }
    unsigned long res = 0;
    int plase = 1;


    while (N > 0)
    {
        res += (N % P) * plase;
        N /= P;
        plase *=10;
    }
    return res;
}

int main(int argc, char **argv) {
    int number = 0;
    int degree = 0;
    
    
    if(scanf("%d %d", &number, &degree) != 2 || number < 0 || degree < 2 || degree >9) {
        printf("Input error.\n");
        return 0;
    }
    
    printf("%lu\n", convertToBase(number, degree));
    return 0;
}
