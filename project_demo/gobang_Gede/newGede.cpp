#include <stdio.h>
#include <graphics.h>
#include <iostream>
using namespace std;
int hua(ExMessage msg ,int arr[15][15],int n) {
	int a = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (msg.x<(j + 1) * 40 && msg.x>j * 40 && msg.y > i * 40 && msg.y < (i + 1) * 40) {
				if (arr[i][j] == 0) {
					arr[i][j] = n;
					fillcircle(20 + 20 * 2 * j, 20 + 20 * 2 * i, 20);
					return 1;
					break;
				}
				else
					return 0;
			}
		}
	}
	return 0;
}
void Printmap(int map[15][15]) {//控制窗口打印棋盘
	for (int i = 0; i < 15; i++){
		for (int j = 0; j < 15; j++)
			cout << map[i][j];
		cout << endl;
	}
		
}
void makemap(int map[15][15]) {
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			map[i][j] = 0;
}
int test(int t, int map[15][15]) {//进行检测
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			//判断白棋子
			if (j < 10 && map[i][j] == 1 && map[i][j + 1] == 1 && map[i][j + 2] == 1 && map[i][j + 3] == 1 && map[i][j + 4] == 1) {
				t = 1;
			}
			else if (i < 10 && map[i][j] == 1 && map[i + 1][j] == 1 && map[i + 2][j] == 1 && map[i + 3][j] == 1 && map[i + 4][j] == 1) {
				t = 1;
			}
			else if (j < 10 && i < 10 && map[i][j] == 1 && map[i + 1][j + 1] == 1 && map[i + 2][j + 2] == 1 && map[i + 3][j + 3] == 1 && map[i + 4][j + 4] == 1) {
				t = 1;
			}
			else if (j < 10 && i>5 && map[i][j] == 1 && map[i - 1][j + 1] == 1 && map[i - 2][j + 2] == 1 && map[i - 3][j + 3] == 1 && map[i - 4][j + 4] == 1) {
				t = 1;
			}
			//判断黑棋子
			if (j < 10 && map[i][j] == 2 && map[i][j + 1] == 2 && map[i][j + 2] == 2 && map[i][j + 3] == 2 && map[i][j + 4] == 2) {
				t = 2;
			}
			else if (i < 10 && map[i][j] == 2 && map[i + 1][j] == 2 && map[i + 2][j] == 2 && map[i + 3][j] == 2 && map[i + 4][j] == 2) {
				t = 2;
			}
			else if (j < 10 && i < 10 && map[i][j] == 2 && map[i + 1][j + 1] == 2 && map[i + 2][j + 2] == 2 && map[i + 3][j + 3] == 2 && map[i + 4][j + 4] == 2) {
				t = 2;
			}
			else if (j < 10 && i>5 && map[i][j] == 2 && map[i - 1][j + 1] == 2 && map[i - 2][j + 2] == 2 && map[i - 3][j + 3] == 2 && map[i - 4][j + 4] == 2) {
				t = 2;
			}
		}
	}
	if (t == 1) {
		cout << "白子赢" << endl;
		return 1;
	}
	else if (t == 2) {
		cout << "黑子赢" << endl;
		return 2;
	}
	else {
		return 0;
	}
}
void printtext(int n=0,int t=0) {//粉刷文字提示
	if (n==1) {
		wchar_t s[] = L"请下白子";
		outtextxy(20, 620, s);
	}
	else if (n==2) {
		wchar_t s[] = L"请下黑子";
		outtextxy(20, 620, s);
	}
	if (t==1) {
		wchar_t s[] = L"白子赢！！！";
		outtextxy(20, 620, s);
	}
	else if (t==2) {
		wchar_t s[] = L"黑子赢！！！";
		outtextxy(20, 620, s);
	}
}
void jixv() {//选择继续还是结束
	int t=0;
	ExMessage msg;
	wchar_t a[] = L"||继续||";
	outtextxy(20, 650, a);
	wchar_t b[] = L"||结束||";
	outtextxy(580, 650, b);
	while(t==0){
		if (peekmessage(&msg, EM_MOUSE)) {//有鼠标消息返回真，没有返回假
			switch (msg.message)
			{
			   case WM_LBUTTONDOWN: {
				   if (msg.x >= 10 && msg.x <= 10 + 100 && msg.y >= 640 && msg.y <= 640 + 60) {
					  t = 1;
					  break;
				   }
				   else if (msg.x >= 570 && msg.x <= 570 + 100 && msg.y >= 640 && msg.y <= 640 + 60) {
					 t = 1;
					 exit(0);
				   }
			   }
			}
		}
	}
}
int main() {
	while(1){
		initgraph(800, 700);
		setbkcolor(RGB(151, 162, 147));
		cleardevice();
		setlinestyle(PS_SOLID, 1);
		setlinecolor(BLACK);
		setfillcolor(WHITE);
		for (int i = 0; i <= 15; i++)
			for (int j = 0; j <= 15; j++)
				rectangle(j * 40, i * 40, 40, 40);
		ExMessage msg;
		int num = 1, //判断黑白
			map[15][15] = { {} };//棋盘
		int ttt;//是否重复的标志
		int t = 0;//判断输赢
		while (t == 0)
		{
			if (peekmessage(&msg, EM_MOUSE))//有鼠标消息返回真，没有返回假
			{
				switch (msg.message)
				{
				case WM_LBUTTONDOWN:
					if (num == 1) {
						setfillcolor(WHITE);
						ttt = hua(msg, map, num);
						if (ttt == 0) {
							break;
						}
						Printmap(map);
						t=test(t, map);
						num += 1;
						printtext(num);
					}
					else if (num == 2) {
						setfillcolor(BLACK);
						ttt = hua(msg, map, num);
						if (ttt == 0) {
							break;
						}
						Printmap(map);
						t=test(t, map);
						num -= 1;
						printtext(num);
					}
					break;
				default:
					break;
				}
			}
		}
		if (t == 1) {
			//进行打印输出白子赢，并且暂停进行决定是否退出
			printtext(0,t);
			jixv();
		}
		else if (t==2) {
			//进行打印输出黑子赢，并且暂停进行决定是否退出
			printtext(0,t);
			jixv();
		}
	}
	closegraph();
}