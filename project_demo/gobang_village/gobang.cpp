#define _CRT_SECURE_NO_WARNINGS 1	//在VS编译器用 scanf 等函数
//需要定义该符号

//需要的包含的头文件
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<iostream>
using namespace std;

//需要更改棋盘的大小或棋子的符号，改这里就可以了
#define ROW 12					//棋盘的行数
#define COL 15					//棋盘的列数
#define PIECE_ONE '*'			//玩家1 的棋子
#define PIECE_TWO '#'			//玩家2 的棋子

//初始化
void init_board(int board[ROW][COL], int row, int col);

//打印棋盘
void print_board(int board[ROW][COL], int row, int col);

//玩家下棋,并判断游戏是否结束，用返回值带回判断的结果
//第四个参数通过传递玩家的棋子，用来代表不同的玩家
char play_board(int board[ROW][COL],
	int row, int col,
	char piece);
    /*此为头文件*/
    #include"game.h"

void mnue()
{
	printf("******************\n");
	printf("***  1.player  ***\n");
	printf("***   0.exit   ***\n");
	printf("******************\n");
}

void game()
{
	char ret = 0;
	int a[ROW][COL];
	init_board(a, ROW, COL);//初始化
	print_board(a, ROW, COL);		//打印棋盘

	printf("********************\n");
	printf("本游戏通过坐标来下棋\n");
	printf("********************\n");

	while (1)
	{
		printf("玩家1 请下棋：>");
		ret = play_board(a, ROW, COL, PIECE_ONE);
		if (ret != 'C')
			break;

		system("cls");
		print_board(a, ROW, COL);

		printf("玩家2 请下棋：>");
		ret = play_board(a, ROW, COL, PIECE_TWO);
		if (ret != 'C')
			break;

		system("cls");
		print_board(a, ROW, COL);
	}

	if (ret == PIECE_ONE)
	{
		printf("恭喜玩家1，获胜\n");
	}
	else if (ret == PIECE_TWO)
	{
		printf("恭喜玩家2，获胜\n");
	}
	else
	{
		printf("很遗憾，没有决出胜负\n");
	}

	Sleep(5000);
	system("cls");
}

int main()
{
	int input = 0;
	do
	{
		//菜单
		mnue();
		printf("请输入：>");
		scanf("%d", &input);
		system("cls");

		//用户选择
		switch (input)
		{
		case 1:
			printf("欢迎来到五子棋，游戏开始\n");
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("输入错误，请重新输入\n");
			break;
		}
	} while (input);

	return 0;
}

void init_board(int board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			board[i][j] = ' ';
}

void print_board(int board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;

	//打印列号
	printf("  ");		//为了对齐
	for (i = 1; i <= COL; i++)
		printf(" %x  ", i);

	printf("\n");

	for (j = 0; j < row; j++)
	{
		//打印行号
		printf("%x ", j + 1);
		//打印 * | * | * 
		for (i = 0; i < col; i++)
		{
			printf(" %c ", board[j][i]);

			if (i < col - 1)
				printf("|");
		}
		printf("\n");

		//为了对齐
		printf("  ");
		//打印___|___|___ ,最后一行打印   |   |   
		for (i = 0; i < col; i++)
		{
			j == row - 1 ? printf("   ") : printf("___");

			if (i < col - 1)
				printf("|");
		}
		printf("\n");
	}
}


static char is_win(int board[ROW][COL], int row, int col, int x, int y, char piece)
{
	int i = 0;
	int j = 0;
	int k = 0;

	//记录当前棋盘的总棋子数
	static int count = 0;
	count++;

	//判断竖线
	for (i = x - 4; i <= x; i++)
	{
		if (i < 0 || i + 4 >= row)
			continue;

		for (j = 0; j < 5; j++)
		{
			if (board[i + j][y] != piece)
				break;
		}

		//判断是否获胜
		if (j == 5)
			return  piece;
	}

	//判断横线
	for (i = y - 4; i <= y; i++)
	{
		if (i < 0 || i + 4 >= col)
			continue;

		for (j = 0; j < 5; j++)
		{
			if (board[x][i + j] != piece)
				break;
		}

		//判断是否获胜
		if (j == 5)
			return  piece;
	}

	//判断正斜线
	for (i = x - 4, j = y - 4; i <= x; i++, j++)
	{
		if (i < 0 || j < 0 || i + 4 >= row || j + 4 >= col)
			continue;

		for (k = 0; k < 5; k++)
		{
			if (board[i + k][j + k] != piece)
				break;
		}

		//判断是否获胜
		if (k == 5)
			return  piece;
	}

	//判断副斜线
	for (i = x + 4, j = y - 4; i <= x; i++)
	{

		if (i >= row || j < 0 || i + 4 < 0 || j + 4 >= col)
			continue;

		for (k = 0; k < 5; k++)
		{
			if (board[i - k][j + k] != piece)
				break;
		}

		//判断是否获胜
		if (k == 5)
			return  piece;
	}

	//判断是否平局
	if (count == row * col)
		return 'Q';

	return 'C';
}

char play_board(int board[ROW][COL], int row, int col, char piece)
{
	int x = 0;
	int y = 0;

	while (1)
	{
		scanf("%d %d", &x, &y);
		//坐标合法
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			//坐标是否被占用
			if (board[x - 1][y - 1] != PIECE_ONE && board[x - 1][y - 1] != PIECE_TWO)
			{
				board[x - 1][y - 1] = piece;

				return is_win(board, row, col, x - 1, y - 1, piece);		//判断是否结束游戏
			}
			else
			{
				printf("输入错误，请重新输入：>");
			}
		}
		else
		{
			printf("坐标非法，请重新输入：>");
		}
	}
	int l;
	cin >> l;
}