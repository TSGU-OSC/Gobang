#pragma once
#include <vector>

enum
{
	None = 0,
	Black= 1,
	White= 2
};

typedef struct Pos
{
	size_t x;
	size_t y;
}Pos;

class chessBoard
{
private:
	const size_t unit = 32;
	static size_t countLog;
	size_t boardSize;
	//Pos position;
	std::vector<std::vector<int>> chess;
public:
	chessBoard(size_t boardSize) :boardSize(boardSize),chess(boardSize,std::vector<int>(boardSize))
		 {}

	size_t getUnit();
	
	size_t getBoardSize();

	bool checkSubscript(int row, int col);

	int getChess(const int &row,const int &col);

	bool setChess(const int &row,const int &col,const int &color);

	void chessBoardInit();

	void setChess(int color);

	void manSetChess(int color);

	void aiSetChess(int color);

	bool judgement();

	bool isWin(int color);

	void reset();
};
