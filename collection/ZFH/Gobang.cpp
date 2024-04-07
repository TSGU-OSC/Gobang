#include <stdio.h>
#include <stdlib.h>

//The player 1 is indicated as'o', the player 2 is indicater as'x'£»
int arrMap[17][17] = { 0 };

int t = 1;

int x = 0, y = 0;

int sum11 = 0, sum12 = 0, sum13 = 0, sum14 = 0;

int sum21 = 1, sum22 = 1, sum23 = 1, sum24 = 1;


void JudgeRepeat()
{
    void Play();

    if (arrMap[x][y] == 'x' || arrMap[x][y] == 'o')
        printf("data repeat, please input again!\n");
    else
    {
        t++;
        Play();
    }
}

void PrintQizi(int i1)
{
    void JudgeWin(int i2);

    int m = 0, n = 0;

    if (i1 == 0)
        arrMap[x][y] = 'o';
        
    if (i1 == 1)
        arrMap[x][y] = 'x';
        

    for (; m < 17; m++)
    {
        for (; n < 17; n++)
        {
            if (m == 0 || m == 16)
            {
                arrMap[m][n] = '-';
            }
            else if (n == 0 || n == 16)
            {
                arrMap[m][n] = '|';
            }

            if (arrMap[m][n] == 0)
                arrMap[m][n] = '+';

            printf("%c", arrMap[m][n]);
        }
        if (n == 17)
            n = 0;

        printf("\n");
    }
    JudgeWin(i1);
}

void Play()
{
    int i = t % 2;

    PrintQizi(i);
}

void JudgeWin(int i2)
{
    int p, t;
    int q, e;

    int add1 = 0, add2 = 0;

    sum11 = 0, sum12 = 0, sum13 = 0, sum14 = 0;
    sum21 = 0, sum22 = 0, sum23 = 0, sum24 = 0;

    bool flag1=false, flag2=false, flag3=false, flag4=false;
    bool flag11 = false, flag22 = false, flag33 = false, flag44 = false;

    if (i2 == 0)
    {
        for (p = 1; p < 5; p++)
        {
            if (arrMap[x + p][y + p] == 'o')
            {
                sum11 = sum11 + 1;
                flag1 = true;
            }             
            if (arrMap[x - p][y - p] == 'o')
            {
                sum11 = sum11 + 1;
                flag1 = true;
            }
            if(!flag1)
                sum11 = 0;
                

            if (arrMap[x + p][y - p] == 'o')
            {
                sum12 = sum12 + 1;
                flag2 = true;
            }               
            if (arrMap[x - p][x + p] == 'o')
            {
                sum12 = sum12 + 1;
                flag2 = true;
            }
            if (!flag2)
                sum11 = 0;
                

            if (arrMap[x][y + p] == 'o')
            {
                sum13 = sum13 + 1;
                flag3 = true;
            }      
            if (arrMap[x][y - p] == 'o')
            {
                sum13 = sum13 + 1;
                flag3 = true;
            }
            if (!flag3)
                sum13 = 0;
                

            if (arrMap[x + p][y] == 'o')
            {
                sum14 = sum14 + 1;
                flag4 = true;
            }
                
            if (arrMap[x - p][y] == 'o')
            {
                sum14 = sum14 + 1;
                flag4 = true;
            }
            if (!flag4)
                sum14 = 0;

        }
        if (sum11 == 4 || sum12 == 4 || sum13 == 4 || sum14 == 4)
        {
            printf("The player 1 Win this game!\n");
            exit(0);
        }
    }

    if (i2 == 1)
    {
        for (t = 1; t < 5; t++)
        {
            if (arrMap[x + t][y + t] == 'x')
            {
                sum21 = sum21 + 1;
                flag11 = true;
            }
            if (arrMap[x - t][y - t] == 'x')
            {
                sum21 = sum21 + 1;
                flag11 = true;
            }
            if (!flag11)
                sum21 = 0;
                

            if (arrMap[x + t][y - t] == 'x')
            {
                sum22 = sum22 + 1;
                flag22 = true;
            }

            if (arrMap[x - t][x + t] == 'x')
            {
                sum22 = sum22 + 1;
                flag22 = true;
            }
            if (!flag22)
                sum22 = 0;
                

            if (arrMap[x][y + t] == 'x')
            {
                sum23 = sum23 + 1;
                flag33 = true;
            }        
            if (arrMap[x][y - t] == 'x')
            {
                sum23 = sum23 + 1;
                flag33 = true;
            }
            if (!flag33)
                sum23 = 0;
               

            if (arrMap[x + t][y] == 'x')
            {
                sum24 = sum24 + 1;
                flag44 = true;
            }
                
            if (arrMap[x - t][y] == 'x')
            {
                sum24 = sum24 + 1;
                flag44 = true;
            }
            if (!flag44)
                sum24 = 0;
        }
        if (sum21 == 4 || sum22 == 4 || sum23 == 4 || sum24 == 4)
        {
            printf("The player 2 win this game!\n");
            exit(0);
        }
    }

    for (q = 1; q < 17; q++)
    {
        for (e = 1; e < 17; e++)
        {
            if (arrMap[q][e] == 'x')
                add1++;
            if (arrMap[q][e] == 'o')
                add2++;
        }
        if (add1 == 122 || add2==122)
        {
            printf("Draw!");
            exit(0);
        }
    }
}

void PrintMap()
{
    for (int i = 0; i < 17; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if (i == 0 || i == 16)
            {
                arrMap[i][j] = '-';
                printf("%c", arrMap[i][j]);
            }
            else if (j == 0 || j == 16)
            {
                arrMap[i][j] = '|';
                printf("%c", arrMap[i][j]);
            }
            else {
                arrMap[i][j] = '+';
                printf("%c", arrMap[i][j]);
            }

        }
        printf("\n");
    }
}

int main()
{
    int u;

    PrintMap();

    while (1)
    {
        for (u = 1; u <= 2;)
        {
            printf("Player %d, this is your turn! please play chess:",u);
            scanf("%d,%d", &x, &y);

            if (x == 0 || x == 16)
                printf("Error Data\n");
            else if (y == 0 || y == 16)
                printf("Error Data\n");
            else
                u++;

            JudgeRepeat();
        }
        if (u == 2)
            u = 1;
    }
      
}