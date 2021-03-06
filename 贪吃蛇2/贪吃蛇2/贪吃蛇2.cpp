#include "pch.h"
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#define map_height 20
#define map_width 80
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define N 65
int a = 1;
int score = 0;
int i, j, k;
char ch = RIGHT;
int grow = 0;
void gotoxy(int x, int y)//输出坐标 
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void color(int b)//颜色函数 
{
	HANDLE hConsole = GetStdHandle((STD_OUTPUT_HANDLE));
	SetConsoleTextAttribute(hConsole, b);
}
struct food//定义食物
{
	int x;
	int y;
}food;
struct poison//定义毒草
{
	int x;
	int y;
}poison;
struct snake//定义蛇
{
	int x[50];
	int y[50];
	int len;
	int speed;
}snake;
void init(void)//初始化
{
	srand(time(NULL));
	food.x = rand() % (map_width - 4)/2*2+2 ;
	food.y = rand() % (map_height - 2)+1 ;
	gotoxy(food.x, food.y);
	color(12);
	printf("●");
	poison.x = rand() % (map_width -4)/2*2+2;
	poison.y = rand() % (map_height- 2)+1;
	gotoxy(poison.x, poison.y);
	color(15);
	printf("●");
	snake.x[0] = map_width / 2;
	snake.y[0] = map_height / 2;
	gotoxy(snake.x[0], snake.y[0]);
	color(13);
	printf("★");
	for (k = 1; k < snake.len; k++)
	{
		snake.x[k] = snake.x[k - 1] + 1;
		snake.y[k] = snake.y[k];
		color(13);
		printf("★");
	}
}
void map(void)//人工手打地图(丢人)
{
	for (i = 1; i <= 20; i++)
	{
		for (j = 1; j <= 40; j++)
		{
			if (i == 1 || i == 20 || j == 1 || j == 40)
			{
				color(11);
				printf("■");
			}
			else
				printf("  ");
			if (j == 40)
				printf("\n");
		}
	}
	gotoxy(map_width/2,map_height/2);
}
void update_food(void)//更新食物
{
	if (snake.x[0] == food.x&&snake.y[0] == food.y)
	{
		srand(time(NULL));
		food.x = rand() % (map_width-4)/2*2+2;
		food.y = rand() % (map_height - 2)+1;
		gotoxy(food.x, food.y);
		color(12);
		printf("●");
		snake.len++;
		grow = 1;
		score += 10;
		gotoxy(N + 44, 12);
		color(10);
		printf("%d", score);
	}
}
void update_poison(void)//更新毒草
{
	if (snake.x[0] == poison.x&&snake.y[0] == poison.y)
	{
		srand(time(NULL));
		poison.x = rand() % (map_width  - 4) /2*2+2;
		poison.y = rand() % (map_height - 2)+1;
		gotoxy(poison.x, poison.y);
		color(15);
		printf("●");
		snake.len--;
		if (snake.len < 3)
		{
			gotoxy(1,map_height+1);
			printf("游戏结束了\n");
			system("pause");
			exit(0);
		}
		gotoxy(snake.x[snake.len], snake.y[snake.len]);
		printf(" ");
		score -= 10;
		gotoxy(N + 44, 12);
		color(10);
		printf("%d", score);
	}
}
void move(void)//移动函数
{
	if (_kbhit())
	{
		ch = _getch();
		if (_getch() == ' ')
			_getch() == 'g';//持续移动解决方案
	}
		if (!grow)
		{
			gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
			if (a <= 2)
			{
				gotoxy(snake.x[3],snake.y[3]);
				color(11);
				printf("■");
				a++;
			}
			else
			printf(" ");//不知为何开局会空格删掉边界线的临时补救措施
		}
		for (k = snake.len - 1; k > 0; k--)
		{
			snake.x[k] = snake.x[k - 1];
			snake.y[k] = snake.y[k - 1];
		}
		switch (ch)
		{
		case UP:snake.y[0] --; break;
		case DOWN:snake.y[0]++; break;
		case LEFT:snake.x[0] -= 2; break;
		case RIGHT:snake.x[0] += 2; break;
		default:break;
		}
	gotoxy(snake.x[0], snake.y[0]);
	color(13);
	printf("★");
	grow = 0;
	gotoxy(0, map_height);
}
int alive(void)//判断死活(撞墙或者撞到自身)
{
	if (snake.x[0] == 0 || snake.x[0] == map_width-2 || snake.y[0] == 0 || snake.y[0] == map_height-1)
	return 0;
	for (k = 1; k < snake.len; k++)
	{
		if (snake.x[k] == snake.x[0] && snake.y[k] == snake.y[0])
			return 0;
	}
	return 1;
}
void speed(void)//速度
{
	Sleep(200);//暂无
}
void Manual()//显示得分
{
	gotoxy(N + 30, 2);
	color(10);
	printf("按 W S A D 移动方向");
	gotoxy(N + 30, 3);
	color(12);
	printf("红圈是食物加分加长度");
	gotoxy(N + 30, 4);
	color(15);
	printf("白圈是毒草减分减长度");
	gotoxy(N + 30, 5);
	color(10);
	printf("长度小于3就GG了");
	gotoxy(N + 30, 8);
	color(11);
	printf("历史最高分为: ");
	color(12);
	gotoxy(N + 44, 8);
	printf("功能暂无");
	color(11);
	gotoxy(N + 30, 12);
	printf("你现在得分为: 0");
}
int main(void)
{
	snake.len = 3;
	map();
	init();
	Manual();
	while (1)
	{
		speed();
		update_food();
		update_poison();
		move();
		if (alive()!=1)
		break;
	}
	printf("游戏结束\n");
	system("pause");
	return 0;
}