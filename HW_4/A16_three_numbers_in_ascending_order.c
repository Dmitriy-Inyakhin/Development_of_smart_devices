#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
    int a, b, c;

    if (scanf("%d %d %d", &a, &b, &c) != 3)
    {
        printf("Input error.");
        return 0;
    }

    (a < b && b < c) ? (printf("YES\n")) : (printf("NO\n"));

    return 0;
}