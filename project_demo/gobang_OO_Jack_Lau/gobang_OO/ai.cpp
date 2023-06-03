#include "ai.h"
#include <iostream>
//easyX
#include <graphics.h>
//Log
#include <fstream>
#include <iomanip>
#include <vector>

size_t Ai::countLog = 0;

Ai::Ai()
{
	
}

void Ai::reset()
{
    for (auto& i : chessLog)
    {
        for (int& j : i)
        {
            j = 0;
        }
    }
    countLog = 0;
}

void Ai::Init(chessBoard* chessboard)
{
    chessLog = std::vector <std::vector<int>>(chessboard->getBoardSize(), 
        std::vector<int>(chessboard->getBoardSize(),0));
    this->chessboard = chessboard;
}

void Ai::WriteArrayToLog(int** arr, int size)
{
    static int log = 1;
    std::ofstream logfile("log.txt", std::ios::app);
    if (logfile.is_open())
    {
        // 写入表头
        logfile << "   ";
        for (int j = 0; j < size; j++)
        {
            logfile << std::setw(4) << j << " ";
        }
        logfile << "------------" << log;
        log++;
        logfile << std::endl;

        // 写入分隔线
        logfile << "   ";
        for (int j = 0; j < size; j++)
        {
            logfile << "----";
        }

        logfile << std::endl;

        // 写入数据行
        for (int i = 0; i < size; i++)
        {
            logfile << std::setw(2) << i << "|";
            for (int j = 0; j < size; j++)
            {
                logfile << std::setw(4) << arr[i][j] << " ";
            }
            logfile << std::endl;
        }

        logfile.close();
    }
}

void Ai::countLogFun(int x, int y)
{
    int unit = chessboard->getUnit();
    countLog++;
    //cleardevice();
    settextstyle(30, 0, "黑体");
    settextcolor(RED);
    setbkmode(TRANSPARENT);
    chessLog[x][y] = countLog;
    static char s[5];
    sprintf(s, "%d", countLog);
    outtextxy(x * unit + unit + 8, y * unit + unit + 8, s);
}

void Ai::computerSet(int color)
{
    size_t unit = chessboard->getUnit();
    static int log = 1;

    int max = 0, row = 7, col = 7;
    int** score = scoreValueSet(color);
    if (color == White)
        WriteArrayToLog(score, 15);

    max = score[0][0];
    for (int i = 0; i < chessboard->getBoardSize(); i++)
        for (int j = 0; j < chessboard->getBoardSize(); j++)
        {
            if (max < score[i][j])
            {
                max = score[i][j];
                row = i;
                col = j;
            }
        }

    if (color == Black)
        setfillcolor(BLACK);
    if (color == White)
        setfillcolor(WHITE);

    if (chessboard->getChess(row,col) == 0)
    {

        chessboard->setChess(row,col,color);
        if (color == Black)
            std::cout << "BLACK ";
        if (color == White)
            std::cout << "White ";


        std::cout << log++ << ": " << row << " " << col << " " << chessboard->getChess(row, col) << std::endl;
        solidcircle(row * unit + unit + 16, col * unit + unit + 16, 16);
        //countLogFun((row), (col));
        return;
    }
}

int** Ai::scoreValueSet(int color)
{
    int** score = new int* [15];
    for (int i = 0; i < 15; i++)
        score[i] = new int[15];

    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            score[i][j] = 0;



    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            if (chessboard->getChess(i,j) == 0)
                score[i][j] = scoreCal(i, j, color);


    //WriteArrayToLog(score, 15);
    return score;
}

void Ai::logCal(int* log, int& count)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (i != j && log[i] == 3 && log[j] == 3)
            {
                count += 512;
                break;
            }
            else if (i != j && log[i] == 1 && log[j] == 3)
                count += 10;
        }
    }

    for (int i = 0, j = i + 4; i < 5; i++, j++)
    {
        if (log[i] && log[j])
        {
            if (log[i] == 1 && log[j] == 1)
            {
                count += 3;
            }
            if (log[i] == 3 && log[j] == 1 || log[i] == 1 && log[j] == 3)
            {
                count += 128;
            }
            if (log[i] == 3 && log[j] == 3)
            {
                count += 256;
            }
            if (log[i] == 63 && log[j] == 3 || log[i] == 63 && log[j] == 1 ||
                log[i] == 3 && log[j] == 63 || log[i] == 1 && log[j] == 3 ||
                log[i] == 63 && log[j] == 63)
            {
                count += 512;
            }
        }
    }
    for (int i = 0; i < 8; i++)
    {
        if (log[i] == 3)
        {
            if (i == 0)
            {
                if (log[i + 1] == 1 && log[i + 1 + 4] == 1 || log[7] == 1 && log[3] == 1)
                {
                    count += 512;
                }
            }
            else if (i == 7)
            {
                if (log[0] == 1 && log[4] == 1 || log[6] == 1 && log[2] == 1)
                {
                    count += 512;
                }
            }
            else if (i <= 4)
            {
                if (i + 1 < 4)
                {
                    if (log[i + 1] == 1 && log[i + 1 + 4] == 1 || log[i - 1] == 1 && log[i - 1 + 4] == 1)
                    {
                        count += 512;
                    }
                }
                else if (i + 1 == 4 || i + 1 == 5)
                {
                    if (log[i + 1] >= 1 && log[i + 1 - 4] == 1 || log[i - 1] == 1 && log[i - 1 + 4] == 1)
                    {
                        count += 512;
                    }
                }
                else
                {
                    if (log[i + 1] == 1 && log[i + 1 - 4] == 1 || log[i - 1] == 1 && log[i - 1 - 4] == 1)
                    {
                        count += 512;
                    }
                }
            }

        }
    }
}

