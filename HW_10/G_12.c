// G_12.c
// Разобрать на слова
// В файле input.txt дано предложение требуется разобрать его на 
// отдельные слова. Напечатать каждое слово на отдельной строке в 
// файл output.txt.

// Input format
//     Одна строка из английских букв и пробелов не более 1000 символов.
// Output format
//     Каждое слово на отдельной строке
// Examples
// Input in input.txt
//     Mama mila ramu
// Output in output.txt
//     Mama
//     mila
//     ramu

#include <stdio.h>
#include <string.h>

int main() {
    FILE *in = fopen("input.txt", "r");
    if (!in) return 1;

    char s[1001];
    if (!fgets(s, sizeof(s), in)) {
        fclose(in);
        return 1;
    }
    fclose(in);

    FILE *out = fopen("output.txt", "w");
    if (!out) return 1;

    int i = 0;
    int n = (int)strlen(s);
    int first_word = 1; // можно использовать для управления форматом (не обязательно)

    while (i < n) {
        // Пропускаем пробелы
        while (i < n && s[i] == ' ') {
            i++;
        }

        if (i >= n) break;

        // Нашли начало слова
        int start = i;
        while (i < n && s[i] != ' ') {
            i++;
        }
        int end = i; // end — первый символ после слова

        // Выводим слово: символы от start до end-1
        for (int j = start; j < end; j++) {
            fputc(s[j], out);
        }
        fputc('\n', out); // каждое слово — на новой строке
    }

    fclose(out);
    return 0;
}