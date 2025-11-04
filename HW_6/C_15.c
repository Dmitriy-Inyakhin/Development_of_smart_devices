// Цифры по возрастанию

// Составить функцию логическую функцию, которая определяет, 
// верно ли, что в заданном числе все цифры стоят по возрастанию. 
// Используя данную функцию решить задачу. int grow_up(int n)
// Input format
// Одно целое не отрицательное число
// Output format
// YES или NO

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool grow_up(int number) {
    int variable = 0;
    int count = 0;
    bool priznak = true;

    variable = number;
    while (number > 0)
    {
        number /= 10;
        count++;
    }
    number = variable;
    int ar[count];

    for(int i = count-1; i>=0; i--)
    {
        ar[i] = number % 10;
        number /= 10;
    }

    for(int i = 0; i < count-1; i++) {

        if(ar[i+1] <= ar[i]) {
        
            return false;
        }
    }
    return true;
    }

int main(int argc, char **argv) {

    int number = 0;
    if(scanf("%d", &number) != 1) {
        printf("Input error.");
        return 0;
    }
    if(number ==0) {
        printf("YES");
        return 0;
    }
    
    printf("%s\n", (grow_up(number)) ? ("YES") : ("NO"));

    return 0;
}

