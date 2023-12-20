#include <stdio.h>

#define boardsize 15

char board[boardsize][boardsize];

int initboard() {
    for (int i = 0; i < boardsize; i++) {
        for (int j = 0; j < boardsize; j++) {
            board[i][j] = '*';
        }
    }
    return 0;
}

int printboard() {
    for (int i = 0; i < boardsize; i++) {
        for (int j = 0; j < boardsize; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int validmove(int x, int y) {
    if (x < 0 || x >= boardsize || y < 0 || y >= boardsize) {
        return 0;
    }
    if (board[x][y] != '*') {
        return 0;
    }
    return 1;
}

int palyermove(int x, int y, char player) {
    if (x < 0 || x >= boardsize || y < 0 || y >= boardsize) {
        return 0;
    }
    board[x][y] = player;
}

int winner(char player) {
    for (int i = 0; i < boardsize; i++) {
        for (int j = 0; j < boardsize; j++) {
            if (board[i][j] != player) {
                continue;
            }
            int count = 1;
            for (int k = 1; k < boardsize; k++) {
                if (board[i][j + k] == player) {
                    count++;
                }
                else {
                    break;
                }
            }
            if (count >= 5) {
                return 1;
            }

            count = 1;
            for (int k = 1; k < boardsize; k++) {
                if (board[i + k][j] == player) {
                    count++;
                }
                else {
                    break;
                }
            }
            if (count >= 5) {
                return 1;
            }
        }
    }

    return 0;
}

int main() {
    initboard();

    printboard();

    int x, y;
    char player = 'X';

    while (1) {
        printf("请输入落子位置（x y）：");
        scanf_s("%d%d", &x, &y);

        if (!validmove(x, y)) {
            printf("无效的落子位置，请重新输入。\n");
            continue;
        }

        palyermove(x, y, player);
        printboard();

        if (winner(player)) {
            printf("玩家 %c 获胜！\n", player);
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
    }


    return 0;
}


