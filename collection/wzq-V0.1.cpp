#include<easyx.h>//需安装easyX与vs。版本:-V0.1
#include<iostream>
using namespace std;
bool search(char str[], char substr[]) {//查找子串
	int strLen = strlen(str);
	int substrLen = strlen(substr);
	int i, j;
	for (i = 0; i <= strLen - substrLen; i++) {
		for (j = 0; j < substrLen; j++) {
			if (str[i + j] != substr[j]) {
				break;
			}
		}
		if (j == substrLen) {
			return true;
		}
	}
	return false;
}

#define width 800 //棋盘宽
#define height 800 //棋盘高
#define qpx 50 //棋盘X轴
#define qpy 50 //棋盘Y轴

COORD tp;//玩家下棋坐标

char qz[15][15];//w白b黑0无

bool hb;//白真黑假

void init();//初始化
void draw();//绘制
void update();//更新

int main() {
	initgraph(width, height);
	init();

	while (1) {
		 draw();
		 update();
	}
	return 0;
}

void init() {
	setbkcolor(RGB(238, 238, 238));//背景颜色
	cleardevice();//刷新窗口显示颜色
	tp.X = -1;
	tp.Y = -1;
	hb = true;
	memset(qz, '0', sizeof(char) * 15 * 15);//旗子初始化
	MessageBox(NULL, TEXT("鼠标左键为白子，右键为黑子，白子先下。点击确定开始游戏 -V:0.1"), NULL, MB_OK);
}

void draw() {
	cleardevice();//刷新窗口
	BeginBatchDraw();//双缓冲
	setlinecolor(0);//棋盘颜色
	//棋盘
	for (int i = 0; i < 15; i++) {
		line(qpx, qpy + 50 * i, qpx + 14 * 50, qpy + 50 * i);
		line(qpx + 50 * i, qpy, qpy + 50 * i, qpy + 14 * 50);
	}
	setfillcolor(RED);
	if (tp.X != -1 && tp.Y != -1) {//预落子
		if (hb == true)setfillcolor(WHITE);
		else setfillcolor(BLACK);
		fillcircle(qpx + tp.X * 50, qpy + tp.Y * 50, 20);
	}
		
	for (int i = 0; i < 15; i++) {//棋子
		for (int j = 0; j < 15; j++) {
			if (qz[i][j] == '0')continue;
			if (qz[i][j] == 'w') setfillcolor(WHITE);
			else if (qz[i][j] == 'b')setfillcolor(BLACK);
			fillcircle(qpx + j * 50, qpy + i * 50, 20);
			}
		}
	EndBatchDraw();
}

void update() {
	//鼠标指向处理
	ExMessage mouse;
	if (peekmessage(&mouse)) {
		if (mouse.message == WM_MOUSEMOVE) {
			int x = mouse.x - qpx;
			int y = mouse.y - qpy;
			if (-24 <= x && x <= 724 && -24 <= y && y <= 724) {
				tp.X = (x + 25) / 50;
				tp.Y = (y + 25) / 50;
			}
			else {
				tp.X = -1;
				tp.Y = -1;
			}
			//cout << tp.X << " " << tp.Y << endl;
		}
		else if (mouse.message == WM_LBUTTONDOWN) {
			char w[6] = { 'w','w','w','w','w'};
			int x = mouse.x - qpx;
			int y = mouse.y - qpy;
			if (-24 <= x && x <= 724 && -24 <= y && y <= 724) {
				x = (x + 25) / 50;
				y = (y + 25) / 50;
				if (qz[y][x] == '0' && hb == true) {
					qz[y][x] = 'w';
					hb = !hb;
				}
				char h[16] = { 0 };//横
				for (int i = 0; i < 15; i++)h[i] = qz[y][i];
				char z[16] = { 0 };//纵
				for (int i = 0; i < 15; i++)z[i] = qz[i][x];
				int bx = x;//左斜起始点
				int by = y;
				while (0 <= bx + 1 && bx + 1 <= 14 && 0 <= by - 1 && by - 1 <= 14) {
					bx++;
					by--;
				}
				char zx[16] = { 0 };//左斜
				for (int i = 0; 0 <= bx && bx <= 14 && 0 <= by && by <= 14; i++)
					zx[i] = qz[by++][bx--];
				bx = x;//右斜起始点
				by = y;
				while (0 <= bx - 1 && bx - 1 <= 14 && 0 <= by - 1 && by - 1 <= 14) {
					bx--;
					by--;
				}
				char yx[16] = { 0 };//右斜
				for (int i = 0; 0 <= bx && bx <= 14 && 0 <= by && by <= 14; i++)
					yx[i] = qz[by++][bx++];
				if (search(h, w) == true || search(z, w) == true || search(zx, w) == true || search(yx, w) == true) {
					draw();
					MessageBox(NULL, TEXT("白手你真牛，打赢了黑手"),NULL, MB_OK);
					init();
				}
			}
			//cout << "左键";
		}
		else if (mouse.message == WM_RBUTTONDOWN) {
			char b[6] = { 'b','b','b','b','b' };
			int x = mouse.x - qpx;
			int y = mouse.y - qpy;
			if (-24 <= x && x <= 724 && -24 <= y && y <= 724) {
				if (qz[(y + 25) / 50][(x + 25) / 50] == '0' && hb == false) {
					qz[(y + 25) / 50][(x + 25) / 50] = 'b';
					hb = !hb;
				}
			}
			x = (x + 25) / 50;
			y = (y + 25) / 50;
			char h[16] = { 0 };//横
			for (int i = 0; i < 15; i++)h[i] = qz[y][i];
			char z[16] = { 0 };//纵
			for (int i = 0; i < 15; i++)z[i] = qz[i][x];
			int bx = x;//左斜起始点
			int by = y;
			while (0 <= bx + 1 && bx + 1 <= 14 && 0 <= by - 1 && by - 1 <= 14) {
				bx++;
				by--;
			}
			char zx[16] = { 0 };//左斜
			for (int i = 0; 0 <= bx && bx <= 14 && 0 <= by && by <= 14; i++)
				zx[i] = qz[by++][bx--];
			bx = x;//右斜起始点
			by = y;
			while (0 <= bx - 1 && bx - 1 <= 14 && 0 <= by - 1 && by - 1 <= 14) {
				bx--;
				by--;
			}
			char yx[16] = { 0 };//右斜
			for (int i = 0; 0 <= bx && bx <= 14 && 0 <= by && by <= 14; i++)
				yx[i] = qz[by++][bx++];
			if (search(h, b) == true || search(z, b) == true || search(zx, b) == true || search(yx, b) == true) {
				draw();
				MessageBox(NULL, TEXT("黑手不亏是黑手，轻松拿捏白手"), NULL, MB_OK);
				init();
			}
			//cout << "右键";
		}
	}
}
