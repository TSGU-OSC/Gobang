#include<stdio.h>

#define PLAYER1 1
#define PLAYER2 2
#define BLANK 0
#define MAX_ROW 15
#define MAX_COL 15
int chessboard[MAX_ROW][MAX_COL];

void initchessboard();
void printchessboard();
int is_win(int player);

void initchessboard()
{
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
			chessboard[i][j] = BLANK;
	}
}

void printchessboard()
{
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			if (chessboard[i][j] == BLANK)
				printf(".");
			else if (chessboard[i][j] == PLAYER1)
				printf("×");
			else if (chessboard[i][j] == PLAYER2)
				printf("○");
		}
		printf("\n");
	}
	printf("\n");
}
int is_win(int player)
{
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j <= MAX_COL - 5; j++)
		{
			int count = 0;
			for (int k = 0; k < 5; k++)
			{
				if (chessboard[i][j + k] == player)
					count++;
			}
			if (count == 5)
				return player;
		}
	}
	for (int i = 0; i < MAX_ROW - 5; i++)
	{
		for (int j = 0; j <= MAX_COL; j++)
		{
			int count = 0;
			for (int k = 0; k < 5; k++)
			{
				if (chessboard[i + k][j] == player)
					count++;
			}
			if (count == 5)
				return player;
		}
	}
	for (int i = 0; i < MAX_ROW - 5; i++)
	{
		for (int j = 0; j <= MAX_COL - 5; j++)
		{
			int count = 0;
			for (int k = 0; k < 5; k++)
			{
				if (chessboard[i + k][j + k] == player)
					count++;
			}
			if (count == 5)
				return player;
		}
	}
	for (int i = 0; i < MAX_ROW - 5; i++)
	{
		for (int j = 0; j <= MAX_COL; j++)
		{
			int count = 0;
			for (int k = 0; k < 5; k++)
			{
				if (chessboard[i + k][j - k] == player)
					count++;
			}
			if (count == 5)
				return player;
		}
	}
	return 0;
}

int main()
{
	initchessboard();
	int currentplayer = PLAYER1;
	while (1)
	{
		printchessboard();
		int row, col;
		printf("请输入行和列(0 - 14):");
		scanf_s("%d %d", &row, &col);
		if (row < 0 || row >= MAX_ROW || col < 0 || col >= MAX_COL)
		{
			printf("输入超出范围，请重新输入：\n");
			continue;
		}
		if (chessboard[row][col] != BLANK)
		{
			printf("该位置已有棋子，请重新输入：\n");
			continue;
		}
		chessboard[row][col] = currentplayer;
		int winner = is_win(currentplayer);
		if (winner)
		{
			printchessboard();
			printf("%d胜利\n", currentplayer);
			break;
		}
		else currentplayer = (currentplayer == PLAYER1) ? PLAYER2 : PLAYER1;
	}
	return 0;

}