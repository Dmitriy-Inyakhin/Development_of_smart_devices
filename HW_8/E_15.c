// E_15.c
// Положительные и отрицательные
// Считать 10 чисел в диапазоне от -500 до 500 и разложить 
// по двум массивам: в одни помещать только положительные, 
// во второй - только отрицательные. Числа, равные нулю, 
// игнорировать. Вывести на экран все элементы обоих массивов.
// Input format
//     10 целых чисел через пробел.
// Output format
//     Сперва положительные числа, потом отрицательыне числа, через пробел.
// Examples
// Input
//     5 -4 0 1 4 -3 -3 3 0 2
// Output
//     5 1 4 3 2 -4 -3 -3

#include <stdio.h>
#define SIZE 10
void print_array(int size, int ar[]);
int sort_arr_poz_neg(int size, int ar[]);


int main(int args, char **argv)
{
    int var[SIZE] = {0};
    
    for (int i = 0; i < SIZE; i++)
    {
        if (scanf("%d", &var[i]) != 1)
        {
            fprintf(stderr, "Input error!\n");
            return 0;
        }
    }
    print_array(sort_arr_poz_neg(sizeof(var) / sizeof(var[0]), var), var);
    return 0;
}

void print_array(int size, int ar[])
{
    for (int i = 0; i < size; ++i)
    {
        if (i > 0)
        {
            putchar(' ');
        }
        printf("%d", ar[i]);
    }
    putchar('\n');
}

int sort_arr_poz_neg(int size, int ar[])
{
    int var_poz[SIZE] = {0};
    int count_poz = 0;
    int var_neg[SIZE] = {0};
    int count_neg = 0;
    for(int i = 0; i<size; ++i)
    {
        if(ar[i] >0)
        {
            var_poz[count_poz++] = ar[i];
        }
        if(ar[i] < 0)
        {
            var_neg[count_neg++] = ar[i]; 
        }
        ar[i] = 0;
    }
    for(int i = 0; i< count_poz; i++)
    {
        ar[i] = var_poz[i];
    }
    for(int i = count_poz; i< count_poz+count_neg; i++)
    {
        ar[i] = var_neg[i-count_poz];
    }
    return count_poz+count_neg;
}
