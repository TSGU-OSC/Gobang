#pragma once
#include "chessboard.h"

class Ai
{
private:
	chessBoard* chessboard;
	std::vector<std::vector<int>> chessLog;
	static size_t countLog;
public:
	Ai();

	void Init(chessBoard* chessboard);

	void reset();

	void Exe();

	void WriteArrayToLog(int** arr, int size);

	void computerSet(int color);

	int** scoreValueSet(int color);

	int scoreCal(int x, int y, int color);

	int scoreCalDirection(int x, int y, int tempX, int tempY, int color);

	void tempCal(int& temp);

	void logCal(int* log, int& count);

	void countLogFun(int x, int y);
};