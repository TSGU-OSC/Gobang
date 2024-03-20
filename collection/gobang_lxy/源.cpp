#include<stdio.h>
#include<easyx.h>
# include <stdlib.h>
# include <time.h>
int a[15][15] = { 0 };
int c, d;
int sum1, sum2;
void hline(int h) 
{
	line(40, 40*h, 600, 40*h);
}
void sline(int h) {
	line(40 * h, 40, 40 * h, 600);
}
bool qz(int x, int y) 
{
	if (a[x][y] == 0)
	{
		a[x][y] = 1;
		setfillcolor(BLACK);
		fillcircle(y*40+40, x*40+40, 16);
		return true;
	}
	else { printf("’º”√"); 
	return false;
	}
	
}
void computermove() {
	
	int flag = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{

			if (j<=12&&a[i][j] == 1 && a[i][j + 1] == 1 && a[i][j + 2] == 0) {
				
				setfillcolor(WHITE);
				fillcircle((j + 2) * 40 + 40, i * 40 + 40, 16);
				a[i][j + 2] = 2;
				printf("@");
				
				
				flag = 1; break;

			}
			if (j>=2&& a[i][j] == 1 && a[i][j - 1] == 1 && a[i][j - 2] == 0) {
				setfillcolor(WHITE);
				fillcircle((j - 2) * 40 + 40, i * 40 + 40, 16);
				a[i][j - 2] = 2;
				printf("@@");
				flag = 1; break;
			}
			if (i>=2&&a[i][j] == 1 && a[i - 1][j] == 1 && a[i - 2][j] == 0)
			{
				setfillcolor(WHITE);
				fillcircle((j) * 40 + 40, (i-2) * 40 + 40, 16);
				a[i-2][j] = 2;
				printf("@@@");
				flag = 1; break;
			}
			if (i<=12&&a[i][j] == 1 && a[i + 1][j] == 1 && a[i + 2][j] == 0)
			{
				setfillcolor(WHITE);
				fillcircle((j) * 40 + 40, (i+2) * 40 + 40, 16);
				a[i+2][j] = 2;
				printf("@@@@");
				flag = 1; break;
			}
			if (40*(j+3)<=600&&(i-1)*40<=600&&40*(j+3)>=40&&(i-1)*40>=40&&i + j >= 4 && i + j <= 24 && a[i][j] == 1 && a[i - 1][j + 1] == 1 && a[i - 2][j + 2] == 0)
			{
				setfillcolor(WHITE);
				fillcircle((j + 2) * 40 + 40, (i - 2) * 40 + 40, 16);
				a[i - 2][j + 2] = 2;
				printf("@@@@@");
				flag = 1; break;
			}
			if ((j-1)*40<=600&&(i-1)*40<=600&&(j-1)*40>=40&&(i-1)*40>=40&&a[i][j] == 1 && a[i - 1][j - 1] == 1 && a[i - 2][j - 2] == 0)
			{
				setfillcolor(WHITE);
				fillcircle((j- 2)* 40 + 40, (i - 2) * 40 + 40, 16);
				a[i - 2][j - 2] = 2;
				flag = 1;
				printf("@@@@@@");
				break;
			}
			if (40*(j+3)<=600&&40*(i+3)<=600&&40*(j+3)>=40&&40*(i+3)>=40&&a[i][j] == 1 && a[i + 1][j + 1] == 1 && a[i + 2][j + 2] == 0)
			{
				setfillcolor(WHITE);
				fillcircle((j +2) * 40 + 40, (i + 2) * 40 + 40, 16);
				a[i +2][j + 2] = 2;
				printf("@@@@@@@");
				flag = 1;
				break;
			}
		}
		if (flag == 1) break;
	}
		
	
	
	if (flag == 0)
	{
		srand((unsigned int)time(NULL));
		do 
		{
			c = rand() % 15;
			d = rand() % 15;
			if (a[d][c] == 0)
			{

				setfillcolor(WHITE);
				fillcircle(c * 40 + 40, d * 40 + 40, 16);
				a[d][c] = 2;
				printf("\n%d %d", d, c); break;
			}
		} while (1);
	}
			
	


}
void jd(int x, int y) 
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			int gridx = j * 40 + 40;
			int gridy = i * 40 + 40;
			if (abs(x - gridx) <= 19 && abs(y - gridy) <= 19)
			{
				sum1 = i;
				sum2 = j;
				
				

			}
		}
	}
}
int iswin()
{
	int flag2 = 0;
	for (int i = 0; i <= 14; i++)
	{
		for (int j = 0; j <= 14; j++)
		{
			if (a[i][j] != 0 && a[i][j] == a[i][j + 1] && a[i][j + 1] == a[i][j + 2] && a[i][j + 2] == a[i][j + 3] && a[i][j + 3] == a[i][j + 4])
			{
				return a[i][j]; flag2 = 1; break;
			}
			if (flag2 == 1)break;
			if (a[i][j] != 0 && a[i][j] == a[i + 1][j] && a[i + 1][j] == a[i + 2][j] && a[i + 2][j] == a[i + 3][j] && a[i + 3][j] == a[i + 4][j])
			{
				return a[i][j]; flag2 = 1; break;
			}if(a[i][j]!=0&&a[i-1][j+1]==a[i][j]&&a[i-1][j+1]==a[i-2][j+2]&&a[i-2][j+2]==a[i-3][j+3]&&a[i-3][j+3]==a[i-4][j+4])
			{
				return a[i][j]; flag2 = 1; break;
			}
			if(a[i][j]!=0&&a[i][j]==a[i+1][j+1]&&a[i+1][j+1]==a[i+2][j+2]&&a[i+2][j+2]==a[i+3][j+3]&&a[i+3][j+3]==a[i+4][j+4])
			{
				return a[i][j]; flag2 = 1; break;
			}
			if (flag2 == 1) break;
		}
	}

}



int main()
{
	
	
	initgraph(640, 640,EX_SHOWCONSOLE);
	setbkcolor(CYAN);
	cleardevice();
	
	setlinecolor(BLACK);
	for (int i = 1; i <= 15; i++)
	{
		hline(i);
		sline(i);
	}
	ExMessage msg;
	do {
		int e = 0;
		while (1)
		{
			if (peekmessage(&msg))
			{


				switch (msg.message)
				{
				                        case WM_LBUTTONDOWN: 
										{
					                      jd(msg.x, msg.y); printf("e=%d\n", e);
					                                          if (qz(sum1, sum2))
					                                             {
					                                            	e = 1;
						                                           printf("sum1=%d,sum2=%d", sum1, sum2);
					                                            }
				                                                             	break;
				                        }
					

				}
				if (e == 1)break;



			}
		}
			
				
			
		int m = iswin();
		if (m == 1) { printf("\n@@@you win@@@"); break; }
	if (m == 2) { printf("\n@@@i win@@@"); break; }
		computermove(); 
		if (m == 1) { printf("\n@@@you win@@@"); break; }
		if (m == 2) { printf("\n@@@i win@@@"); break; }
	} while (1);
	

	getchar();
	return 0;
}
