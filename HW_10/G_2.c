// G_2.c
// Строка и цифры
// Считать число N из файла input.txt. Сформировать строку из N
// символов. N четное число, не превосходящее 26. На четных позициях
// должны находится четные цифры в порядке возрастания, кроме 0, на
// нечетных позициях - заглавные буквы в порядке следования в английском
// алфавите. Результат записать в файл output.txt

// Input format
//     Четное N ≤ 26
// Output format
//     Строка из английских букв и цифр
// Examples
//     Input in input.txt
//     10
// Output in output.txt
//     A2B4C6D8E2
// Input in input.txt
//     16
// Output in output.txt
//     A2B4C6D8E2F4G6H8

#include <stdio.h>
#include <stdlib.h>

const int LINE_WIDTH = 256;

int main(void)
{
    char *input_fn = "input.txt";
    char *output_fn = "output.txt";
    char line[LINE_WIDTH];
    int some_number = 0;
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
    some_number = atoi(line);
    some_number = (some_number >= 26) ? (26) : (some_number);

    c = 'A';

    fclose(fp);
    // printf("%d\n", some_number);

    if ((fp = fopen(output_fn, "w")) == NULL)
    {
        perror("Error occured while opening output file!");
        return 1;
    }
    count =2;
    for (int i = 1; i <= some_number; ++i)
    {
        if (i % 2 != 0)
        {
            fprintf(fp, "%c", c++);
        }
        else
        {
            count = (count > 8) ? (2) : (count);
            fprintf(fp, "%d", count);
            count +=2;
        }
    }
    fclose(fp);
    return 0;
}