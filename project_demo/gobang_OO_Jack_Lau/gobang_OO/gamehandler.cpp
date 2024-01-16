#include "gamehandler.h"
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <cstdlib>


gameHandler::gameHandler(Man* man, Ai* ai, chessBoard* chessboard)
	:man(man),ai(ai),chessboard(chessboard)
{
	man->Init(chessboard);
	ai->Init(chessboard);
}



void gameHandler::Play()
{
	chessboard->chessBoardInit();
	while (1)
	{
		ai->Exe();
		if (chessboard->isWin(Black))
		{
			std::cout << "Black win!" << std::endl;
			messageBox(1);
			break;
		}
			
		if (chessboard->judgement())
		{
			messageBox(3);
			break;
		}
			
		
		man->Exe();
		if (chessboard->isWin(White))
		{
			std::cout << "White win!" << std::endl;
			messageBox(2);
			break;
		}
		if (chessboard->judgement())
		{
			messageBox(3);
			break;
		}

	}
	
	_getch();
	closegraph();
}

void gameHandler::messageBox(int log)
{
	HWND hand = GetHWnd();
	int i = 0;
	if (log == 1)
		i = MessageBox(hand, "Black win!Do you wanna play it agin?", "message", MB_YESNO);
	else if (log == 2)
		i = MessageBox(hand, "White win!Do you wanna play it agin?", "message", MB_YESNO);
	else if (log == 3)
		i = MessageBox(hand, "stalemate!White win!Do you wanna play it agin?", "message", MB_YESNO);
	if (IDYES == i)
	{
		std::cout << "Play again!" << std::endl;
		ai->reset();
		chessboard->reset();
		Play();
	}
	else if (IDNO == i)
	{
		std::cout << "Exit!" << std::endl;
		HWND hand1 = GetHWnd();
		int i = MessageBox(hand1, "Exiting~", "message", MB_OK);
		exit(0);
	}
}

gameHandler::~gameHandler()
{
	delete man;
	delete ai;
	delete chessboard;
}