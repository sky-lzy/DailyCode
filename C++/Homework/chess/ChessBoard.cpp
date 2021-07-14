#include <iostream>
#include "ChessBoard.h"
using namespace std;

int ChessBoard::step = 0;

ChessBoard::ChessBoard() : board{0} //初始化棋盘
{
    cout << "游戏开始，请黑方先落子" << endl;
    show();
}

ChessBoard::~ChessBoard()
{
    cout << "游戏结束，再见！" << endl;
}

void ChessBoard::show()
{
    int i, j;
    for (i = 1; i <= 15; i++)
    {
        for (j = 1; j <= 15; j++)
        {
            if (board[i][j] == 0)
                cout << "+ ";
            else if (board[i][j] == 1)
                cout << "● ";
            else if (board[i][j] == 2)
                cout << "○ ";
        }
        cout << endl;
    }
}

void ChessBoard::SetChess(ChessType c, int row, int column)
{
    if (c == Black)
        board[row][column] = 1;
    else
        board[row][column] = 2;
    show();
    step++;
}

bool ChessBoard::ValidPlace(int row, int column)
{
    if (row >= 1 && row <= 15 && column >= 1 && column <= 15) //不超范围
        if (board[row][column] == 0)                          //落子于空位处
            return true;
        else
        {
            cout << "此位置不可以落子" << endl;
            return false;
        }
    else
    {
        cout << "超出棋盘范围" << endl;
        return false;
    }
}

bool ChessBoard::Win(ChessType c, int row, int column)
{
    int s;
    bool flag = false;
    if (FiveChesses(c, row, column, 1, 1))
        flag = true;
    if (FiveChesses(c, row, column, 1, 0) && !flag)
        flag = true;
    if (FiveChesses(c, row, column, 1, -1) && !flag)
        flag = true;
    if (FiveChesses(c, row, column, 0, 1) && !flag)
        flag = true;
    if (flag)
        cout << "一共走了" << step << "步" << endl;
    return flag;
}

bool ChessBoard::FiveChesses(ChessType c, int row, int column, int i, int j)
{
    int s = 1;
    bool flag = false;
    for (int k = 1; k < 5; k++)
    {
        if (row + i * k > 15 || row + i * k < 1 || column + j * k > 15 || column + j * k < 1)
            break;
        if (board[row + i * k][column + j * k] != (int)c)
            break;
        s++;
    }
    for (int k = 1; k < 5; k++)
    {
        if (row - i * k > 15 || row - i * k < 1 || column - j * k > 15 || column - j * k < 1)
            break;
        if (board[row - i * k][column - j * k] != (int)c)
            break;
        s++;
    }
    if (s >= 5)
        flag = true;
    return flag;
}