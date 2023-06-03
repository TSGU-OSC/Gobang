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
	CHESS_WHITE = -1,//白棋
	CHESS_BLACK = 1
}chess_kind_t;

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	void init();

	//判断在指定坐标(x,y)位置是否是有效点击
	//如果是有效点击，把有效点击的位置（行，列）保存在参数pos中
	bool clickBoard(int x, int y, ChessPos* pos);

	//在棋盘的指定位置（pos），落子（kind）
	void chessDown(ChessPos* pos, chess_kind_t kind);

	int getGradeSize();//获取棋盘的大小
	
	//获取指定位置是黑棋还是白棋
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

	//存储当前棋局的棋子分布数据
	//chessMap[3][5] 表示棋盘的第三行第五列的落子情况 0：空白 1：黑子  -1：白子
	vector<vector<int>> chessMap;

	//表示现在该谁下棋
	bool playerFlag;//true: 黑子走  false：白字走

	void updateGameMap(ChessPos* pos);

	bool checkWin();//胜负已分返回true，否则返回false

	ChessPos lastPos;//最近落子点的位置
};

