// Вычеркивание
// Сколько различных трехзначных чисел можно получить из заданного 
// натурального N, вычеркивая цифры из его десятичной записи?
// Input
// 1111111111111111111111111
// Output
// 1


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {
    // Чтение числа как строки (без ограничения на длину до 2 млн символов)
    char buf[2000000];
    if (scanf("%1999999s", buf) != 1) {
        return 1;
    }
    int len = strlen(buf);

    // Если цифр меньше трёх — невозможно составить трёхзначное число
    if (len < 3) {
        printf("0\n");
        return 0;
    }

    // Выделение памяти для массива next[len+1][10]
    // next[i][d] = позиция первой цифры d, начиная с индекса i (или len, если нет)
    int (*next)[10] = malloc((len + 1) * sizeof(*next));
    if (!next) {
        return 1;
    }

    // Инициализация последней строки (после конца строки цифр нет)
    for (int d = 0; d < 10; ++d) {
        next[len][d] = len;
    }

    // Заполнение массива справа налево
    for (int i = len - 1; i >= 0; --i) {
        // Копируем значения из следующей позиции
        for (int d = 0; d < 10; ++d) {
            next[i][d] = next[i + 1][d];
        }
        // Обновляем позицию текущей цифры
        int digit = buf[i] - '0';
        next[i][digit] = i;
    }

    // Массив для отслеживания уникальных трёхзначных чисел
    bool seen[1000] = {false};

    // Перебор всех возможных трёхзначных чисел (от 100 до 999)
    for (int a = 1; a <= 9; ++a) {          // Первая цифра не может быть 0
        int i = next[0][a];
        if (i == len) continue;             // Цифра a не найдена

        for (int b = 0; b <= 9; ++b) {
            int j = next[i + 1][b];
            if (j == len) continue;         // Цифра b после позиции i не найдена

            for (int c = 0; c <= 9; ++c) {
                int k = next[j + 1][c];
                if (k == len) continue;     // Цифра c после позиции j не найдена

                int num = 100 * a + 10 * b + c;
                seen[num] = true;
            }
        }
    }

    // Подсчёт уникальных чисел
    int count = 0;
    for (int num = 100; num <= 999; ++num) {
        if (seen[num]) {
            ++count;
        }
    }

    printf("%d\n", count);

    free(next);
    return 0;
}