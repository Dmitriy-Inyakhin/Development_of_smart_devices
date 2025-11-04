// функция нахождения модуля числа
#include <stdio.h>

int main(int argc, char **argv) {
    int number = 0;
    
    if(scanf("%d", &number) != 1) {
        printf("Input error.");
        return 0;
    }

    if(number<0) {
        printf("%d\n", -number);
    } else {
        printf("%d\n", number);
    }

    return 0;
}