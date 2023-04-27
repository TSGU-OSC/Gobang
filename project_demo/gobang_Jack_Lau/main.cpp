#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")//处理接口

#include "gobang.h"




void BGM()
{
    //文件为.mp3为后缀才可播放，要把音乐拷贝到项目所在文件夹里
    mciSendString(L"open music.mp3", 0, 0, 0);//0，0,0为默认输出控制台
    mciSendString(L"play music.mp3 repeat", 0, 0, 0);
    if (0)
    {
        mciSendString(L"close music.mp3", 0, 0, 0);
    }
}

void Reset()
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            gobang[i][j] = 0;
        }
    }
    BoardPrint();
}

void BoardPrint()
{
    initgraph(512 + u, 512 + u, EX_SHOWCONSOLE); // 初始化图形窗口
    setbkcolor(GREEN);
    cleardevice();
    HWND hand = GetHWnd();
    SetWindowText(hand, L"welcome");
    setlinecolor(BLACK);
    for (int i = 0; i < 16; i++)
    {
        line(u, u*(i+1), u  * 16, u*(i+1));
        line(u*(i+1), u , u*(i+1), u * 16);
    }
}

void BlackSet()
{
    setfillcolor(BLACK);
    while (1)
    {
        ExMessage m = getmessage(EX_MOUSE);
        if (m.message == WM_LBUTTONDOWN)
        {
            
            if (m.x / u > 0 && m.x / u < 16 && m.y / u > 0 && m.y / u < 16&& gobang[m.x / u - 1][m.y / u - 1] == 0)
            {
                gobang[m.x / u - 1][m.y / u - 1] = Black;
                std::cout <<"BLACK: " << m.x / u - 1 << " " << m.y / u - 1 << " " << gobang[m.x / u - 1][m.y / u - 1] << std::endl;
                solidcircle((m.x / u) * u + 16, (m.y / u) * u + 16, 16);
                return;
            }
        }
    }
}

void WhiteSet()
{
    setfillcolor(WHITE);
    while (1)
    {
        ExMessage m = getmessage(EX_MOUSE);
        if (m.message == WM_LBUTTONDOWN)
        {
            if (m.x / u > 0 && m.x / u < 16 && m.y / u > 0 && m.y / u < 16&& gobang[m.x / u - 1][m.y / u - 1]==0)
            {
                gobang[m.x / u - 1][m.y / u - 1] = White;
                std::cout <<"WHITE " << m.x / u - 1 << " " << m.y / u - 1 << " " << gobang[m.x / u - 1][m.y / u - 1] << std::endl;
                solidcircle((m.x / u) * u + 16, (m.y / u) * u + 16, 16);
                return;
            }
            
        }
    }
}

int Gobang_Exe(int color)
{
    int count, i, j;

    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            if (gobang[i][j] == color) {

                // 检查行
                if (j <= 10)
                {
                    count = 1;
                    for (int k = 1; k < 5; k++)
                    {
                        if (gobang[i][j + k] == color)
                        {
                            count++;
                        }
                        else break;
                    }
                    if (count == 5) return color;
                }

                // 检查列
                if (i <= 10)
                {
                    count = 1;
                    for (int k = 1; k < 5; k++)
                    {
                        if (gobang[i + k][j] == color)
                        {
                            count++;
                        }
                        else break;
                    }
                    if (count == 5) return color;
                }

                // 检查正斜线
                if (i <= 10 && j <= 10)
                {
                    count = 1;
                    for (int k = 1; k < 5; k++)
                    {
                        if (gobang[i + k][j + k] == color)
                        {
                            count++;
                        }
                        else break;
                    }
                    if (count == 5) return color;
                }

                // 检查反斜线
                if (i >= 4 && j <= 10)
                {
                    count = 1;
                    for (int k = 1; k < 5; k++)
                    {
                        if (gobang[i - k][j + k] == color)
                        {
                            count++;
                        }
                        else break;
                    }
                    if (count == 5) return color;
                }
            }
        }
    }
    // 如果没有五子连珠，则返回0
    return 0;
}

int Judgement()
{
    int b = 0, i = 0, j = 0;
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 15; j++)
        {
            if (gobang[i][j] != 0)
            {
                b++;
            }
        }
    }
    if (b == 225)
    {
        printf("stalemate!\n");
        return 3;
    }
}

int EXE()
{
    int temporary = 0;
    do {
        BlackSet();
        temporary = Gobang_Exe(Black);
        if (temporary == 1 || temporary == 2) { break; }
        temporary = Judgement();
        if (temporary == 3) { return 3; }

        WhiteSet();
        temporary = Gobang_Exe(White);
        if (temporary == 1 || temporary == 2) { break; }
        temporary = Judgement();
        if (temporary == 3) { return 3; }
    } while (temporary != 1 && temporary != 2 && temporary != 3);

    if (temporary == 1) 
    { 
        printf("black win!\n");
        return 1;
    }
    if (temporary == 2) 
    { 
        printf("white win!\n");
        return 2;
    }
    return 0;
}

int main()
{
    BoardPrint();
    BGM();
    bool tem = false;
    do
    {
        int log=EXE();
        HWND hand = GetHWnd();
        int i=0;
        if(log==1)
            i = MessageBox(hand, L"Black win!Do you wanna play it agin?", L"message", MB_YESNO);
        else if(log==2)
            i = MessageBox(hand, L"White win!Do you wanna play it agin?", L"message", MB_YESNO);
        else if(log==3)
            i = MessageBox(hand, L"stalemate!White win!Do you wanna play it agin?", L"message", MB_YESNO);
        if (IDYES == i)
        {
            tem = true;
            std::cout << "Play again!" << std::endl;
            Reset();
        }
        else if (IDNO == i)
        {
            std::cout << "Exit!" << std::endl;
            HWND hand1 = GetHWnd();
            int i = MessageBox(hand1, L"Exiting~", L"message", MB_OK);
            return 0;
        }
    } while (tem);
    
    _getch();   
    closegraph();  
    return 0;
}