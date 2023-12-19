#include<stdio.h>
void Hanoi(int n,char a,char c,char b)
{
    if(n==1)
    {
        printf("%c->%c\n",a,b);
        return;
    }
    Hanoi(n-1,a,b,c);
    printf("%c->%c\n",a,b);
    Hanoi(n-1,c,a,b);
}
int main()
{
    char a,b,c;
    a='A';
    b='B';
    c='C';
    Hanoi(3,a,c,b);
    return 0;
}