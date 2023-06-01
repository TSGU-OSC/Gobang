#include "Man.h"

void Man::init(Chess* chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;
	ChessPos pos;

	while (1)
	{
		//��ȡ�������Ϣ
		msg = GetMouseMsg();

		//ͨ��chess�����������ж������Ƿ���Ч���Լ����ӹ���
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos))
		{
			break;
		}
	}

	printf("%.0f,%.0f\n", pos.row, pos.col);

	//���� 
	chess->chessDown(&pos, CHESS_BLACK);
}