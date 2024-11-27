
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define High 20  // ��Ϸ����ߴ�
#define Width 30
int q = 4;//���߿��Ա䳤
// ȫ�ֱ���
int moveDirection; 
int food_x, food_y; 
int canvas[High][Width] = { 0 };

void gotoxy(int x, int y) //����ƶ���(x,y)λ�õĺ�������
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}


void moveSnakeByDirection()//���������ƶ��ĺ���
{
    int i, j;
    for (i = 1; i < High - 1; i++)
        for (j = 1; j < Width - 1; j++)
            if (canvas[i][j] > 0)
                canvas[i][j]++;

    int oldTail_i, oldTail_j, oldHead_i, oldHead_j;
    int max = 0;

    for (i = 1; i < High - 1; i++)
        for (j = 1; j < Width - 1; j++)
            if (canvas[i][j] > 0)
            {
                if (max < canvas[i][j])
                {
                    max = canvas[i][j];
                    oldTail_i = i;
                    oldTail_j = j;
                }
                if (canvas[i][j] == 2)
                {
                    oldHead_i = i;
                    oldHead_j = j;
                }
            }

    int newHead_i, newHead_j;

    if (moveDirection == 1)   
    {
        newHead_i = oldHead_i - 1;
        newHead_j = oldHead_j;
    }
    if (moveDirection == 2)  
    {
        newHead_i = oldHead_i + 1;
        newHead_j = oldHead_j;
    }
    if (moveDirection == 3)  
    {
        newHead_i = oldHead_i;
        newHead_j = oldHead_j - 1;
    }
    if (moveDirection == 4)  
    {
        newHead_i = oldHead_i;
        newHead_j = oldHead_j + 1;
    }

 
    if (canvas[newHead_i][newHead_j] == -2)//�ж���ͷ�Ƿ�Ե�ʳ������������ʳ��
    {
        canvas[food_x][food_y] = 0;
        
        food_x = rand() % (High - 5) + 2;
        food_y = rand() % (Width - 5) + 2;
        canvas[food_x][food_y] = -2;
        q++;//��������
         
    }
    else 
        canvas[oldTail_i][oldTail_j] = 0;

   
    if (canvas[newHead_i][newHead_j] > 0 || canvas[newHead_i][newHead_j] == -1)//�ж����Ƿ�ײ���߽�
    {
        printf("��Ϸʧ�ܣ�\n");
        Sleep(2000);
        system("pause");
        exit(0);
    }
    else
        canvas[newHead_i][newHead_j] = 1;
}

void startup()  
{
    int i, j;

    //�߽�����
    for (i = 0; i < High; i++)
    {
        canvas[i][0] = -1;
        canvas[i][Width - 1] = -1;
    }
    for (j = 0; j < Width; j++)
    {
        canvas[0][j] = -1;
        canvas[High - 1][j] = -1;
    }

    //������
    canvas[High / 2][Width / 2] = 1;
     
    for (i = 1; i <= q && i <= 9; i++)
        canvas[High / 2][Width / 2 - i] = i + 1;

     
    moveDirection = 4;//��ʼ�ƶ�����

    food_x = rand() % (High - 5) + 2;
    food_y = rand() % (Width - 5) + 2;
    canvas[food_x][food_y] = -2;
}
//��ʼ��ʽ������,ʳ�������
void show()   
{
    gotoxy(0, 0); 
    int i, j;
    for (i = 0; i < High; i++)
    {
        for (j = 0; j < Width; j++)
        {
            if (canvas[i][j] == 0)
                printf(" ");    
            else if (canvas[i][j] == -1)
                printf("#");   
            else if (canvas[i][j] == 1)
                printf("@");    
            else if (canvas[i][j] > 1)
                printf("*");   
            else if (canvas[i][j] == -2)
                printf("F");   
        }
        printf("\n");
        
    }
    Sleep(100);
}

void updateWithoutInput()   {
    moveSnakeByDirection();//�����ƶ�
}

void updateWithInput()   //¼���û�����
{
    char input;
    if (_kbhit())  
    {
        char input = _getch();   

        if (input == 75)
        {
            moveDirection = 3;   
            moveSnakeByDirection();
        }
        else if (input == 77)
        {
            moveDirection = 4;   
            moveSnakeByDirection();
        }
        else if (input == 72)
        {
            moveDirection = 1; 
            moveSnakeByDirection();
        }
        else if (input == 80)
        {
            moveDirection = 2;   
            moveSnakeByDirection();
        }
    }
}
//��Ϸ��ʽ����
int main()
{
    
 
    startup();   
    while (1)  
    {
        show(); 
        updateWithoutInput();   
        updateWithInput();  
        printf("ͨ���������Ҽ��ƶ�");
    }
    return 0;
}
