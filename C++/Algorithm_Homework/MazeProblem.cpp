#include <iostream>
#include <vector>
#include <queue>
#include <stack>

#define MAPSIZE 10

//地图每一个结点
struct Node
{
    int x;
    int y;
    int p; //0:上, 1:左, 2:下, 3:右

    Node() : x(0), y(0), p(0) {}
    Node(int inputX, int inputY, int inputP) : x(inputX), y(inputY), p(inputP) {}
    bool operator==(const Node &tempNode) { return x == tempNode.x && y == tempNode.y && p == tempNode.p; }
};

//地图类
class Map
{
    //内部成员
private:
    int Lx;                           //长
    int Ly;                           //宽
    Node Start;                       //初始
    Node End;                         //终止
    bool MapState[MAPSIZE][MAPSIZE];  //地图状态, true有墙壁, false可通行
    bool IsWalk[MAPSIZE][MAPSIZE][4]; //是否经过, true已经过, false未经过
    int Move[MAPSIZE][MAPSIZE][4];    //记录经历, 0:F, 1:F2, 2:L, 3:R
    std::queue<Node> Walk;            //路径

    //公用接口
public:
    //构造函数
    Map(int inputLx, int inputLy);

    void BFS();         //广度优先搜索
    void print() const; //打印路径

    //内部实现方法
private:
    inline Node MoveF(const Node &tempNode, int step) const;   //向前移动step格
    inline bool IsWall(const Node &tempNode) const;            //判断路是否可行
    inline void TestNode(const Node &tempNode, int inputMove); //将此结点加入队列中
};

Map::Map(int inputLx, int inputLy) : Lx(inputLx), Ly(inputLy)
{
    for (int i = 0; i < Ly; i++)
        for (int j = 0; j < Lx; j++)
        {
            scanf("%d", &MapState[j][i]);
            IsWalk[j][i][0] = false;
            IsWalk[j][i][1] = false;
            IsWalk[j][i][2] = false;
            IsWalk[j][i][3] = false;
        }

    scanf("%d%d%d", &Start.x, &Start.y, &Start.p);
    Start.p--;
    scanf("%d%d%d", &End.x, &End.y, &End.p);
    End.p--;
}

inline Node Map::MoveF(const Node &tempNode, int step) const
{
    switch (tempNode.p)
    {
    case 0:
        return Node(tempNode.x, tempNode.y - step, tempNode.p);
        break;
    case 1:
        return Node(tempNode.x - step, tempNode.y, tempNode.p);
        break;
    case 2:
        return Node(tempNode.x, tempNode.y + step, tempNode.p);
        break;
    case 3:
        return Node(tempNode.x + step, tempNode.y, tempNode.p);
        break;
    default:
        break;
    }
    return Node();
}

inline bool Map::IsWall(const Node &tempNode) const
{
    if (tempNode.x < 0 || tempNode.x >= Lx || tempNode.y < 0 || tempNode.y >= Ly)
        return true; //没有越边界
    if (MapState[tempNode.x][tempNode.y])
        return true; //不是墙
    if (IsWalk[tempNode.x][tempNode.y][tempNode.p])
        return true; //没有经过
    return false;
}

inline void Map::TestNode(const Node &tempNode, int inputMove)
{
    Walk.emplace(tempNode);
    Move[tempNode.x][tempNode.y][tempNode.p] = inputMove;
    IsWalk[tempNode.x][tempNode.y][tempNode.p] = true;
}

void Map::BFS()
{
    bool flag = true; //控制循环
    Walk.emplace(Start);
    IsWalk[Start.x][Start.y][Start.p] = true;
    while (flag && !Walk.empty())
    {
        Node tempNode;
        //F
        tempNode = MoveF(Walk.front(), 1);
        if (tempNode == End)
            flag = false;
        if (!IsWall(tempNode))
        {
            TestNode(tempNode, 0);
            //F2
            tempNode = MoveF(Walk.front(), 2);
            if (tempNode == End)
                flag = false;
            if (!IsWall(tempNode))
                TestNode(tempNode, 1);
        }
        //L
        tempNode = Node(Walk.front().x, Walk.front().y, (Walk.front().p + 1) % 4);
        if (tempNode == End)
            flag = false;
        if (!IsWall(tempNode))
            TestNode(tempNode, 2);
        //R
        tempNode = Node(Walk.front().x, Walk.front().y, (Walk.front().p + 3) % 4);
        if (tempNode == End)
            flag = false;
        if (!IsWall(tempNode))
            TestNode(tempNode, 3);

        Walk.pop();
    }
}

void Map::print() const
{
    std::stack<int> tempWalk;
    Node tempNode(End);
    int count = 0;
    while (!(tempNode == Start))
    {
        count++;
        tempWalk.push(Move[tempNode.x][tempNode.y][tempNode.p]);
        switch (Move[tempNode.x][tempNode.y][tempNode.p])
        {
        case 0:
            tempNode = MoveF(tempNode, -1);
            break;
        case 1:
            tempNode = MoveF(tempNode, -2);
            break;
        case 2:
            tempNode.p = (tempNode.p + 3) % 4;
            break;
        case 3:
            tempNode.p = (tempNode.p + 1) % 4;
            break;
        }
    }
    printf("%d\n", count);
    while (!tempWalk.empty())
    {
        switch (tempWalk.top())
        {
        case 0:
            printf("F\n");
            break;
        case 1:
            printf("F2\n");
            break;
        case 2:
            printf("L\n");
            break;
        case 3:
            printf("R\n");
            break;
        }
        tempWalk.pop();
    }
}

int main()
{
    int Lx, Ly;
    scanf("%d%d", &Lx, &Ly);
    Map map(Lx, Ly);
    map.BFS();
    map.print();
    return 0;
}