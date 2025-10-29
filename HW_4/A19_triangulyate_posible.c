#include <stdio.h>
#include <math.h>

int main(int args, char **argv) {
    double a, b, c;

    if(scanf("%lf %lf %lf", &a, &b, &c)!=3) {
        printf("Input error.");
        return 0;
    }

    ((a < b+c) && (b < a+c) && (c<a+b)) ? (printf("YES\n")) : (printf("NO\n"));

    return 0;
}