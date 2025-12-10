// G_6.c
// Проверка на палиндром
// В файле input.txt символьная строка не более 1000 символов.
// Необходимо проверить, является ли она палиндромом (палиндром
//     читается одинаково в обоих направлениях). Реализовать
//     логическую функцию is_palindrom(str) и записать ответ в
//     файл output.txt.

// Input format
//     Строка из заглавных английских букв
// Output format
//     YES или NO
// Examples
// Input in input.txt
//     ABCDEF
// Output in output.txt
//     NO
// Input in input.txt
//     KAZAK
// Output in output.txt
//     YES

#include <stdio.h>
#include <stdbool.h>

const int LINE_WIDTH = 1000;

int main(void)
{
    char *input_fn = "input.txt";
    char *output_fn = "output.txt";
    char line[LINE_WIDTH];
    int some_number = 0;
    char c;
    FILE *fp;
    int count = 0;
    bool isPalindrom = true;

    if ((fp = fopen(input_fn, "r")) == NULL)
    {
        perror("Error occured while opening input file!");
        return 1;
    }

    while (((c = getc(fp)) != EOF) && (c != '\n'))
    {
        line[count++] = (char)c;
    }
    line[count] = '\0';

    fclose(fp);

    for(int i = 0; i<count/2; ++i)
    {
        if(line[i] != line[count-1-i])
        {
            isPalindrom = false;
            break;
        }

    }

    if ((fp = fopen(output_fn, "w")) == NULL)
    {
        perror("Error occured while opening output file!");
        return 1;
    }

    if (isPalindrom)
    {
        fprintf(fp, "YES");
    }
    else
    {
        fprintf(fp, "NO");
    }
    fclose(fp);

    return 0;
}