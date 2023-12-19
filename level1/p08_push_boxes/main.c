#include<stdio.h>
#include<conio.h>
#include<windows.h>
int winner=0;
int map[11][13]={
        {1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,1,0,0,0,1,0,1},
        {1,0,1,0,0,3,0,0,0,0,1,0,1},
        {1,0,1,0,3,0,3,3,3,0,1,1,1},
        {1,0,1,0,0,0,2,0,0,0,0,1,1},
        {1,1,1,0,0,1,1,1,0,3,0,1,1},
        {1,1,0,4,4,0,4,0,0,0,0,1,1},
        {1,1,0,4,4,0,4,4,3,0,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1}};//0空地；1墙；2人；3箱子；4目标位置
int drawmap();
int movement();
int ifwin();
int main()
{
    for(;;)
    {
        if(winner){break;}
        system("cls");
        drawmap();
        movement();
    }
    return 0;
}
int drawmap()
{
    ifwin();
    if(winner){
        return 0;
    }
    for(int i=0;i<11;i++){
        for(int j=0;j<13;j++){
            switch(map[i][j]){
                case 0:
                    printf(" "); //空地
                    break;
                case 1:
                    printf("#"); //墙
                    break;
                case 2:
                    printf("@"); //人
                    break;
                case 3:
                    printf("&"); //箱子
                    break;
                case 4:
                    printf("0"); //目标
                    break;
                case 6:
                    printf("$");//人和目标重叠
                    break;
                case 7:
                    printf("Q");//箱子和目标重叠
                    break;
            }
        }
        printf("\n");
    }
}
int movement()
{
    int count,caw=0,tui;
    for(int i=0;i<11;i++){
        for(int j=0;j<13;j++){
            if(map[i][j]==2||map[i][j]==6){
                count=i;
                caw=j;
            }
        }
    }
    tui=getch();
    switch(tui){
//        case 'W':
        case 72:
            // 1.人的前面是空地；
            // 2.人的前面是终点位置；
            // 3.人的前面是箱子
            //3.1.箱子的前面是空地；
            //3.2.箱子的前面是终点位置。
            if(map[count-1][caw]==0||map[count-1][caw]==4){
                map[count][caw]-=2;
                map[count-1][caw]+=2;
            }
            else if(map[count-1][caw]==3||map[count-1][caw]==7){
                if(map[count-2][caw]==0||map[count-2][caw]==4){
                    map[count][caw]-=2;
                    map[count-1][caw]-=1;
                    map[count-2][caw]+=3;
                }
            }
            break;
//        case 'S':
        case 80://键值
            if(map[count+1][caw]==0||map[count+1][caw]==4){
                map[count][caw]-=2;
                map[count+1][caw]+=2;
            }
            else if(map[count+2][caw]==0||map[count+2][caw]==4){
                if(map[count+1][caw]==3||map[count+1][caw]==7){
                    map[count][caw]-=2;
                    map[count+1][caw]-=1;
                    map[count+2][caw]+=3;
                }
            }
            break;
//        case 'A':
        case 75:
            if(map[count][caw-1]==0||map[count][caw-1]==4){
                map[count][caw]-=2;
                map[count][caw-1]+=2;
            }
            else if(map[count][caw-2]==0||map[count][caw-2]==4){
                if(map[count][caw-1]==3||map[count][caw-1]==7){
                    map[count][caw]-=2;
                    map[count][caw-1]-=1;
                    map[count][caw-2]+=3;
                }
            }
            break;
//        case 'D':
        case 77:
            if(map[count][caw+1]==0||map[count][caw+1]==4){
                map[count][caw]-=2;
                map[count][caw+1]+=2;
            }
            else if(map[count][caw+2]==0||map[count][caw+2]==4){
                if(map[count][caw+1]==3||map[count][caw+1]==7){
                    map[count][caw]-=2;
                    map[count][caw+1]-=1;
                    map[count][caw+2]+=3;
                }
            }
            break;

    }
}

int ifwin()
{
    int k=0;
    for(int i=0;i<11;i++){
        for (int j=0;j<13;j++){
            if(map[i][j]==3) k++;
        }
    }
    if(k==0){
        system("cls");
        printf("You win!\n");
        winner=1;
    }
}