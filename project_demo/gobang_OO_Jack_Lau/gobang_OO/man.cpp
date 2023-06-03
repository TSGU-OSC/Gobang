#include "man.h"

#include <iostream>
#include <graphics.h>

Man::Man()
{}


void Man::Init(chessBoard* chessboard)
{
	this->chessboard = chessboard;
}

void Man::setChess(int color)
{
    size_t unit = chessboard->getUnit();

    if (color == Black)
        setfillcolor(BLACK);
    if (color == White)
        setfillcolor(WHITE);

    
    while (1)
    {
        ExMessage m = getmessage(EX_MOUSE);//获取鼠标消息
        if (m.message == WM_LBUTTONDOWN)//如果鼠标左键触发
        {
            if (m.x / unit > 0 && m.x / unit < 16 && m.y / unit > 0 && m.y / unit < 16 && 
                chessboard->getChess(m.x / unit - 1,m.y / unit - 1) == 0)
            {
                chessboard->setChess(m.x / unit - 1, m.y / unit - 1, color);
                //chess[m.x / unit - 1][m.y / unit - 1] = color;

                if (color == Black)
                    std::cout << "BLACK ";
                if (color == White)
                    std::cout << "White ";

                std::cout << ": " << m.x / unit - 1 << " " << m.y / unit - 1 << " " << chessboard->getChess(m.x / unit - 1, m.y / unit - 1) << std::endl;
                solidcircle((m.x / unit) * unit + 16, (m.y / unit) * unit + 16, 16);//绘制棋子
                return;
            }
        }
    }
}

void Man::Exe()
{
	setChess(White);
}