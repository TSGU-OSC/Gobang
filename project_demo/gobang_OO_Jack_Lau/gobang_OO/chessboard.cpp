#include <graphics.h>
#include <iostream>
#include "chessboard.h"

size_t chessBoard::countLog = 0;

size_t chessBoard::getUnit()
{
	return unit;
}

size_t chessBoard::getBoardSize()
{
    return boardSize;
}

bool chessBoard::checkSubscript(int row, int col)
{
    if (row >= 0 && row < boardSize && col >= 0 && col < boardSize)
        return true;
    else
        return false;
}

void chessBoard::chessBoardInit()
{
    initgraph((boardSize + 2) * unit, (boardSize + 2) * unit, EX_SHOWCONSOLE); // 初始化图形窗口
    setbkcolor(GREEN);
    cleardevice();
    HWND hand = GetHWnd();
    SetWindowText(hand, "welcome");
    setlinecolor(BLACK);
    for (int i = 0; i < boardSize+1; i++)
    {
        line(unit, unit * (i + 1), unit * (boardSize + 1), unit * (i + 1));
        line(unit * (i + 1), unit, unit * (i + 1), unit * (boardSize + 1));
    }
}

void chessBoard::setChess(int color)
{
    
    setfillcolor(WHITE);
    while (1)
    {
        ExMessage m = getmessage(EX_MOUSE);
        if (m.message == WM_LBUTTONDOWN)
        {
            if (m.x / unit > 0 && m.x / unit < 16 && m.y / unit > 0 && m.y / unit < 16 && chess[m.x / unit - 1][m.y / unit - 1] == 0)
            {
                chess[m.x / unit - 1][m.y / unit - 1] = White;
                std::cout << "WHITE  : " << m.x / unit - 1 << " " << m.y / unit - 1 << " " << chess[m.x / unit - 1][m.y / unit - 1] << std::endl;
                solidcircle((m.x / unit) * unit + 16, (m.y / unit) * unit + 16, 16);
                //countLogFun((int)(m.x / u - 1), (int)(m.y / u - 1));
                return;
            }
        }
    }
}

void chessBoard::manSetChess(int color)
{
    if (color == Black)
        setfillcolor(BLACK);
    if (color == White)
        setfillcolor(WHITE);

    while (1)
    {
        ExMessage m = getmessage(EX_MOUSE);
        if (m.message == WM_LBUTTONDOWN)
        {
            if (m.x / unit > 0 && m.x / unit < 16 && m.y / unit > 0 && m.y / unit < 16 && chess[m.x / unit - 1][m.y / unit - 1] == 0)
            {
                chess[m.x / unit - 1][m.y / unit - 1] = color;

                if (color == Black)
                    std::cout << "BLACK ";
                if (color == White)
                    std::cout << "White ";

                std::cout << ": " << m.x / unit - 1 << " " << m.y / unit - 1 << " " << chess[m.x / unit - 1][m.y / unit - 1] << std::endl;
                solidcircle((m.x / unit) * unit + 16, (m.y / unit) * unit + 16, 16);
                return;
            }
        }
    }

    
}

void chessBoard::aiSetChess(int color)
{

}

int chessBoard::getChess(const int &row,const int &col)
{
    return chess[row][col];
}

bool chessBoard::setChess(const int &row,const int &col,const int &color)
{
    if (chess[row][col] == 0)
    {
        chess[row][col] = color;
        return true;
    }
    else
        return false;
}

bool chessBoard::judgement()
{
    int b = 0, i = 0, j = 0;
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 15; j++)
        {
            if (chess[i][j] != 0)
            {
                b++;
            }
        }
    }
    if (b == 225)
    {
        printf("stalemate!\n");
        return true;
    }
    return false;
}

bool chessBoard::isWin(int color)
{
    int count, i, j;

    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            if (chess[i][j] == color) {

                // 检查行
                if (j <= 10)
                {
                    count = 1;
                    for (int k = 1; k < 5; k++)
                    {
                        if (chess[i][j + k] == color)
                        {
                            count++;
                        }
                        else break;
                    }
                    if (count == 5) return true;
                }

                // 检查列
                if (i <= 10)
                {
                    count = 1;
                    for (int k = 1; k < 5; k++)
                    {
                        if (chess[i + k][j] == color)
                        {
                            count++;
                        }
                        else break;
                    }
                    if (count == 5) return true;
                }

                // 检查正斜线
                if (i <= 10 && j <= 10)
                {
                    count = 1;
                    for (int k = 1; k < 5; k++)
                    {
                        if (chess[i + k][j + k] == color)
                        {
                            count++;
                        }
                        else break;
                    }
                    if (count == 5) return true;
                }

                // 检查反斜线
                if (i >= 4 && j <= 10)
                {
                    count = 1;
                    for (int k = 1; k < 5; k++)
                    {
                        if (chess[i - k][j + k] == color)
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
    return false;
}

void chessBoard::reset()
{
    for (auto &i:chess)
    {
        for (int &j:i)
        {
            j = 0;
        }
    }
    
    chessBoardInit();
    countLog = 0;
}