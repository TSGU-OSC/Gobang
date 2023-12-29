#include<easyx.h>//�谲װeasyX��vs���汾:-V0.1
#include<iostream>
using namespace std;
bool search(char str[], char substr[]) {//�����Ӵ�
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

#define width 800 //���̿�
#define height 800 //���̸�
#define qpx 50 //����X��
#define qpy 50 //����Y��

COORD tp;//�����������

char qz[15][15];//w��b��0��

bool hb;//����ڼ�

void init();//��ʼ��
void draw();//����
void update();//����

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
	setbkcolor(RGB(238, 238, 238));//������ɫ
	cleardevice();//ˢ�´�����ʾ��ɫ
	tp.X = -1;
	tp.Y = -1;
	hb = true;
	memset(qz, '0', sizeof(char) * 15 * 15);//���ӳ�ʼ��
	MessageBox(NULL, TEXT("������Ϊ���ӣ��Ҽ�Ϊ���ӣ��������¡����ȷ����ʼ��Ϸ -V:0.1"), NULL, MB_OK);
}

void draw() {
	cleardevice();//ˢ�´���
	BeginBatchDraw();//˫����
	setlinecolor(0);//������ɫ
	//����
	for (int i = 0; i < 15; i++) {
		line(qpx, qpy + 50 * i, qpx + 14 * 50, qpy + 50 * i);
		line(qpx + 50 * i, qpy, qpy + 50 * i, qpy + 14 * 50);
	}
	setfillcolor(RED);
	if (tp.X != -1 && tp.Y != -1) {//Ԥ����
		if (hb == true)setfillcolor(WHITE);
		else setfillcolor(BLACK);
		fillcircle(qpx + tp.X * 50, qpy + tp.Y * 50, 20);
	}
		
	for (int i = 0; i < 15; i++) {//����
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
	//���ָ����
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
				char h[16] = { 0 };//��
				for (int i = 0; i < 15; i++)h[i] = qz[y][i];
				char z[16] = { 0 };//��
				for (int i = 0; i < 15; i++)z[i] = qz[i][x];
				int bx = x;//��б��ʼ��
				int by = y;
				while (0 <= bx + 1 && bx + 1 <= 14 && 0 <= by - 1 && by - 1 <= 14) {
					bx++;
					by--;
				}
				char zx[16] = { 0 };//��б
				for (int i = 0; 0 <= bx && bx <= 14 && 0 <= by && by <= 14; i++)
					zx[i] = qz[by++][bx--];
				bx = x;//��б��ʼ��
				by = y;
				while (0 <= bx - 1 && bx - 1 <= 14 && 0 <= by - 1 && by - 1 <= 14) {
					bx--;
					by--;
				}
				char yx[16] = { 0 };//��б
				for (int i = 0; 0 <= bx && bx <= 14 && 0 <= by && by <= 14; i++)
					yx[i] = qz[by++][bx++];
				if (search(h, w) == true || search(z, w) == true || search(zx, w) == true || search(yx, w) == true) {
					draw();
					MessageBox(NULL, TEXT("��������ţ����Ӯ�˺���"),NULL, MB_OK);
					init();
				}
			}
			//cout << "���";
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
			char h[16] = { 0 };//��
			for (int i = 0; i < 15; i++)h[i] = qz[y][i];
			char z[16] = { 0 };//��
			for (int i = 0; i < 15; i++)z[i] = qz[i][x];
			int bx = x;//��б��ʼ��
			int by = y;
			while (0 <= bx + 1 && bx + 1 <= 14 && 0 <= by - 1 && by - 1 <= 14) {
				bx++;
				by--;
			}
			char zx[16] = { 0 };//��б
			for (int i = 0; 0 <= bx && bx <= 14 && 0 <= by && by <= 14; i++)
				zx[i] = qz[by++][bx--];
			bx = x;//��б��ʼ��
			by = y;
			while (0 <= bx - 1 && bx - 1 <= 14 && 0 <= by - 1 && by - 1 <= 14) {
				bx--;
				by--;
			}
			char yx[16] = { 0 };//��б
			for (int i = 0; 0 <= bx && bx <= 14 && 0 <= by && by <= 14; i++)
				yx[i] = qz[by++][bx++];
			if (search(h, b) == true || search(z, b) == true || search(zx, b) == true || search(yx, b) == true) {
				draw();
				MessageBox(NULL, TEXT("���ֲ����Ǻ��֣������������"), NULL, MB_OK);
				init();
			}
			//cout << "�Ҽ�";
		}
	}
}
