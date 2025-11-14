/*
D_6.c
Строка наоборот
Дана строка заканчивающаяся символом точка '.' Напечатать строку наоборот. 
Реализуйте рекурсивную функцию, которая считывает и печатает строку наоборот.
void reverse_string()
Формат входных данных
    Строка из английских букв и знаков препинания. В конце строки символ точка.
Формат результата
    Исходная строка задом наперед.
*/

#include <stdio.h>

void reverse_string(void);

int main(int argc, char **argv)
{
    reverse_string();
    printf("\n");
    return 0;
}

void reverse_string(void)
{
    int c = getchar();
    if(c == EOF) return;

    if(c != '.')
    {
        reverse_string();
        putchar(c);
    } else 
    {
        //putchar(c);
    }
    
}

