#include<stdio.h>
#include<string.h>
char string[5000],s1[5000],s2[5000];
void encrypt(char string[],char s1[],int *l){
    for(int i=0;i<*l;i++){
        s1[i]=(string[i]+66)%128;
    }
}
void decrypt(char string[],char s2[],int *l){
    for(int i=0;i<*l;i++){
        s2[i]=(string[i]-66)%128;
    }
}
int main() {
    scanf("%s",string);
    int l=strlen(string);
    encrypt(string,s1,&l);
    decrypt(string,s2,&l);
    printf("%s\n%s\n",s1,s2);
    return 0;
}