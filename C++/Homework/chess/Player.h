#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "ChessType.h"
using namespace std;

class ChessBoard;

class Player
{
private:
    string name;
    ChessType chessType;

public:
    Player(string s, ChessType c);                      //构造函数
    ~Player();                                          //析构函数
    bool setChess(int row, int column, ChessBoard &ch); //玩家落子，并返回是否合法
    bool Win(ChessBoard &ch, int x, int y);             //判断是否获胜
};

#endif