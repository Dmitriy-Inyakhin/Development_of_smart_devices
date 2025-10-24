#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

//Доказать тождества А → В =!A||B

int main(int argc, char **argv) {
    setlocale(LC_ALL, "en_US.UTF-8");
    bool A, B;

    printf("\nДоказательства тождеств:\n\n");
    printf("  A, !A,  B,  A→B,  !A||B\t||\t");
    printf("  A, !A,  B, !B,  A↔B,  A&&B,  !A&&!B,  (A&&B)||(!A&&!B)\n");


    for (int i = 0; i<2; i++){
        A = i;
        for (int j = 0; j<2; j++) {
            B = j;
            printf("%3d ", A);
            printf("%3d ", !A);
            printf("%3d ", B);
            printf("%5d ", (A==true && B == false) ? (0) : (1));
            printf("%7d\t||\t", !A||B);

            printf("%3d ", A);
            printf("%3d ", !A);
            printf("%3d ", B);
            printf("%3d ", !B);
            printf("%5d", (A==B) ? (1) : (0));
            printf("%7d", A&&B);
            printf("%9d", !A&&!B);
            printf("%11d\n", (A&&B)||(!A&&!B));

        }
    }



    return 0;
}