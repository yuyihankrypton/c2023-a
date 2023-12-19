#include <stdio.h>
#include <stdlib.h>
#define bound 80
int main() {
    for(;;)
    {
        for(int i=1;i<=bound;i++)
        {
            system("cls");
            for (int j = 1; j < i; j++)
                printf(" ");
            printf("R");
            sleep(1);
        }
        for(int i=bound;i>=1;i--)
        {
            system("cls");
            for (int j = 1; j < i; j++)
                printf(" ");
            printf("R");
            sleep(1);
        }
    }
    return 0;
}
