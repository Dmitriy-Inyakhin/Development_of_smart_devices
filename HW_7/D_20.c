// D_20.c
// Возвести в степень

// Написать рекурсивную функцию возведения целого числа n в степень p.
// int recurs_power(int n, int p)
// Используя данную функцию, решить задачу.
// Input format
//     Два целых числа -100 ≤ n ≤ 100 и 0 ≤ p ≤ 100
// Output format
//     Одно целое число n в степени p

#include <stdio.h>

long long recurs_power(int, int);

int main() {
   int n, p;
    int items_read = scanf("%d %d", &n, &p);

    // Проверка: прочитано ровно 2 значения
    if (items_read != 2) {
        fprintf(stderr, "Error: Exactly two integers expected.\n");
        return 1;
    }

    // Проверка границ
    if (n < -100 || n > 100) {
        fprintf(stderr, "Error: n must be between -100 and 100 (inclusive).\n");
        return 1;
    }
    if (p < 0 || p > 100) {
        fprintf(stderr, "Error: p must be between 0 and 100 (inclusive).\n");
        return 1;
    }

    // Дополнительно: проверим, нет ли "мусора" после двух чисел
    // (например, пользователь ввёл "2 3 abc")
    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        if (c != ' ' && c != '\t') {
            fprintf(stderr, "Error: Extra characters after input.\n");
            return 1;
        }
    }

    long long result = recurs_power(n, p);
    printf("%lld\n", result);
    return 0;
}

long long recurs_power(int n, int p) {
    if (p == 0) {
        return 1;
    }
    long long half = recurs_power(n, p / 2);
    if (p % 2 == 0) {
        return half * half;
    } else {
        return half * half * n;
    }
}