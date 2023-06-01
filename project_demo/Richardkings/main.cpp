#include<iostream>
#include"ChessGame.h"

int main(void)
{
	Man man;
	//(线，左边距，上边距，棋子大小)
	//Chess(int gradeSize, int marginX, int marginY, float chessSize);
	Chess chess(13, 50, 50,50);

	AI ai;
	ChessGame game(&man, &ai, &chess);

	game.play();

	return 0;
}