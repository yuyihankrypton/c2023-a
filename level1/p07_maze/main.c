#include <stdio.h>
#include <conio.h>
#include <windows.h>
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
struct Man
{
    int x;
    int y;
};
struct Man man = {1, 1, 1};
void CursorJump(int x, int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, pos);
}
int map[10][10]={
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,1,0,1},
        {1,1,1,1,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,0,1},
        {1,0,1,0,1,1,1,1,0,1},
        {1,0,1,0,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,1,2,1},
        {1,1,1,1,1,1,1,1,1,1},
        };
int main()
{
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            CursorJump(2 * j, i);
            switch (map[i][j]){
                case 0: {
                    printf(" ");
                    break;
                }
                case 1: {
                    printf("#");
                    break;
                }
                case 2: {
                    printf("*");
                    break;
                }
                default:
                    break;
            }
        }
    }
    CursorJump(2 * man.x, man.y);
    printf("@");
    for(;;)
    {
        int willx = 0;
        int willy = 0;
        char key = getch();
        switch (key)
        {
            case UP:
                willx = man.x;
                willy = man.y - 1;
                break;
            case DOWN:
                willx = man.x;
                willy = man.y + 1;
                break;
            case LEFT:
                willx = man.x - 1;
                willy = man.y;
                break;
            case RIGHT:
                willx = man.x + 1;
                willy = man.y;
                break;
            default:
                break;
        }
        switch (map[willy][willx])
        {
            case 0:
                man.x = willx;
                man.y = willy;
                printf("\b ");
                CursorJump(2 * man.x, man.y);
                printf("@");
                break;
            case 1:
                break;
            case 2:
                CursorJump(2 * 10 + 2, 0);
                system("cls");
                printf("You win!\n");
                getch();
                return 0;
            default:
                break;
        }
    }
}