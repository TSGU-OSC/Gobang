#include <stdio.h>
#include<graphics.h>
#include<iostream>
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

int main() {
	while(1){
		initgraph(800, 800, SHOWCONSOLE);
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
						test(t, map);
						num += 1;
					}
					else if (num == 2) {
						setfillcolor(BLACK);
						ttt = hua(msg, map, num);
						if (ttt == 0) {
							break;
						}
						Printmap(map);
						test(t, map);
						num -= 1;
					}

					break;
				default:
					break;
				}
			}
		}
	}
	getchar();
	closegraph();

}