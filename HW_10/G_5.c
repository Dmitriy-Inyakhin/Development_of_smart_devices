// G_5.c
// Заменить a на b
// В файле input.txt дана символьная строка не более 1000 символов.
// Необходимо заменить все буквы "а" на буквы "b" и наоборот, как заглавные,
// так и строчные. Результат записать в output.txt.

// Input format
//     Строка из маленьких и больших английских букв, знаков препинания и пробелов.
// Output format
//     Строка из маленьких и больших английских букв, знаков препинания и пробелов.
// Examples
// Input in input.txt
//     aabbccddABCD
// Output in output.txt
//     bbaaccddBACD

#include <stdio.h>
#include <stdlib.h>

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
    // printf("%d\n", some_number);

    if ((fp = fopen(output_fn, "w")) == NULL)
    {
        perror("Error occured while opening output file!");
        return 1;
    }

    for (int i = 0; i < count; ++i)
    {
        switch (line[i]) {
            case 'a': fputc('b', fp); break;
            case 'b': fputc('a', fp); break;
            case 'A': fputc('B', fp); break;
            case 'B': fputc('A', fp); break;
            default:  fputc(line[i], fp); break;
        }
    }
    fclose(fp);
    return 0;
}