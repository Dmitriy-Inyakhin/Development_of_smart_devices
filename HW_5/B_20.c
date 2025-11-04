// Проверка на простоту

// Проверить число на простоту.
// Input format
// Натуральное число
// Output format
// Если число является простым напечатать YES, иначе NO

#include <stdio.h>

int main(int argc, char **argv) {
    int number;
    int priznak = 0;

    if(scanf("%d", &number) != 1) {
        printf("Imput error.\n");
        return 0;
    }
    if(number == 1 ){
        printf("NO\n");
        return 0;
    }
    for(int i =2; i< number; i++) {
        if(number % i == 0) {
            priznak++;
        }
    }
        if(priznak == 0) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
    
    return 0;
}