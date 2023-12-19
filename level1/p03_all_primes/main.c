#include <stdio.h>
#include <time.h>
int main() {
    int a[500],sum=2,b=0;
    a[1]=2,a[2]=3;
    printf("2\n3\n");
    for(int i=4;i<=1000;i++)
    {
        b=0;
        for(int j=1;j<=sum;j++)
            if(i%a[j]==0)
            {
                b=1;
                break;
            }
        if(b==0)
        {
            sum++;
            a[sum]=i;
            printf("%d\n",i);
        }
    }
    printf("Time used = %.2f\n",(double)clock()/CLOCKS_PER_SEC);
    return 0;
}