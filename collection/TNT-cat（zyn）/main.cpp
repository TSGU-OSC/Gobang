#include<graphics.h>
#include<iostream>
#include<Windows.h>
#include<stdlib.h>



IMAGE bk;
IMAGE blackchess;
IMAGE whitechess;

#define ROW 15
#define COL 15
#define GRID_SIZE 39   

int chessMap[15][15];//��¼���ӷ�ֹ�ظ�����
int pan[15][15];//��¼�������
int scoremap[15][15];//��¼��������Ȩ������
int num = 1;    // Chess_white = -1; Chess_black = 1;

MOUSEMSG m;


void draw_line()
{
	setlinecolor(BROWN);
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			int x = j * GRID_SIZE + 220;
			int y = i * GRID_SIZE + 30;

			line(x, y, x, 570);
			line(x, y, 760, y);
		}
	}
}
void draw_point()
{
	setfillcolor(BLACK);
	fillcircle(337, 147, 5);
	fillcircle(337, 459, 5);
	fillcircle(493, 303, 5);
	fillcircle(649, 147, 5);
	fillcircle(649, 459, 5);

}
void Chess_init()
{

	initgraph(975, 600);
	loadimage(&bk, _T("Resource/images/bk.png"));
	putimage(0, 0, &bk);
	loadimage(&blackchess, _T("Resource/images/blackchess.png"));
	loadimage(&whitechess, _T("Resource/images/whitechess.png"));
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++) {
			chessMap[i][j] = 0;
			pan[i][j] = 0;
		}
	
}
//�ж����λ���Ƿ�����Чλ��
int  chess_down()
{

	m = GetMouseMsg();
	if (m.x >= 202 && m.y >= 18 && m.x <= 778 && m.y <= 588)
		return 1;
	else
		return 0;
}

int change_piece(int x, int y)
{
	if (chessMap[x][y] != 0)//����
		return 0;
	else //û�ӵĻ��ͷ���1����¼����
		chessMap[x][y] = num;
		pan[x][y] = num;
	return 1;
}
void chess_xy(double i,double j)
{
	m = GetMouseMsg();
	double z, c;
	int x, y;
	//���������������е�xyλ��
	z = (i - 220.0) / 39.0;
	if (z > (int)z + 0.5)
	{
		x = (int)z + 1;
	}
	else
	{
		x = (int)z;
	}
	c = (j - 30.0) / 39.0;
	if (c > (int)c + 0.5)
	{
		y = (int)c + 1;
	}
	else
	{
		y = (int)c;
	}

	//���������ɫ
	if (num == 1)
	{
		setfillcolor(BLACK);
	}
	else if (num == -1)
	{
		setfillcolor(WHITE);
	}
	
		//�жϸõ�ʹ��������,û��������
	
	if (change_piece(x, y) == 0)
			return;
		
	else if (chess_down() == 1)
	{
		fillcircle(220+x*39, 30+y*39, 18);
		num *= -1;
	}
}

