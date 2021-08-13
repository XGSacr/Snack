#define  _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <mmsystem.h>//��ý��ͷ�ļ�
#pragma comment(lib,"winmm.lib")//��ý��ͷ�ļ�
#define SNAKE_NUM 500    //�ߵ�������


enum dio    //�ߵķ���
{
	up,
	down,
	left,
	right,
};

struct Snake
{
	int size; //�ߵĽ���
	int dir;    //�ߵķ���
	int speed;  //�ƶ��ٶ�
	POINT coor[SNAKE_NUM];//�ߵ�����
  
}snake;

struct food
{
	int x;
	int y;    
	int r;         //ʳ��뾶aaa
	bool flag;     //ʳ���Ƿ񱻳�
	DWORD color;   //ʳ����ɫ
}food;


//�ߵĳ�ʼ��
void GameInit()
{
	//BGM
	mciSendString("open ./res/lll.mp3", 0, 0, 0);
	mciSendString("play /res/lll.mp3 repeat", 0, 0, 0);
	//init��ʼ�� graph ͼ�δ���
	//����һ������
	initgraph(640, 480);
	//���������
	srand(GetTickCount());
	snake.size = 5;
	snake.speed = 10;
	snake.dir = right;
	for (int i = 0; i <snake.size; i++)
	{
		snake.coor[i].x = 40 - 10 * i;
		snake.coor[i].y = 10;
	}
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = 10;
		food.flag = true;
}

void GameDraw()
{
	//��ֹ���� ˫����
	BeginBatchDraw();
	//������ɫ
	setbkcolor(RGB(28, 115, 119));
	cleardevice();
	//������
	setfillcolor(GREEN);
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);

	}
	//����ʳ��
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();//˫�������
}

void snakeMove()     
{
	//���Ӹ���ͷ
	for (int i = snake.size-1; i > 0 ; i--)
	{
		snake.coor[i] = snake.coor[i-1];
	}
	//�ߵ��ƶ�
		switch (snake.dir)
		{
		case up:
			snake.coor[0].y-= snake.speed;
			if (snake.coor[0].y+10==0)
			{
				snake.coor[0].y = 480;
			}
			break;
		case down:
			snake.coor[0].y+= snake.speed;
			if (snake.coor[0].y-10 == 480)
			{
				snake.coor[0].y = 0;
			}
			break;
		case left:
			snake.coor[0].x-= snake.speed;
			if (snake.coor[0].x == 0)
			{
				snake.coor[0].x = 640;
			}
			break;
		case right:
			snake.coor[0].x+= snake.speed;
			if (snake.coor[0].x == 640)
			{
				snake.coor[0].x = 0;
			}
			break;
		}
}

void anjian()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case'w':
		case'W':
		case'72':
			if (snake.dir != down)
			{
				snake.dir = up;//�ı䷽��
			}
			break;
		case's':
		case'S':
		case'80':
			if (snake.dir != up)
			{
				snake.dir = down;//�ı䷽��
			}
			
			break;
		case'a':
		case'A':
		case'75':
			if (snake.dir != right)
			{
				snake.dir = left;//�ı䷽��
			}
			
			break;
		case'd':
		case'D':
		case'77':
			if (snake.dir != left)
			{
				snake.dir = right; //�ı䷽��
			}
			
			break;
		case ' '://��ͣ
				while (1)
				{
					if (_getch() == ' ')
						return;
				}
	    }
	}
}

void eatfood()
{
	if (food.flag && snake.coor[0].x >= food.x - food.r && snake.coor[0].x <= food.x + food.r &&
		snake.coor[0].y >= food.y - food.r && snake.coor[0].y <= food.y + food.r)
	{
		food.flag = false;
		snake.size++;
	}
	if (!food.flag)
	{
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = 10;
		food.flag = true;
	}
}



int main()
{
	GameInit();
	/*GameDraw();*/
	
	while (1)
	{
		eatfood();
		
		GameDraw();
		snakeMove();
		anjian();
		Sleep(50);	
	}
	
	return 0;
}