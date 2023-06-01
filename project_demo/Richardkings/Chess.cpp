#include "Chess.h"
#include<math.h>
#include<conio.h>

//�ֳ�ʤ�������������������¿�ʼ��Ϸ

void Chess::init()
{
    ////������Ϸ����
    //initgraph(897, 895 );//��ʾ����̨   EX_SHOWCONSOLE

    ////��ʾ����ͼƬ
    //loadimage(0, L"D:\\storageVS2019_data\\�˻���ս������\\background\\back.png");

    ////���غ���Ͱ������ӵ�ͼƬ
    // �����Լ������ϼ���ͼƬʱ��Ҫʹ��ͼƬ�ľ���·��
    //loadimage(&chessWhiteImg, L"D:\\storageVS2019_data\\�˻���ս������\\background\\timo.png", chessSize, chessSize, true);
    //loadimage(&chessBlackImg, L"D:\\storageVS2019_data\\�˻���ս������\\background\\chuishi.png", chessSize, chessSize, true);

        //1.1 Drawing environment,there use library functions

    initgraph(800, 680);	//create a self-defined windows.

    //background color
    //setbkcolor(BLUE);		
    //cleardevice();			

    //1.2 put the background

    //loadimage(&bk, "background\\back3.png");�����Ŀ������������ԣ�Ȼ��߼��������и��ַ�������Ҫ��unicode�ַ�����Ϊ���ֽ��ַ���
    loadimage(&bk, L"background\\back3.png");//�˴���Unicode�ַ���������µ�ʹ��,outtextxy(700, 200,L"change");Ҳ��һ��
    putimage(0, 0, &bk);


    //�˴�ûʲô���壬����������
    setcolor(BLUE);
    rectangle(695, 195, 755, 220);
    outtextxy(700, 200,L"change");


    setlinecolor(BLACK);
    //define color next using.
    //1.4 Make the chess map.
    //draw  lines
    for (int i = 0; i < 12; i++)
    {   
        //������Ҫ������һ���
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

    //��������
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
//�������
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
        //���Ͻǵ��ж�
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

        //���Ͻǵ��ж�
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

        //���½ǵ��ж�
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

        //���½ǵ��ж�
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

//��ʾ����
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
            //�ϴ����ӵ��Ǻڷ������ַ���������ʤ��
            loadimage(0, L"background\\win.png");
        }
        else
        {
            loadimage(0, L"background\\lost.png");
        }
         
        _getch();//��ͣ
        return true;
    }

    return false;
}

void Chess::updateGameMap(ChessPos* pos)
{
    lastPos = *pos;
    chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
    playerFlag = !playerFlag;//����
}


bool Chess::checkWin()
{
    int row = lastPos.row;
    int col = lastPos.col;

    //ˮƽ����
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

    //��ֱ����
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


    //  "/"  ����
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

    //   "\"  ����
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
