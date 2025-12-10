// G_8.c
// Числа в массив
// В файле input.txt дана строка, не более 1000 символов, содержащая 
// буквы, целые числа и иные символы. Требуется все числа, которые 
// встречаются в строке, поместить в отдельный целочисленный массив. 
// Например, если дана строка "data 48 call 9 read13 blank0a", то в 
// массиве числа 48, 9, 13 и 0. Вывести массив по возрастанию в файл 
// output.txt.

// Input format
//     Строка из английских букв, цифр и знаков препинания
// Output format
//     Последовательность целых чисел отсортированная по возрастанию
// Examples
// Input in input.txt
//     data 48 call 9 read13 blank0a
// Output in output.txt
//     0 9 13 48

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

//функция перемены мест аргументов
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Функция сортировки пузырьком (можно заменить на qsort, но без библиотек — проще так)
void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}


int main() {
    FILE *in = fopen("input.txt", "r");
    if (!in) return 1;

    char line[1001];
    if (!fgets(line, sizeof(line), in)) {
        fclose(in);
        return 1;
    }
    fclose(in);

    int numbers[1000]; // максимум — каждая цифра отдельно, но реально гораздо меньше
    int count = 0;

    int i = 0;
    while (line[i] != '\0') {
        // Пропускаем нецифровые символы
        while (line[i] != '\0' && !isdigit((unsigned char)line[i])) {
            i++;
        }

        if (line[i] == '\0') break;

        // Нашли начало числа — читаем его целиком (atoi не подойдёт напрямую, т.к. 
        // нужно остановиться на нецифре)
        // Лучше парсить вручную: поддержка многозначных чисел, включая 0 в начале 
        // (но atoi и strtoul обработают правильно)
        // Используем strtol для надёжного парсинга:
        char *endptr;
        long num = strtol(&line[i], &endptr, 10);

        // Проверяем, что действительно распарсили цифры (endptr != &line[i])
        if (endptr != &line[i]) {
            // Игнорируем переполнение int для простоты (по условию — разумные числа)
            if (num >= INT_MIN && num <= INT_MAX) {
                numbers[count++] = (int)num;
            }
        }

        // Продвигаем i на позицию после числа
        i = (int)(endptr - line);
    }

    // Сортируем
    sort(numbers, count);

    // Выводим в output.txt
    FILE *out = fopen("output.txt", "w");
    if (!out) return 1;

    for (int i = 0; i < count; i++) {
        if (i > 0) fprintf(out, " ");
        fprintf(out, "%d", numbers[i]);
    }
    // Даже если count == 0 — выводим пустой файл, как и требуется

    fclose(out);
    return 0;
}