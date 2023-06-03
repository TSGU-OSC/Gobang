#pragma once
#include "chessboard.h"

class Ai
{
private:
	chessBoard* chessboard;
	std::vector<std::vector<int>> chessLog;//用于存储棋子序号
	static size_t countLog;//记录棋子数量
public:
	Ai();

	void Init(chessBoard* chessboard);

	void reset();

	void Exe();//电脑下棋主函数

	void WriteArrayToLog(int** arr, int size);//日志文件 用于打印分值表

	void computerSet(int color);//电脑下棋

	//以下为电脑算法
	int** scoreValueSet(int color);

	int scoreCal(int x, int y, int color);

	int scoreCalDirection(int x, int y, int tempX, int tempY, int color);

	void tempCal(int& temp);

	void logCal(int* log, int& count);

	void countLogFun(int x, int y);
};