int Ai::scoreCal(int x, int y, int color)
{
    int count = 0;
    int log[8] = { 0 };
    log[0] = scoreCalDirection(x, y, -1, -1, color);
    log[1] = scoreCalDirection(x, y, -1, 0, color);
    log[2] = scoreCalDirection(x, y, -1, 1, color);
    log[3] = scoreCalDirection(x, y, 0, 1, color);
    log[4] = scoreCalDirection(x, y, 1, 1, color);
    log[5] = scoreCalDirection(x, y, 1, 0, color);
    log[6] = scoreCalDirection(x, y, 1, -1, color);
    log[7] = scoreCalDirection(x, y, 0, -1, color);


    logCal(log, count);


    for (int i = 0; i < 8; i++)
        count += log[i];

    return count;
}

int Ai::scoreCalDirection(int x, int y, int tempX, int tempY, int color)
{
    int anotherColor;
    if (color == Black)
        anotherColor = White;
    else
        anotherColor = Black;

    int count = 0;
    int a = tempX, b = tempY;
    if (x + tempX + 1 && y + tempY + 1)
    {
        //computer's color
        if (chessboard->checkSubscript(x + tempX, y + tempY))
        {
            if (chessboard->getChess(x + tempX, y + tempY) == color)
            {
                count += 2;
                tempCal(tempX);
                tempCal(tempY);
                if (chessboard->checkSubscript(x + tempX, y + tempY))
                {
                    if (chessboard->getChess(x + tempX, y + tempY) == color)
                    {
                        count += 2;
                        tempCal(tempX);
                        tempCal(tempY);
                        int symbolX = 1, symbolY = 1;
                        if (tempX < 0) symbolX = -1;
                        if (tempY < 0) symbolY = -1;
                        if (chessboard->checkSubscript(x + tempX, y + tempY))
                        {
                            if (chessboard->getChess(x - symbolX, y - symbolY) == anotherColor ||
                                chessboard->getChess(x + tempX + symbolX, y + tempY + symbolY) == anotherColor)
                                count -= 4;
                            else if (chessboard->getChess(x + tempX + symbolX, y + tempY + symbolY) == 0 &&
                                chessboard->getChess(x + tempX + symbolX, y + tempY + symbolY) == 0)
                                count += 4;
                            if (chessboard->getChess(x + tempX, y + tempY) == color)
                            {

                                count += 20;
                                tempCal(tempX);
                                tempCal(tempY);
                                if (chessboard->getChess(x + tempX, y + tempY) == color)
                                {
                                    if (chessboard->getChess(x - symbolX, y - symbolY) == anotherColor)
                                        count -= 20;
                                    else if (chessboard->getChess(x - symbolX, y - symbolY) == 0 &&
                                        chessboard->getChess(x + tempX + symbolX, y + tempY + symbolY) == 0)
                                        count += 1024;
                                    if (chessboard->getChess(x + tempX, y + tempY) == color)
                                    {
                                        count += 4096;
                                    }
                                } 
                            }
                        }
                    }
                }
            }
        }
        
        //player's color
        tempX = a;
        tempY = b;
        if (chessboard->checkSubscript(x + tempX, y + tempY))
        {
            if (chessboard->getChess(x + tempX, y + tempY) == anotherColor)
            {
                count += 1;
                tempCal(tempX);
                tempCal(tempY);
                if (chessboard->checkSubscript(x + tempX, y + tempY))
                {
                    if (chessboard->getChess(x + tempX, y + tempY) == anotherColor)
                    {
                        count += 2;
                        tempCal(tempX);
                        tempCal(tempY);
                        int symbolX = 1, symbolY = 1;
                        if (tempX < 0) symbolX = -1;
                        if (tempY < 0) symbolY = -1;
                        if (chessboard->checkSubscript(x + tempX, y + tempY))
                        {
                            if (chessboard->getChess(x - symbolX, y - symbolY) == color ||
                                chessboard->getChess(x + tempX + symbolX, y + tempY + symbolY) == color)
                                count -= 3;
                            if (chessboard->getChess(x + tempX, y + tempY) == anotherColor)
                            {
                                count += 60;
                                tempCal(tempX);
                                tempCal(tempY);
                                if (chessboard->checkSubscript(x + tempX, y + tempY))
                                {
                                    if (chessboard->getChess(x + tempX, y + tempY) == anotherColor)
                                    {
                                        count += 128;
                                    }
                                }
                                
                            }
                        }
                        
                    }
                }
                
            }
        }
        
    }

    return count;
}

void Ai::tempCal(int& temp)
{
    if (temp > 0) temp++;
    else if (temp < 0) temp--;
}

void Ai::Exe()
{
    computerSet(Black);
}