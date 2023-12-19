#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
int main()
{
    system("chcp 65001");//修复中文乱码
    char s1[100][100],s2[100][100];
    int k=0;
    int goods[100]={0};
    FILE *p = fopen("D:/CLionProjects/level1/p10_warehouse/file.txt", "r");
    while(!feof(p)){
        k++;
        fscanf(p,"%s",s1[k]);
        fscanf(p,"%s",s2[k]);
    }
    FILE *q = fopen("D:/CLionProjects/level1/p10_warehouse/file.txt", "w");
    for(int i=1;i<=k;i++){
        int l2=strlen(s2[i]);
        for(int j=0;j<l2;j++){
            goods[i]*=10;
            goods[i]+=s2[i][j]-48;
        }
    }
    while(1){
        printf("输入1显示存货列表\n");
        printf("输入2入库\n");
        printf("输入3出库\n");
        printf("输入4退出程序\n");
        char ch;
        ch=getch();
        printf("\n");
        int n;
        n=ch-48;
        switch(n){
            case 1:{
                printf("货物型号    数量\n");
                for(int i=1;i<=k;i++){
                    printf("%d.%s    %d\n",i,s1[i],goods[i]);
                }
                printf("\n");
                break;
            }
            case 2:{
                printf("输入入库货物类别及数量\n");
                int num;
                gets(s1[++k]);
                scanf("%d",&num);
                goods[k]=num;
               break;
            }
            case 3:{
                printf("输入出库货物编号\n");
                int w;
                scanf("%d",&w);
                for(int i=w;i<k;i++){
                    strcpy(s1[i],s1[i+1]);
                    goods[i]=goods[i+1];
                }
                k--;
                break;
            }
            case 4:{
                for(int i=1;i<k;i++){
                    fprintf(q,"%s %d\n",s1[i],goods[i]);
                }
                fprintf(q,"%s %d",s1[k],goods[k]);
                fclose(p);
                return 0;
            }
            default:{
                continue;
            }
        }
    }
}