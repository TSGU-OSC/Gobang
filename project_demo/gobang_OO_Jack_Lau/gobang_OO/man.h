#pragma once
#include "chessboard.h"

class Man
{
private:
	chessBoard* chessboard;
public:
	Man();
	void Init(chessBoard* chessboard);

	void setChess(int color);//玩家下棋
	
	void Exe();//玩家下棋主函数
};