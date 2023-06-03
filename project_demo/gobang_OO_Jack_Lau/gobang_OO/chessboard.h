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
}Pos;//暂未实现

class chessBoard
{
private:
	const size_t unit = 32;
	size_t boardSize;
	//Pos position;
	std::vector<std::vector<int>> chess;
public:
	chessBoard(size_t boardSize) :boardSize(boardSize),chess(boardSize,std::vector<int>(boardSize))
		 {}//初始化动态数组

	size_t getUnit();
	
	size_t getBoardSize();

	bool checkSubscript(int row, int col);//检查访问动态数组的下标是否合法

	int getChess(const int &row,const int &col);//读取棋子状态的方法

	bool setChess(const int &row,const int &col,const int &color);//下棋的方法

	void chessBoardInit();//初始化棋盘

	void setChess(int color);//暂未实现

	void manSetChess(int color);//暂未实现

	void aiSetChess(int color);//暂未实现

	bool judgement();//判断是否和棋

	bool isWin(int color);//判断输赢

	void reset();//重制棋盘状态
};
