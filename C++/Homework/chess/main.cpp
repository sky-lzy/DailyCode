#include <iostream>
#include <string>
#include "ChessBoard.h"
#include "Player.h"
using namespace std;

int main()
{
    string n;
    cout << "请输入黑方姓名：" << endl;
    cin >> n;
    Player P1(n, Black);
    cout << "请输入白方姓名：" << endl;
    n = "";
    cin >> n;
    Player P2(n, White);
    ChessBoard chessBoard;
    bool flag = false, p = true;
    int x, y;
    while (!flag)
    {
        if (p)
        {
            cout << "黑方：" << endl;
            cin >> x >> y;
            if (P1.setChess(x, y, chessBoard))
            {
                p = !p;
                if (P1.Win(chessBoard,x,y))
                    flag = true;
            }
        }
        else
        {
            cout << "白方：" << endl;
            cin >> x >> y;
            if (P2.setChess(x, y, chessBoard))
            {
                p = !p;
                if (P2.Win(chessBoard,x,y))
                    flag = true;
            }
        }
    }
    if (!p)
        cout << "黑方五子连珠，获胜！" << endl;
    else
        cout << "白方五子连珠，获胜！" << endl;
    return 0;
}