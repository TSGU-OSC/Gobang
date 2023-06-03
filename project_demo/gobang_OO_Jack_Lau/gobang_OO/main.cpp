#include "gamehandler.h"


int main()
{
	Man *man=new Man;
	Ai *ai=new Ai;
	chessBoard* chessboard=new chessBoard(15);
	
	gameHandler gamehandler(man,ai,chessboard);
	gamehandler.Play();

	return 0;
}