// Сумма цифр равна 10

// Ввести натуральное число и определить, верно ли, что сумма его цифр равна 10.
// Input format
// Натуральное число
// Output format
// YES или NO

#include <stdio.h>

int main(int argc, char **argv) {
    int number;

    if(scanf("%d", &number) != 1) {
        printf("Imput error.\n");
        return 0;
    }
    
        int summ = 0;
        while (number > 0)
        {
            summ += number % 10;
            number /= 10;
        }
        if(summ == 10) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
    
    return 0;
}