#pragma once
#include<graphics.h>
#include<vector>
using namespace std;

#define space 50
#define grid_w 50

struct ChessPos
{
	float row;
	float col;

	ChessPos(float r = 0,float c=0):row(r),col(c){}
};

typedef enum
{
	CHESS_WHITE = -1,//����
	CHESS_BLACK = 1
}chess_kind_t;

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	void init();

	//�ж���ָ������(x,y)λ���Ƿ�����Ч���
	//�������Ч���������Ч�����λ�ã��У��У������ڲ���pos��
	bool clickBoard(int x, int y, ChessPos* pos);

	//�����̵�ָ��λ�ã�pos�������ӣ�kind��
	void chessDown(ChessPos* pos, chess_kind_t kind);

	int getGradeSize();//��ȡ���̵Ĵ�С
	
	//��ȡָ��λ���Ǻ��廹�ǰ���
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	bool checkOver();

private:
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;
	IMAGE bk;

	int gradeSize;
	int margin_x;
	int margin_y;
	float chessSize;

	//�洢��ǰ��ֵ����ӷֲ�����
	//chessMap[3][5] ��ʾ���̵ĵ����е����е�������� 0���հ� 1������  -1������
	vector<vector<int>> chessMap;

	//��ʾ���ڸ�˭����
	bool playerFlag;//true: ������  false��������

	void updateGameMap(ChessPos* pos);

	bool checkWin();//ʤ���ѷַ���true�����򷵻�false

	ChessPos lastPos;//������ӵ��λ��
};

