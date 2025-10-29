#include <stdio.h>
int main(int args, char **argv) {
    int mount = 0;

    if(scanf("%d", &mount)!=1) {
        printf("Input error.");
        return 0;
    } 
// winter, spring, summer, autumn
    switch (mount)
    {
        case 12:
        case 1:
        case 2:
            printf("winter\n");
            break;
        case 3:
        case 4:
        case 5:
            printf("spring\n");
            break;
        case 6:
        case 7:
        case 8:
            printf("summer\n");
            break;
        case 9:
        case 10:
        case 11:
            printf("autumn\n");
            break;
    default:
        break;

    return 0;
}
}