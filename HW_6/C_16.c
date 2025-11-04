// Проверка на простоту

// Составить логическую функцию, которая определяет, верно ли,
// что число простое. Используя функцию решить задачу. int is_prime(int n)
// Input format
// Одно целое не отрицательное число.
// Output format
// YES или NO

#include <stdio.h>
#include <stdbool.h>

int is_prime(int n)
{
    for(int i = 2; i < n; i++){
        if(n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char **argv)
{
    int number;
    if (scanf("%d", &number) != 1 || number < 0)
    {
        printf("Input error.\n");
        return 0;
    }
    if(number == 1 ||number == 0) {
        printf("NO\n");
        return 0;
    }
    printf("%s\n", (is_prime(number)) ? ("YES") : ("NO"));
    return 0;
}