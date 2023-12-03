#pragma once
#include <vector>
#include <graphics.h>
#include <iostream>

static size_t scs = 32;

enum Chess {
	none = 0,
	black = 1,
	white = 2
};

class ScoreBoard {
private:
	int whiteScore;
	int blackScore;
public:
	ScoreBoard() {

	}

	void addWhiteScore() {
		whiteScore++;
	}

	void addBlackScore() {
		blackScore++;
	}

	void displayScore() {
		std::cout << "current white score: " << whiteScore << std::endl;
		std::cout << "current black score: " << blackScore << std::endl;
	}
};

class ChessBoard {
private:
	size_t boardSize;
	std::vector<std::vector<int>> chessBoard;
public:
	ChessBoard(size_t boardSize) : boardSize{ boardSize }, chessBoard(boardSize, std::vector<int>(boardSize)) {

	}

	void initailizeBoard() {
		initgraph(800 + scs, 800 + scs, EX_SHOWCONSOLE);
		setbkcolor(YELLOW);
		cleardevice();
		HWND hand = GetHWnd();
		SetWindowText(hand, L"ChessGame");
		setlinecolor(BLACK);
		for (int i = 0; i < 25; i++)
		{
			line(scs, scs * (i + 1), scs * 25, scs * (i + 1));
			line(scs * (i + 1), scs, scs * (i + 1), scs * 25);
		}
	}

	void restChessBoard() {
		for (auto& i : chessBoard) {
			for (int& j : i) {
				j = 0;
			}
		}
		initailizeBoard();
	}

	void putChess(Chess chess) {
		if (chess == black) {
			setfillcolor(BLACK);
		}
		else {
			setfillcolor(LIGHTGRAY);
		}
		while (true)
		{
			ExMessage mouse = getmessage(EX_MOUSE);
			if (mouse.message == WM_LBUTTONDOWN)
			{
				int x = mouse.x;
				int y = mouse.y;

				if (x / scs > 0
					&& x / scs < 32
					&& y / scs > 0
					&& y / scs < 32) {
					int currentColor = chessBoard.at(mouse.x / scs - 1).at(mouse.y / scs - 1);
					if (currentColor == none)
					{
						chessBoard.at(mouse.x / scs - 1).at(mouse.y / scs - 1) = chess;
						//std::cout << "BLACK: " << mouse.x / u - 1 << " " << mouse.y / u - 1 << " " << gobang[mouse.x / u - 1][mouse.y / u - 1] << std::endl;
						solidcircle((x / scs) * scs + 16, (y / scs) * scs + 16, 16);
						return;
					}
				}


			}
		}
	}

	bool checkForWining(Chess chess) {
		int count, i, j;

		for (i = 0; i < boardSize; i++) {
			for (j = 0; j < boardSize; j++) {
				if (chessBoard[i][j] == chess) {

					// 检查行
					if (j <= boardSize - 5)
					{
						count = 1;
						for (int k = 1; k < 5; k++)
						{
							if (chessBoard[i][j + k] == chess)
							{
								count++;
							}
							else break;
						}
						if (count == 5) return true;
					}

					// 检查列
					if (i <= boardSize - 5)
					{
						count = 1;
						for (int k = 1; k < 5; k++)
						{
							if (chessBoard[i + k][j] == chess)
							{
								count++;
							}
							else break;
						}
						if (count == 5) return true;
					}

					// 检查正斜线
					if (i <= boardSize - 5 && j <= boardSize - 5)
					{
						count = 1;
						for (int k = 1; k < 5; k++)
						{
							if (chessBoard[i + k][j + k] == chess)
							{
								count++;
							}
							else break;
						}
						if (count == 5) return true;
					}

					// 检查反斜线
					if (i >= 4 && j <= boardSize - 5)
					{
						count = 1;
						for (int k = 1; k < 5; k++)
						{
							if (chessBoard[i - k][j + k] == chess)
							{
								count++;
							}
							else break;
						}
						if (count == 5) return true;
					}
				}
			}
		}
		// 如果没有五子连珠，则返回0
		return 0;
	}

	bool checkForFullChessBoard() {
		int r = 0;
		for (auto& a : chessBoard) {
			for (int& i : a) {
				if (i != none) {
					r++;
				}
			}
		}
		return r == std::pow(boardSize, 2);
	}
};

class GameHandler {
private:
	ChessBoard cb;
	ScoreBoard scb;
public:
	GameHandler(size_t initSize) : cb{ ChessBoard(initSize) }, scb{ ScoreBoard() } {
		cb.initailizeBoard();
	}

	Chess runGame() {
		int temporary = 0;
		bool fullChessBoard = false;
		do {
			cb.putChess(black);
			bool blackWin = cb.checkForWining(black);
			fullChessBoard = cb.checkForFullChessBoard();
			if (blackWin) {
				scb.addBlackScore();
				return black;
			}
			cb.putChess(white);
			bool whiteWin = cb.checkForWining(white);
			fullChessBoard = cb.checkForFullChessBoard();
			if (whiteWin) {
				scb.addWhiteScore();
				return white;
			}
			if (fullChessBoard) {
				return none;
			}
		} while (true);
	}

	void judugeForWinner() {
		bool stop = false;
		do {
			Chess winner = runGame();
			HWND hand = GetHWnd();
			int i = 0;
			switch (winner) {
			case black:
				i = MessageBox(hand, L"Black win!Do you wanna play it agin?", L"message", MB_YESNO);
				break;
			case white:
				i = MessageBox(hand, L"White win!Do you wanna play it agin?", L"message", MB_YESNO);
				break;
			case none:
				i = MessageBox(hand, L"stalemate!White win!Do you wanna play it agin?", L"message", MB_YESNO);
				break;
			}
			if (IDYES == i)
			{
				stop = true;
				std::cout << "Play again!" << std::endl;
				scb.displayScore();
				cb.restChessBoard();
			}
			else if (IDNO == i)
			{
				std::cout << "Exit!" << std::endl;
				HWND hand1 = GetHWnd();
				int i = MessageBox(hand1, L"Exiting~", L"message", MB_OK);
			}
		} while (stop);
		closegraph();
	}
};
