// F_5.c
// Максимум в массиве
// Написать только одну функцию, которая находит максимальный элемент 
// в массиве. Всю программу загружать не надо.
// Прототип функции: int find_max_array(int size, int a[])
// Input format
// Массив состоящий из целых чисел. Первый аргумент, размер массива, 
// второй аргумент адрес нулевого элемента.
// Output format
// Одно целое число
// Examples
// Input
//     773 307 371 548 531 765 402 27 573 591 217 859 662 493 173 174 125 591 324 231 130 394 573 65 570 258 343 3 586 14 785 296 140 726 598 262 807 794 510 465 66 895 182 218 302 34 205 252 687 660 952 737 2 32 310 680 36 139 346 139 489 217 767 544 158 774 883 154 802 136 569 377 867 423 224 176 118 660 513 734 45 978 983 749 909 601 270 147 433 737 789 304 842 769 815 503 190 399 3
// Output
//     983

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int find_max_array(int size, int a[]) {
    if (size <= 0 || a == NULL) {
        return 0;
    }
    int max = a[0];
    for (int i = 1; i < size; ++i) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

int main() {
    char line[4096];  // буфер под строку до ~1000 чисел (достаточно: 1000*5 ≈ 5000 байт → берём с запасом 4K)
    
    if (fgets(line, sizeof(line), stdin) == NULL) {
        fprintf(stderr, "Input error!\n");
        return 1;
    }

    // Подсчитываем количество чисел, чтобы выделить память
    int count = 0;
    char *ptr = line;
    while (*ptr) {
        // Пропускаем не-цифры (пробелы, табы и т.п.)
        while (*ptr && (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' || *ptr == '\r')) {
            ++ptr;
        }
        if (*ptr == '\0' || *ptr == '\n') break;

        // Нашли начало числа — пропускаем его
        if (*ptr == '-' || *ptr == '+') ++ptr;  // знак опционален
        if (*ptr < '0' || *ptr > '9') break;   // не число — ошибка формата (но по условию — целые числа)

        while (*ptr >= '0' && *ptr <= '9') {
            ++ptr;
        }
        ++count;
    }

    if (count == 0) {
        fprintf(stderr, "Input error!\n");
        return 1;
    }

    int *arr = malloc(count * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Input error!\n");
        return 1;
    }

    // ✅ Надёжный парсинг:
    int i = 0;
    ptr = line;
    while (1) {
        char *end;
        long val = strtol(ptr, &end, 10);
        if (ptr == end) break;  // ничего не прочитано
        if (val < INT_MIN || val > INT_MAX) {
            // переполнение — по условию не ожидается, но для надёжности
            break;
        }
        arr[i++] = (int)val;
        ptr = end;
    }

    int size = i;
    if (size == 0) {
        free(arr);
        fprintf(stderr, "Input error!\n");
        return 1;
    }

    int result = find_max_array(size, arr);
    printf("%d\n", result);

    free(arr);
    return 0;
}