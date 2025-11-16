// _D_25.c
// Переменная имеет тип unsigned int, необходимо

#include <stdio.h>
void binprintf(int);

int main(int argc, char **argv)
{
    unsigned int a = 0xAABBCCFF;
    unsigned int mask = -1;

    printf("a = %X\n", a);
    binprintf(a);
    // обнулить 3 младших бита числа.
    a = a >> 3;
    a = a << 3;
    printf("a = %X\n", a);
    binprintf(a);
    // a = aabbccf8
    printf("**********\n");
    // Поднять два младших бита в 4 байтном беззнаковом числе.
    a = 0xFFFFFF00, 
    
    // mask = 0xffffffff
    mask = mask >> (32 - 2);
    binprintf(mask);
    binprintf(a);
    a = a | mask;
    //printf("a = %x", a);
    binprintf(a);
    // a = ffffff03
}

void binprintf(int v)
{
    unsigned int mask = 1 << ((sizeof(int) << 3) - 1);
    while (mask)
    {
        printf("%d", (v & mask ? 1 : 0));
        mask >>= 1;
    }
    printf("\n");
}
