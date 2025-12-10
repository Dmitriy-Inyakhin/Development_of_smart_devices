// G_11.c
// Заканчивается на a
// В файле input.txt дано предложение. Необходимо определить, сколько
// слов заканчиваются на букву 'а'. Ответ записать в файл output.txt.

// Input format
//     Строка из английских букв и пробелов не более 1000 символов.
// Output format
//     Одно целое число
// Examples
// Input in input.txt
//     Mama mila ramu
// Output in output.txt
//     2

#include <stdio.h>
#include <string.h>

int main()
{
    FILE *in = fopen("input.txt", "r");
    if (!in)
        return 1;

    char s[1001];
    if (!fgets(s, sizeof(s), in))
    {
        fclose(in);
        return 1;
    }
    fclose(in);

    // Удаляем '\n' в конце строки
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n')
    {
        s[len - 1] = '\0';
    }

    int count = 0;
    int i = 0;
    int n = (int)strlen(s);

    while (i < n)
    {
        // Пропускаем пробелы
        while (i < n && s[i] == ' ')
        {
            i++;
        }
        if (i >= n)
            break;

        int start = i;
        while (i < n && s[i] != ' ')
        {
            i++;
        }
        int end = i - 1;

        if (s[end] == 'a')
        {
            count++;
        }
    }

    FILE *out = fopen("output.txt", "w");
    if (!out)
        return 1;

    fprintf(out, "%d", count);
    fclose(out);

    return 0;
}