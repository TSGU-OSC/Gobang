#pragma once
#include "man.h"
#include "ai.h"

class gameHandler
{
private:
	Man *man;
	Ai *ai;
	chessBoard *chessboard;
public:
	gameHandler(Man* man, Ai* ai, chessBoard* chessboard);

	~gameHandler();

	void Play();
	
	void messageBox(int log);
};



