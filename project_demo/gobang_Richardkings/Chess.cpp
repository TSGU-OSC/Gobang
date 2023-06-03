#include "Chess.h"
#include<math.h>
#include<conio.h>

//分出胜负后点击任意键后可以重新开始游戏

void Chess::init()
{
    ////创建游戏窗口
    //initgraph(897, 895 );//显示控制台   EX_SHOWCONSOLE

    ////显示棋盘图片
    //loadimage(0, L"D:\\storageVS2019_data\\人机对战五子棋\\background\\back.png");

    ////加载黑棋和白棋棋子的图片
    // 我在自己电脑上加载图片时需要使用图片的绝对路径
    //loadimage(&chessWhiteImg, L"D:\\storageVS2019_data\\人机对战五子棋\\background\\timo.png", chessSize, chessSize, true);
    //loadimage(&chessBlackImg, L"D:\\storageVS2019_data\\人机对战五子棋\\background\\chuishi.png", chessSize, chessSize, true);

        //1.1 Drawing environment,there use library functions

    initgraph(800, 680);	//create a self-defined windows.

    //background color
    //setbkcolor(BLUE);		
    //cleardevice();			

    //1.2 put the background

    //loadimage(&bk, "background\\back3.png");点击项目，最下面的属性，然后高级，下面有个字符集，需要将unicode字符集改为多字节字符集
    loadimage(&bk, L"background\\back3.png");//此处是Unicode字符集的情况下的使用,outtextxy(700, 200,L"change");也是一样
    putimage(0, 0, &bk);


    //此处没什么意义，仅用来测试
    setcolor(BLUE);
    rectangle(695, 195, 755, 220);
    outtextxy(700, 200,L"change");


    setlinecolor(BLACK);
    //define color next using.
    //1.4 Make the chess map.
    //draw  lines
    for (int i = 0; i < 12; i++)
    {   
        //棋盘需要向右走一点点
        line(space, i * grid_w + space, 12 * grid_w + space, i * grid_w + space);
        line(i * grid_w + space, space, i * grid_w + space, 12 * grid_w + space);
    }
    //frame
    setlinestyle(PS_SOLID, 2);
    rectangle(space, space, grid_w * 12 + space, grid_w * 12 + space);

    //five dot
    setfillcolor(BLACK);
    solidcircle(space + 6 * grid_w, space + 6 * grid_w, 5);//center
    solidcircle(space + (7 - 5) * grid_w, space + (7 - 5) * grid_w, 5);//left up
    solidcircle(space + (7 - 5) * grid_w, space + (7 + 3) * grid_w, 5);//left down
    solidcircle(space + (7 + 3) * grid_w, space + (7 - 5) * grid_w, 5);//right up
    solidcircle(space + (7 + 3) * grid_w, space + (7 + 3) * grid_w, 5);//right down

    //棋盘清零
    for (int i = 0; i < gradeSize; i++)
    {
        for (int j = 0; j < gradeSize; j++)
        {
            chessMap[i][j] = 0;
        }
    }

    playerFlag = true;
}



Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize)
{
    this->gradeSize = gradeSize;
    this->margin_x = marginX;
    this->margin_y = marginY;
    this->chessSize = chessSize;
    playerFlag = CHESS_BLACK;

    for (int i = 0; i < gradeSize; i++)
    {
        vector<int> row;
        for (int j = 0; j < gradeSize; j++)
        {
            row.push_back(0);
        }
        chessMap.push_back(row);
    } 

}
//点击下棋
bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
    /*int col = (x - margin_x) / chessSize;
    int row = (y - margin_y) / chessSize;
    int leftTopPosX = margin_x + chessSize * col;
    int leftTopPosY = margin_y + chessSize * row;
    int offset = chessSize * 0.5;*/
    int col = (x - margin_x) / grid_w;
    int row = (y - margin_y) / grid_w;
    int leftTopPosX = margin_x + grid_w * col;
    int leftTopPosY = margin_y + grid_w * row;
    int offset = grid_w * 0.5;

    int len;
    bool ret = false;

    do
    {
        //左上角的判断
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));

        if (len < offset)
        {
            pos->row = row;
            pos->col = col;
            if (chessMap[pos->row][pos->col] == 0)
            {
                ret = true;
            }
            break;
        }

        //右上角的判断
        int x2 = leftTopPosX + chessSize;
        int y2 = leftTopPosY;
        len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
        if (len < offset)
        {
            pos->row = row;
            pos->col = col + 1;
            if (chessMap[pos->row][pos->col] == 0)
            {
                ret = true;
            }
            break;
        }

        //左下角的判断
        x2 = leftTopPosX;
        y2 = leftTopPosY + chessSize;
        len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
        if (len < offset)
        {
            pos->row = row + 1;
            pos->col = col;
            if (chessMap[pos->row][pos->col] == 0)
            {
                ret = true;
            }
            break;
        }

        //右下角的判断
        x2 = leftTopPosX + chessSize;
        y2 = leftTopPosY + chessSize;
        len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
        if (len < offset)
        {
            pos->row = row + 1;
            pos->col = col + 1;
            if (chessMap[pos->row][pos->col] == 0)
            {
                ret = true;
            }
            break;
        }

        

    } while (0);

    return ret;

   
}