//������Ȩ����·��������
void ai_score()
{
	

	//��������
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			scoremap[i][j] = 0;
		}
	}

	//quanzhong
	for (int row=0; row < 15; row++)
	{
		for (int col=0; col < 15; col++)
		{
			if (pan[row][col] != 0)
				continue;
			//�����I�������J�ĸ�����
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 0; y++)
				{
					if (x == 0 && y == 0) continue;
					if (y == 0 && x != 1)continue;

					int blacknum = 0;
					int whitenum = 0;
					int emptynum = 0;
					//����������Ӹ�4����������
					for (int i = 0; i <= 3; i++)
					{
						int currow = row + i * y;
						int curcol = col + i * x;

						if (currow >= 0 && currow <= 15 && curcol >= 0 && curcol <= 15 && pan[currow][curcol] == 1)
						{
							blacknum++;
						}
						else if (currow >= 0 && currow <= 15 && curcol >= 0 && curcol <= 15 && pan[currow][curcol] == 0)
						{
							emptynum++;
						}
						else
						{
							break;
						}

					}
					//���������4����������
					for (int i = 0; i <= 3; i++)
					{
						int currow = row - i * y;
						int curcol = col - i * x;

						if (currow >= 0 && currow <= 15 && curcol >= 0 && curcol <= 15 && pan[currow][curcol] == 1)
						{
							blacknum++;
						}
						else if (currow >= 0 && currow <= 15 && curcol >= 0 && curcol <= 15 && pan[currow][curcol] == 0)
						{
							emptynum++;
							break;
						}
						else
						{
							break;
						}
					}
					//Ȩ�ظ�ֵ
					if (blacknum == 1) {
						scoremap[row][col] += 10;
					}
					else if (blacknum == 2) {
						if (emptynum == 1) {
							scoremap[row][col] += 30;
						}
						else if (emptynum == 2) {
							scoremap[row][col] += 40;
						}
					}
					else if (blacknum == 3) {
						if (emptynum == 1) {
							scoremap[row][col] = 60;
						}
						else if (emptynum == 2) {
							scoremap[row][col] = 5000;
						}
					}
					else if (blacknum == 4) {
						scoremap[row][col] == 20000;
					}

					//����bai�����Ӹ�4����������
					for (int i = 1; i <= 4; i++)
					{
						int currow = row + i * y;
						int curcol = col + i * x;

						if (currow >= 0 && currow < 15 && curcol >= 0 && curcol < 15 && pan[currow][curcol] == -1)
						{
							whitenum++;
						}
						else if (currow >= 0 && currow < 15 && curcol >= 0 && curcol < 15 && pan[currow][curcol] == 0)
						{
							emptynum++;
							break;
						}
						else
						{
							break;
						}

					}
					//����bai����4����������
					for (int i = 1; i <= 4; i++)
					{
						int currow = row - i * y;
						int curcol = col - i * x;

						if (currow >= 0 && currow < 15 && curcol >= 0 && curcol < 15 && pan[currow][curcol] == -1)
						{
							whitenum++;
						}
						else if (currow >= 0 && currow < 15 && curcol >= 0 && curcol < 15 && pan[currow][curcol] == 0)
						{
							emptynum++;
							break;
						}
						else
						{
							break;
						}
					}
					//Ȩ�ظ�ֵ
					if (whitenum == 0) {
						scoremap[row][col] += 5;
					}
					else if (whitenum == 1) {
						scoremap[row][col] += 10;

					}
					else if (whitenum == 2) {
						if (emptynum == 1) {
							scoremap[row][col] += 25;
						}
						else if (emptynum == 2) {
							scoremap[row][col] += 50;
						}
					}
					else if (whitenum == 3) {
						if (emptynum == 1) {
							scoremap[row][col] += 55;
						}
						else if (emptynum == 2) {
							scoremap[row][col] += 10000;
						}
					}
					else if (whitenum == 4) {
						scoremap[row][col] += 30000;
					}
				}
			}
		}
	}

	
}
void ai_go()
{
	ai_score();

	int maxscore = 0;

	int m, n;
	for (int col = 0; col < 15; col++) 
	{
		for (int row = 0; row < 15; row++)
		{

				if (scoremap[col][row] > maxscore)
				{
					maxscore = scoremap[col][row];
					m = col;
					n = row;

				}
				
		}
	}
	
	if (chess_down() == 1&& change_piece(m, n) == 1)
	{
		setfillcolor(WHITE);
		fillcircle(220 + m * 39, 30 + n * 39, 18);
		num *= -1;
	}
}

int five_chess(int x,int y)
{
	int n = 1;
	/*����*/
	for (int i = x - 4; i >= 0 && chessMap[x][y] == chessMap[i][y] && i < x + 4 && i < 15; i++)
	{
		n++;
		if (chessMap[x][y] != chessMap[i][y])n = 1;
	}
	if (n >= 5)return 1;

	/*����*/
	for (int j = y - 4; j >= 0 && chessMap[x][y] == chessMap[x][j] && y < 15; j++)
	{
		n++;
		if (chessMap[x][y] != chessMap[x][j])n = 1;
	}
	if (n >= 5)return 1;

	/*��������*/
	for (int i = x - 4, j = y - 4; i >= 0 && j >= 0 && i < 15 && j < 15 && chessMap[x][y] == chessMap[i][j]; i++, j++)
	{
		n++;
		if (chessMap[x][y] != chessMap[i][j])n = 1;
	}
	if (n >= 5)return 1;

	/*��������*/
	for (int i = x - 4, j = y + 4; i >= 0 && j <= 15 && i <= 15 && j >= 0 && chessMap[x][y] == chessMap[i][j]; i++, j--)
	{
		n++;
		if (chessMap[x][y] != chessMap[i][j])n = 1;
	}
	if (n >= 5)return 1;

}
int  check_over()
{
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
			{
				if (chessMap[i][j] == 0)
					continue;
				if (five_chess(i, j) == 1)
					return 1;
			}
}

void chess_map()
{

}
int main() 
{
	Chess_init();
	draw_line();
	draw_point();
	while (1)
	{
		m = GetMouseMsg();
		Chess_init;
		//man();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			chess_xy(m.x, m.y);
			ai_go();
			
		}
		if (check_over() == 1)
		{
			settextcolor(RED);
			settextstyle(42, 20, _T("����"));
			outtextxy(350, 350, _T("YOU WIN!"));
			system("pause");
			return 0;
		}
	}
	return 0;
}