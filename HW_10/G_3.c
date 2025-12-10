// G_3.c
// Последний номер символа
// В файле input.txt дана строка из не более 1000 символов. 
// Показать номера символов, совпадающих с последним символом 
// строки.
// Результат записать в файл output.txt

// Input format
//     Строка из не более 1000 символов
// Output format
//     Целые числа через пробел - номера символа, который совпадает 
// с последним символом строки.
//     Examples
// Input in input.txt
//     aabbcdb
// Output in output.txt
//     2 3

#include <stdio.h>
#include <stdlib.h>

const int LINE_WIDTH = 1000;

int main(void)
{
    char *input_fn = "input.txt";
    char *output_fn = "output.txt";
    char line[LINE_WIDTH];
    char end_number;
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
    end_number = line[count-1];
    line[count] = '\0';

    fclose(fp);
    // printf("%d\n", some_number);

    if ((fp = fopen(output_fn, "w")) == NULL)
    {
        perror("Error occured while opening output file!");
        return 1;
    }

    for (int i = 0; i < count-1; ++i)
    {
        if(i)
        {
             fprintf(fp, " ");
        }
        if (line[i] == end_number)
        {
            fprintf(fp, "%d", i);
        }
    }
    fclose(fp);
    return 0;
}