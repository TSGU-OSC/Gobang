#include<easyx.h>
#include<iostream>
#include<mmstream.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
#define GRID_W 25
#define ROW 15
#define COL 15
#define SPACE (3*GRID_W)

void Chongkai();
bool judge(int r, int c);
enum Chess
{
	None,
	Black,
	White
};
int map[ROW][COL];
class Pos
{
public:
	 int row;
	 int col;
	//bool isShow;
	int player;		
}p1 = {-10,-10,Black};
void qizi()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (map[i][j] == Black)
			{
				setfillcolor(BLACK);
				solidcircle(j * GRID_W + SPACE, i * GRID_W + SPACE, 10);
			}
			else if (map[i][j] == White)
			{
				setfillcolor(WHITE);
				solidcircle(j * GRID_W + SPACE, i * GRID_W + SPACE, 10);
			}
		}
	}
}
void Draw()
{
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	for (int i = 0; i < 15; i++)
	{
		line(SPACE, i * GRID_W + SPACE, 14 * GRID_W + SPACE, i * GRID_W + SPACE);
		line(i * GRID_W + SPACE, SPACE, i * GRID_W + SPACE, 14 * GRID_W + SPACE);

	}
	setlinestyle(PS_SOLID, 2);
	rectangle(SPACE, SPACE, SPACE + 14 * GRID_W, SPACE + 14 * GRID_W);
	settextstyle(20, 0, "����");
	settextcolor(BLACK);
	outtextxy(450, 35, "����");
}
/*void mouseMoveMsg(ExMessage* msg)
{
	p1.isShow = false;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			int gridx = j * GRID_W + SPACE;
			int gridy = i * GRID_W + SPACE;
			if (abs(msg->x - gridx) <= 12 && abs(msg->y - gridy) <= 12)
			{
				p1.isShow = true;
				p1.row = i;
				p1.col = j;

			}
		}
	}
}
*/

void mousePressMsg(ExMessage* msg)
{
	
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			int gridx = j * GRID_W + SPACE;
			int gridy = i * GRID_W + SPACE;
			if (abs(msg->x - gridx) <= 12 && abs(msg->y - gridy) <= 12)
			{
				p1.row = i;
				p1.col = j;

			}
		}
	}
	if (msg->x <= 490 && msg->x >= 450 && msg->y <= 55 && msg->y >= 35)
	{
		cout << "������" << endl;
		map[p1.row][p1.col] = 0;
		clearcircle(p1.col * GRID_W + SPACE, p1.row * GRID_W + SPACE, 10);
		p1.player = (p1.player == Black ? White : Black);
	}
	if (msg->message == WM_LBUTTONDOWN)
	{
		if (map[p1.row][p1.col] == None)
		{
			if (p1.player == 1)
			{
				cout << "Black" << "("<<p1.row<<","<<p1.col<<")"<<endl;
			}
			else { cout << "White" << "(" << p1.row << "," << p1.col << ")" << endl; }
			if (msg->x > SPACE && msg->x < 14 * GRID_W + SPACE && msg->y > SPACE && msg->y < 14 * GRID_W + SPACE)
			{
				map[p1.row][p1.col] = p1.player;
			}
			if (judge(p1.row, p1.col))
			{
				int msgboxID;
				msgboxID =MessageBox(GetHWnd(), "��Ӯ�ˣ��Ƿ����¿�ʼ��", "hit", MB_OKCANCEL);
				switch (msgboxID)
				{
				case IDOK:
					Chongkai();
					p1.player = White;
					clearrectangle(SPACE, SPACE, 14 * GRID_W + SPACE, 14 * GRID_W + SPACE);
					break;
				case IDCANCEL:
					exit(0);
					break;
				default:
					break;
				}
				//exit(0);
			}
			cout << "msgx=" << msg->x << "msgy=" << msg->y << endl;
			if (msg->x > SPACE && msg->x < 14 * GRID_W + SPACE && msg->y > SPACE && msg->y < 14 * GRID_W + SPACE)
			{
				cout << p1.player << endl;
				p1.player = (p1.player == Black ? White : Black);
			}
		}
	}
}
bool judge(int r,int c)
{
	int who = p1.player;
	int n, m;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (map[i][j] == who && map[i][j + 1] == who && map[i][j + 2] == who && map[i][j + 3] == who && map[i][j + 4] == who)
			{
				qizi();
				cout << "��������" << endl;
				return true;
			}
		}
	}
	for (int j = 0; j < 15; j++)
	{
		for (int i = 0; i < 15; i++)
		{
			if (map[i][j] == who && map[i + 1][j] == who && map[i + 2][j] == who && map[i + 3][j] == who && map[i + 4][j] == who)
			{
				qizi();
				cout << "��������" << endl;
				return true;
			}
		}
	}
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			for (n = i, m = j; n < 11 && m < 11; n++, m++)
			{
				if (map[n][m] == who && map[n + 1][m + 1] == who && map[n + 2][m + 2]==who && map[n + 3][m + 3] == who && map[n + 4][m + 4] == who)
				{
					qizi();
					cout << "��б����" << endl;
					return true;
				}
			}
		}
	}
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			for (n = i, m = j; n >= 4 && m < 11; n--, m++)
			{
				if (map[n][m] == who && map[n - 1][m+1] == who && map[n - 2][m + 2] == who && map[n - 3][m + 3] == who && map[n - 4][m + 4] == who)
				{
					qizi();
					cout << "��б����" << endl;
					return true;
				}
			}
		}
	}
	
	return false;
}
void tupian()
{
	IMAGE mag;
	loadimage(&mag, "ͼƬ.jpg");
	putimage(0, 0, &mag);
}
void Chongkai()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			map[i][j] = 0;
		}
	}
}
int main()
{
	initgraph(600, 500,EX_SHOWCONSOLE);
	//LoadResource();
	setbkcolor(GREEN);
	cleardevice();
	//tupian();
	mciSendString("open ����ķ羰.mp3", 0, 0, 0);
	mciSendString("play ����ķ羰.mp3", 0, 0, 0);
	Draw();
	while (true)
	{
		BeginBatchDraw();
		Draw();
		qizi();
		//tupian();
		EndBatchDraw();
		ExMessage msg;
		if (peekmessage(&msg, EX_MOUSE))
		{
			switch (msg.message)
			{
			//case WM_MOUSEMOVE:
			//	mouseMoveMsg(&msg);
			//	break;
			case WM_LBUTTONDOWN:
				mousePressMsg(&msg);
				break;


			default:
				break;
			}
		}
	}


	//getchar();
	closegraph();

	return 0;
}