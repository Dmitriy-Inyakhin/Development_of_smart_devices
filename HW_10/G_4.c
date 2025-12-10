// G_4.c
// По одному разу
// В файле input.txt даны два слова не более 100 символов каждое, 
// разделенные одним пробелом. Найдите только те символы слов, которые 
// встречаются в обоих словах только один раз. Напечатайте их через 
// пробел в файл output.txt в лексикографическом порядке.

// Input format
//     Два слова из маленьких английских букв через пробел. Длинна каждого 
//     слова не больше 100 символов.
// Output format
//     Маленькие английские буквы через пробел.
// Examples
//     Input in input.txt
//     hello world
// Output in output.txt
//     o
// Input in input.txt
//     aabcd bcef
// Output in output.txt
//     b c

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    FILE *in = fopen("input.txt", "r");
    if (!in) return 1;

    char word1[101], word2[101];
    if (fscanf(in, "%100s %100s", word1, word2) != 2) {
        fclose(in);
        return 1;
    }
    fclose(in);

    // Считаем частоту символов в каждом слове
    int freq1[26] = {0};
    int freq2[26] = {0};

    for (int i = 0; word1[i]; i++) {
        if (islower(word1[i])) {
            freq1[word1[i] - 'a']++;
        }
    }

    for (int i = 0; word2[i]; i++) {
        if (islower(word2[i])) {
            freq2[word2[i] - 'a']++;
        }
    }

    // Ищем буквы, которые встречаются ровно один раз в каждом слове
    FILE *out = fopen("output.txt", "w");
    if (!out) return 1;

    int first = 1;
    for (int c = 0; c < 26; c++) {
        if (freq1[c] == 1 && freq2[c] == 1) {
            if (!first) fprintf(out, " ");
            fprintf(out, "%c", 'a' + c);
            first = 0;
        }
    }

    // Если ничего не найдено — файл будет пустой, что соответствует условию
    fclose(out);
    return 0;
}