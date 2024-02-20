
#include <stdio.h>
#include <stdbool.h>

#define ROWS 16//行数 
#define COLS 16//列数 

char board[ROWS][COLS]; // 棋盘

// 初始化棋盘
void initBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = '-';
        }
    }
}

// 打印棋盘
void printBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// 判断胜负
bool isWin(int row, int col, char player) {
    // 判断行胜负
    int count = 1;
    int i = row, j = col;
    while (count < 5 && j > 0 && board[i][j - 1] == player) {
        count++;
        j--;
    }
    i = row, j = col;
    while (count < 5 && j < COLS - 1 && board[i][j + 1] == player) {
        count++;
        j++;
    }
    if (count >= 5) {
        return true;
    }

    // 判断列胜负
    count = 1;
    i = row, j = col;
    while (count < 5 && i > 0 && board[i - 1][j] == player) {
        count++;
        i--;
    }
    i = row, j = col;
    while (count < 5 && i < ROWS - 1 && board[i + 1][j] == player) {
        count++;
        i++;
    }
    if (count >= 5) {
        return true;
    }

    // 判断正对角线胜负
    count = 1;
    i = row, j = col;
    while (count < 5 && i > 0 && j > 0 && board[i - 1][j - 1] == player) {
        count++;
        i--;
        j--;
    }
    i = row, j = col;
    while (count < 5 && i < ROWS - 1 && j < COLS - 1 && board[i + 1][j + 1] == player) {
        count++;
        i++;
        j++;
    }
    if (count >= 5) {
        return true;
    }

    // 判断反对角线胜负
    count = 1;
    i = row, j = col;
    while (count < 5 && i > 0 && j < COLS - 1 && board[i - 1][j + 1] == player) {
        count++;
        i--;
        j++;
    }
    i = row, j = col;
    while (count < 5 && i < ROWS - 1 && j > 0 && board[i + 1][j - 1] == player) {
        count++;
        i++;
        j--;
    }
    if (count >= 5) {
        return true;
    }

    return false;
}

int main() {
    int row, col, player = 1;

    initBoard();
    printBoard();

    while (true) {
        printf("玩家 %d开始: ", player);
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
            printf("越界了，请重新输人.\n");
            continue;
        }

        if (board[row][col] != '-') {
            printf("重复了，请重新输人\n");
            continue;
        }

        board[row][col] = (player == 1) ? '*' : '#';
        printBoard();

        if (isWin(row, col, board[row][col])) {
            printf("玩家 %d 赢了!\n", player);
            break;
        }

        player = (player == 1) ? 2 : 1;
    }

    return 0;
}