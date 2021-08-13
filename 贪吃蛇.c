#define  _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <mmsystem.h>//自媒体头文件
#pragma comment(lib,"winmm.lib")//自媒体头文件
#define SNAKE_NUM 500    //蛇的最大节数


enum tes
{
	xgs,
	xgs1,
	xgs2,
};

enum dio    //蛇的方向
{
	up,
	down,
	left,
	right,
};

struct Snake
{
	int size; //蛇的节数
	int dir;    //蛇的方向
	int speed;  //移动速度
	POINT coor[SNAKE_NUM];//蛇的坐标
  
}snake;

struct food
{
	int x;
	int y;    
	int r;         //食物半径aaa
	bool flag;     //食物是否被吃
	DWORD color;   //食物颜色
}food;


//蛇的初始化
void GameInit()
{
	//BGM
	mciSendString("open ./res/lll.mp3", 0, 0, 0);
	mciSendString("play /res/lll.mp3 repeat", 0, 0, 0);
	//init初始化 graph 图形窗口
	//创建一个窗口
	initgraph(640, 480);
	//设置随机数
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
	//防止闪屏 双缓冲
	BeginBatchDraw();
	//背景颜色
	setbkcolor(RGB(28, 115, 119));
	cleardevice();
	//绘制蛇
	setfillcolor(GREEN);
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);

	}
	//绘制食物
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();//双缓冲结束
}

void snakeMove()     
{
	//身子跟着头
	for (int i = snake.size-1; i > 0 ; i--)
	{
		snake.coor[i] = snake.coor[i-1];
	}
	//蛇的移动
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
				snake.dir = up;//改变方向
			}
			break;
		case's':
		case'S':
		case'80':
			if (snake.dir != up)
			{
				snake.dir = down;//改变方向
			}
			
			break;
		case'a':
		case'A':
		case'75':
			if (snake.dir != right)
			{
				snake.dir = left;//改变方向
			}
			
			break;
		case'd':
		case'D':
		case'77':
			if (snake.dir != left)
			{
				snake.dir = right; //改变方向
			}
			
			break;
		case ' '://暂停
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
