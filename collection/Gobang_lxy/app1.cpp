# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define ROW 8
# define COL 8
char a[ROW][COL];
int flag = 0;

//棋盘每两行作为一个整体
void hang(int i)
{

	int j = 0;

	for (; j <= COL - 1; j++)
	{
		if (j == COL - 1) {
			printf(" %c ", a[i][j]); break;
		}
		printf(" %c |", a[i][j]);
	}
	printf("\n");


	for (int x = 1; x <= ROW; x++)
	{
		if (x == ROW) {
			printf("---");
			printf("\n"); break;
		}
		if (x == 1)printf(" ");

		printf("---|");

	}


}
//棋盘
void qp()
{
	//数组为空格


	for (int a = 0; a <= ROW - 1; a++) {
		if (a == 0) printf(" ");

		if (a == ROW - 1) { printf(" %d ", a); printf("\n"); break; }
		printf(" %d |", a);

	}
	int i = 0;

	for (; i < COL; i++)
	{
		printf("%d", i);
		hang(i);
	}

}
void playermove(int c, int b)
{

	if (c >= 0 && c <= ROW - 1 && b >= 0 && b <= COL - 1)
	{
		if (a[c][b] == ' ')
			a[c][b] = '#';
		else
		{
			printf("被占用"); flag = 1;
		}

	}
	else
	{
		printf("出界无效"); flag = 1;
	}
	//printf("%c\n", a[c][b]);//调试成功

}
void computermove()
{
	int m, n;
	int t = 0;
	for (m = 0; m <= ROW - 1; m++)
	{
		for (n = 0; n <= COL - 1; n++)
		{
			if (a[m][n] == '#' && a[m][n + 1] == '#' && a[m][n + 2] == ' ')
			{
				a[m][n + 2] = '*'; t = 1; break;
			}
			if (a[m][n] == '#' && a[m][n + 1] == '#' && a[m][n - 1] == ' ')
			{
				a[m][n - 1] = '*'; t = 1; break;
			}
			if (a[m][n] == '#' && a[m + 1][n] == '#' && a[m + 2][n] == ' ')
			{
				a[m + 2][n] = '*'; t = 1; break;
			}
			if (a[m][n] == '#' && a[m + 1][n] == '#' && a[m - 1][n] == ' ')
			{
				a[m - 1][n] = '*'; t = 1; break;
			}
			if (a[m][n] == '#' && a[m + 1][n - 1] == '#' && a[m + 2][n - 2] == ' ')
			{
				a[m + 2][n - 2] = '*'; t = 1; break;
			}
			if (a[m][n] == '#' && a[m - 1][n + 1] == '#' && a[m - 2][n + 2] == ' ')
			{
				a[m - 2][n + 2] = '*'; t = 1; break;
			}
			if (a[m][n] == '#' && a[m + 1][n + 1] == '#' && a[m + 2][n + 2] == ' ')
			{
				a[m + 2][n + 2] = '*'; t = 1; break;
			}
			if (a[m][n] == '#' && a[m + 1][n + 1] == '#' && a[m - 1][n - 1] == ' ')
			{
				a[m - 1][n - 1] = '*'; t = 1; break;
			}


		}
		if (t == 1)break;
	}
	if (t != 1)
	{
		srand((unsigned int)time(NULL));
		do {
			m = rand() % ROW;
			n = rand() % COL;

			if (m >= 0 && m <= ROW - 1 && n >= 0 && n <= COL - 1 && a[m][n] == ' ')
			{
				a[m][n] = '*'; break;
			}
		} while (1);
	}


}
char Iswin() {
	int _flag = 0;

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < ROW - 3; j++)
			if (a[i][j] != ' ' && a[i][j] == a[i][j + 1] && a[i][j + 1] == a[i][j + 2] && a[i][j + 2] == a[i][j + 3] && a[i][j + 3] == a[i][j + 4])
			{
				return a[i][j]; _flag = 1; break;
			}
		if (_flag == 1)break;
	}
	for (int j = 0; j < COL; j++)
	{
		for (int i = 0; i < ROW - 3; i++)
			if (a[i][j] != ' ' && a[i][j] == a[i + 1][j] && a[i + 1][j] == a[i + 2][j] && a[i + 2][j] == a[i + 3][j] && a[i + 3][j] == a[i + 4][j])
			{
				return a[i][j]; _flag = 1; break;
			}
		if (_flag == 1)break;
	}
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (a[i][j] != ' ' && a[i][j] == a[i - 1][j + 1] && a[i - 1][j + 1] == a[i - 2][j + 2] && a[i - 2][j + 2] == a[i - 3][j + 3] && a[i - 3][j + 3] == a[i - 4][j + 4])
			{
				return a[i][j]; _flag = 1; break;
			}
			if (a[i][j] != ' ' && a[i][j] == a[i + 1][j + 1] && a[i + 1][j + 1] == a[i + 2][j + 2] && a[i + 2][j + 2] == a[i + 3][j + 3] && a[i + 3][j + 3] == a[i + 4][j + 4])
			{
				return a[i][j]; _flag = 1; break;
			}
		}
		if (_flag == 1)break;
	}
}
//游戏
void game() {
	for (int i = 0; i <= ROW - 1; i++)
		for (int j = 0; j <= COL - 1; j++)
			a[i][j] = ' ';//数组刷新全为空格


	qp();
	//玩家下棋
	while (1) {
		int c, b;
		char a = 0;
		printf("请玩家下棋");
		scanf_s("%d%d", &c, &b);
		playermove(c, b);

		if (flag == 1) { flag = 0; continue; }

		qp();
		//判断输赢
		a = Iswin();
		if (a == '#') {
			printf("你赢了"); break;
		}
		computermove();
		qp();
		a = Iswin();
		if (a == '*') { printf("你输了"); break; }
		//判断输赢
	}
}

int main() {
	//菜单
	int x = 0;
	do
	{
		printf("五子棋（弱智版）**********作者 刘昕雨\n");
		printf("按1开始游戏，按0退出游戏\n**********\n");
		scanf_s("%d", &x);
		if (x == 1) {
			game(); break;
		}

	} while (x);

	return 0;
}