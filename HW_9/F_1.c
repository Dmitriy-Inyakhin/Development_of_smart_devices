// F_1.c
// Сортировка по взрастанию

// Написать только одну функцию, которая сортирует массив
// по возрастанию. Необходимо реализовать только одну функцию,
// всю программу составлять не надо.
// Строго согласно прототипу. Имя функции и все аргументы
// должны быть: void sort_array(int size, int a[]).
// Всю программу загружать не надо, только одну эту функцию.
// Можно просто закомментировать текст всей программы, кроме
// данной функции.
// Input format
//     Функция принимает на вход, первый аргумент - размер массива,
// второй аргумент - адрес нулевого элемента.
// Output format
//     Функция ничего не возвращает. Производит сортировку переданного
// ей массива по возрастанию.

// #include <stdio.h>
// #define SIZE 20
// void print_array(int size, int ar[]);
// void sort_array(int size, int ar[]);

// int main(int args, char **argv)
// {
//     int var[SIZE] = {0};

//     for (int i = 0; i < SIZE; i++)
//     {
//         if (scanf("%d", &var[i]) != 1)
//         {
//             fprintf(stderr, "Input error!\n");
//             return 0;
//         }
//     }
//     sort_array(sizeof(var) / sizeof(var[0]), var);
//     print_array(sizeof(var) / sizeof(var[0]), var);
//     return 0;
// }

// void sort_array(int size, int ar[])
// {
//     int i = 0;
//     _Bool flag;
//     do
//     {
//         flag = 0;
//         for (int j = size - 2; j >= i; j--)
//         {
//             if (ar[j] > ar[j + 1])
//             {
//                 int temp = ar[j];
//                 ar[j] = ar[j + 1];
//                 ar[j + 1] = temp;
//                 flag = 1;
//             }
//         }
//         i++;
//     } while (flag);
// }

// void print_array(int size, int ar[])
// {
//     for (int i = 0; i < size; ++i)
//     {
//         if (i > 0)
//         {
//             putchar(' ');
//         }
//         printf("%d", ar[i]);
//     }
//     putchar('\n');
// }

#include <stdio.h>

//функция ввода последовательности чисел из буфера
int Input(int arr[], int n)
{
    int i =0, num;
    while (i < n && scanf("%d", &num) == 1)
        arr[i++] = num;
    return i;
}

// функция проверяет является ли символ цифрой
int isDigit(char c) 
{
    return ((c >= '0') && (c <= '9'));
}

//функция ввода последовательности чисел
int InputGet(int arr[], int n)
{
    int i=0;
    char c;
    while ((c = getchar()) != '\n')
    {
        if (isDigit(c))
        {
            int number = 0;
            do
            {
                number = number * 10 + c - '0';
                c = getchar();
            } while (isDigit(c));
            arr[i++] = number;
            if (c == '\n')
                break;
        }
    }
    return i;
}

// функция сортировки пузырьком
void BubbleSort(int arr[], int n)
{
    int i = 0;
    int j = 0;
    int temp = 0;
    for (i = 0; i < n-1; ++i)
    {
        for (j = 0; j < n-i-1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j +1] = temp;
            }
        }
    }
}

//функция печати массива
void Print(int arr[], int len)
{
    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


int main()
{
    enum
    {
        BUFFER_SIZE = 20
    };

    int buffer[BUFFER_SIZE];                    //объявляем массив целых чисел
    int size = Input(buffer, BUFFER_SIZE);   //вычисляеем размер массива
    printf("size =%d\n", size);                 // печать размера массива
    BubbleSort(buffer, size);                   //сортировка массива
    Print(buffer, size);                        //печать массива
    return 0;
}
