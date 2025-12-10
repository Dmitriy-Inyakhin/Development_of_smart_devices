// G_13.c
// Изменить расширение
// В файле input.txt записан полный адрес файла (возможно, без расширения).
// Необходимо изменить его расширение на ".html" и записать результат
// в файл output.txt.

// Input format
//     Строка состоящая из символов: a-z, A-Z, 0-9, /
// Output format
//     Исходная строка с измененным расширением.
// Examples
// Input in input.txt
//     /DOC.TXT/qqq
// Output in output.txt
//     /DOC.TXT/qqq.html
// Input in input.txt
//     /DOC.TXT/qqq.com
// Output in output.txt
//     /DOC.TXT/qqq.html

#include <stdio.h>
#include <string.h>

int main()
{
    // Открываем входной файл
    FILE *in = fopen("input.txt", "r");
    if (!in)
        return 1;

    char path[1001];
    if (!fgets(path, sizeof(path), in))
    {
        fclose(in);
        return 1;
    }
    fclose(in);

    // Удаляем '\n' в конце строки (если есть)
    size_t len = strlen(path);
    if (len > 0 && path[len - 1] == '\n')
    {
        path[len - 1] = '\0';
    }

    // Находим начало имени файла (после последнего '/')
    char *filename = strrchr(path, '/');
    if (filename == NULL)
    {
        filename = path;
    }
    else
    {
        filename++;
    }

    // Ищем последнюю точку в имени файла
    char *dot = strrchr(filename, '.');

    // Если точка есть и не является первым символом имени — обрезаем расширение
    if (dot != NULL && dot > filename)
    {
        *dot = '\0'; // завершаем строку на месте точки
    }

    // Дописываем ".html" через strcat
    strcat(path, ".html");

    // Записываем результат
    FILE *out = fopen("output.txt", "w");
    if (!out)
        return 1;

    fputs(path, out);
    fclose(out);

    return 0;
}