//显示棋子
void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
    float x = margin_x + chessSize * pos->col -0.05 * chessSize;
    float y = margin_y + chessSize * pos->row - 0.05* chessSize;

    if (kind == CHESS_WHITE)
    {
        //putimage(x, y, &chessWhiteImg);
        setfillcolor(WHITE);
        solidcircle(x, y, 23);
    }
    else
    {
        //putimage(x, y, &chessBlackImg);
        setfillcolor(BLACK);
        solidcircle(x, y, 23);
    }

    updateGameMap(pos);
}

int Chess::getGradeSize()
{
    return gradeSize;
}

int Chess::getChessData(ChessPos* pos)
{
    return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{
    return chessMap[row][col];
}

bool Chess::checkOver()
{
    if (checkWin())
    {
        Sleep(1500);
        if (playerFlag == false)
        {
            //上次落子的是黑方（棋手方），棋手胜利
            loadimage(0, L"background\\win.png");
        }
        else
        {
            loadimage(0, L"background\\lost.png");
        }
         
        _getch();//暂停
        return true;
    }

    return false;
}

void Chess::updateGameMap(ChessPos* pos)
{
    lastPos = *pos;
    chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
    playerFlag = !playerFlag;//交换
}


bool Chess::checkWin()
{
    int row = lastPos.row;
    int col = lastPos.col;

    //水平方向
    for (int i = 0; i < 5; i++)
    {
        if (
            col - i >= 0 &&
            col - i + 4 < gradeSize &&
            chessMap[row][col - i] == chessMap[row][col - i + 1] &&
            chessMap[row][col - i] == chessMap[row][col - i + 2] &&
            chessMap[row][col - i] == chessMap[row][col - i + 3] &&
            chessMap[row][col - i] == chessMap[row][col - i + 4])
            return true;
    }

    //竖直方向
    for (int i = 0; i < 5; i++)
    {
        if (row - i >= 0 && 
            row - i + 4 < gradeSize &&
            chessMap[row - i][col] == chessMap[row - i + 1][col] &&
            chessMap[row - i][col] == chessMap[row - i + 2][col] &&
            chessMap[row - i][col] == chessMap[row - i + 3][col] &&
            chessMap[row - i][col] == chessMap[row - i + 4][col] )
            return true;
    }


    //  "/"  方向
    for (int i = 0; i < 5; i++)
    {
        if (row + i < gradeSize && 
            row + i - 4 >= 0 &&
            col - i >= 0 &&
            col - i + 4 < gradeSize &&
            chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
            chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
            chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
            chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4] )
            return true;

    }

    //   "\"  方向
    for (int i = 0; i < 5; i++)
    {
        if (row - i >= 0 && 
            row - i + 4 < gradeSize &&
            col - i>=0 && 
            col - i + 4 < gradeSize &&
            chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
            chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
            chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] &&
            chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4] )
            return true;
    }
    
    return false;
}
