// D_12.c
// Монотонная последовательность
// Дана монотонная последовательность, в которой каждое
// натуральное число k встречается ровно k раз: 1, 2, 2, 3, 3, 3, 4, 4, 4, 4,…
// Выведите первые n членов этой последовательности.
// Input format
//     Натуральное число.
// Output format
//     Последовательность целых чисел.


#include <stdio.h>

// Вспомогательная функция: какой элемент на позиции i (1-based)?
int kth_term(int i) {
    int k = 1;
    int total = 0;
    while (total + k < i) {
        total += k;
        k++;
    }
    return k;
}

// Рекурсивная функция с ОДНИМ аргументом
void print_seq(int n) {
    if (n <= 0) return;

    if (n == 1) {
        printf("1");
    } else {
        print_seq(n - 1);          // сначала выведем первые n-1
        printf(" %d", kth_term(n)); // затем n-й элемент
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Input error.\n");
        return 1;
    }

    print_seq(n);
    printf("\n");
    return 0;
}