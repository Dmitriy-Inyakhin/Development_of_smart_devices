// Префикс и суффикс

// На стандартном потоке ввода задаются две символьные строки, разделённые 
// символом перевода строки. Каждая из строк не превышает подлине 104. 
// В строках не встречаются пробельные символы. На стандартный поток вывода 
// напечатайте два числа, разделённых пробелом: первое число — длина 
// наибольшего префикса первойстроки, являющегося суффиксом второй; 
// второе число — наоборот, длина наибольшего суффикса первой строки, 
// являющегося префиксомвторой. Сравнение символов проводите с учётом 
// регистра (т.е. символы 'a' и 'A' различны).
// Input

//      don't_panic
//      nick_is_a_mastodon

// Output
//      3 3

// Input
//      monty_python
//      python_has_list_comprehensions

// Output
//      0 6

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Вычисление префикс-функции для КМП
void compute_prefix_function(const char *pattern, int len, int *pi) {
    pi[0] = 0;
    for (int i = 1; i < len; ++i) {
        int j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        pi[i] = j;
    }
}

// Поиск длины наибольшего префикса pattern, совпадающего с суффиксом text
int find_max_overlap(const char *text, int text_len, const char *pattern, int pattern_len) {
    if (pattern_len == 0 || text_len == 0) {
        return 0;
    }
    
    int *pi = (int *)malloc(pattern_len * sizeof(int));
    if (!pi) return 0;
    
    compute_prefix_function(pattern, pattern_len, pi);
    
    int j = 0;
    for (int i = 0; i < text_len; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (text[i] == pattern[j]) {
            ++j;
        }
    }
    
    free(pi);
    return j;
}

// Разворот строки
void reverse_string(char *dest, const char *src, int len) {
    for (int i = 0; i < len; ++i) {
        dest[i] = src[len - 1 - i];
    }
    dest[len] = '\0';
}

int main() {
    char s1[10002], s2[10002];
    
    // Чтение строк с учётом пустых строк
    if (!fgets(s1, sizeof(s1), stdin)) return 1;
    if (!fgets(s2, sizeof(s2), stdin)) return 1;
    
    // Удаление символа перевода строки \n (и \r для Windows)
    s1[strcspn(s1, "\r\n")] = '\0';
    s2[strcspn(s2, "\r\n")] = '\0';
    
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    
    // Случай пустых строк: ответ всегда (0, 0)
    if (len1 == 0 || len2 == 0) {
        printf("0 0\n");
        return 0;
    }
    
    // Часть 2: суффикс s1 = префикс s2
    int ans2 = find_max_overlap(s1, len1, s2, len2);
    
    // Часть 1: префикс s1 = суффикс s2 (через разворот)
    char *rev1 = (char *)malloc((len1 + 1) * sizeof(char));
    char *rev2 = (char *)malloc((len2 + 1) * sizeof(char));
    if (!rev1 || !rev2) {
        free(rev1);
        free(rev2);
        return 1;
    }
    
    reverse_string(rev1, s1, len1);
    reverse_string(rev2, s2, len2);
    
    int ans1 = find_max_overlap(rev1, len1, rev2, len2);
    
    printf("%d %d\n", ans1, ans2);
    
    free(rev1);
    free(rev2);
    return 0;
}