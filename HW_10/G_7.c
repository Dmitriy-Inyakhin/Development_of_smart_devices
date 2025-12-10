// G_7.c
// Количество букв
// В файле input.txt считать символьную строку, не более 10 000
// символов. Посчитать количество строчных (маленьких) и прописных
// (больших) букв в введенной строке. Учитывать только английские
// буквы. Результат записать в файл output.txt.

// Input format
//     Строка состоящая из английских букв, цифр, пробелов и знаков препинания.
// Output format
//     Два целых числа. Количество строчных букв и количество заглавных букв.
// Examples
// Input in input.txt
//     aabbAB
// Output in output.txt
//     4 2
// Input in input.txt
//     HELLO WORLD
// Output in output.txt
//     0 10

#include <stdio.h>

const int LINE_WIDTH = 10000;

int main(void)
{
    char *input_fn = "input.txt";
    char *output_fn = "output.txt";
    char line[LINE_WIDTH];
    int some_number = 0;
    char c;
    FILE *fp;
    int count = 0;
    int count_a = 0;
    int count_A = 0;

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

    for (int i = 0; i < count; ++i)
    {
        if (line[i] >= 'a' && line[i] <= 'z')
        {
            count_a++;
        }
        else if (line[i] >= 'A' && line[i] <= 'Z')
        {
            count_A++;
        }
    }

    if ((fp = fopen(output_fn, "w")) == NULL)
    {
        perror("Error occured while opening output file!");
        return 1;
    }

    fprintf(fp, "%d ", count_a);
    fprintf(fp, "%d\n", count_A);

    fclose(fp);

    return 0;
}