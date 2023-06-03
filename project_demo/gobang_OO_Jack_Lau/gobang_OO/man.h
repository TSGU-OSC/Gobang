#pragma once
#include "chessboard.h"

class Man
{
private:
	chessBoard* chessboard;
public:
	Man();
	void Init(chessBoard* chessboard);
	void setChess(int color);
	void Exe();
};