# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define ROW 8
# define COL 8
char a[ROW][COL];
int flag = 0;

//����ÿ������Ϊһ������
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
//����
void qp()
{
	//����Ϊ�ո�


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
			printf("��ռ��"); flag = 1;
		}

	}
	else
	{
		printf("������Ч"); flag = 1;
	}
	//printf("%c\n", a[c][b]);//���Գɹ�

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
//��Ϸ
void game() {
	for (int i = 0; i <= ROW - 1; i++)
		for (int j = 0; j <= COL - 1; j++)
			a[i][j] = ' ';//����ˢ��ȫΪ�ո�


	qp();
	//�������
	while (1) {
		int c, b;
		char a = 0;
		printf("���������");
		scanf_s("%d%d", &c, &b);
		playermove(c, b);

		if (flag == 1) { flag = 0; continue; }

		qp();
		//�ж���Ӯ
		a = Iswin();
		if (a == '#') {
			printf("��Ӯ��"); break;
		}
		computermove();
		qp();
		a = Iswin();
		if (a == '*') { printf("������"); break; }
		//�ж���Ӯ
	}
}

int main() {
	//�˵�
	int x = 0;
	do
	{
		printf("�����壨���ǰ棩**********���� �����\n");
		printf("��1��ʼ��Ϸ����0�˳���Ϸ\n**********\n");
		scanf_s("%d", &x);
		if (x == 1) {
			game(); break;
		}

	} while (x);

	return 0;
}