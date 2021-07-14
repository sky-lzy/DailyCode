#include "Player.h"
#include "ChessBoard.h"

Player::Player(string s, ChessType c) : name(s), chessType(c) {}

Player::~Player() {}

bool Player::setChess(int row, int column, ChessBoard &ch)
{
    if (ch.ValidPlace(row, column))
    {
        ch.SetChess(chessType, row, column);
        return true;
    }
    else
        return false;
}

bool Player::Win(ChessBoard &ch, int x, int y)
{
    return ch.Win(chessType, x, y);
}