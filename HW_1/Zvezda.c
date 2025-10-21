/*   *      1
    ***     3
   *****    5
  *******   7
   HHOHH
   ZZZZZ
   */

#include <stdio.h>
 
int main(int argc, char **argv) {
    int count = 1;
    int probel =0;
    for (int s=1; s<=4; s++) {
        for (int j = 3-probel; j > 0; j--) {
            printf(" ");
        }
        for (int i =1; i<=count; i++){
        printf("*");
        }
        printf("\n");
        count +=2;
        probel++;
    } 
    
    printf(" HHOHH\n");
    printf(" ZZZZZ\n");
}

