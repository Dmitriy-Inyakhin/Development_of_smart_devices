// G_1.c
// Три раза
// В файле input.txt дана строка. Вывести ее в файл output.txt
//  три раза через запятую и показать количество символов в ней.

// Input format
// Строка из английских букв и пробелов. Не более 100 символов.
// В конце могут быть незначащие переносы строк.
// Output format
// Исходная строка 3 раза подряд, через запятую пробел и количество
// символов в ней.
// Examples
// Input in input.txt
//  aab
// Output in output.txt
//  aab, aab, aab 3

#include <stdio.h>

const int LINE_WIDTH = 256;

int main(void)
{
    char *input_fn = "input.txt";
    char *output_fn = "output.txt";
    char line[LINE_WIDTH];
    char c;
    FILE *fp;
    int count = 0;

    if ((fp = fopen(input_fn, "r")) == NULL)
        {
            perror("Error occured while opening input file!");
            return 1;
        }
    while (((c = getc(fp)) != EOF) && (c != '\n'))
    {
        line[count++] = c;
    }
    line[count] = '\0';

    fclose(fp);

    if ((fp = fopen(output_fn, "w")) == NULL)
    {
        perror("Error occured while opening output file!");
        return 1;
    }

    for (int i = 0; i < 3; ++i)
    {
        if (i)
        {
            fprintf(fp, ", ");
        }
        fprintf(fp, "%s", line);
    }
    fprintf(fp, " %d", count);
    fclose(fp);
    return 0;
}