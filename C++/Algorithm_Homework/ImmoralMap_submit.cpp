#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <utility>
#include <algorithm>

struct EdgeNode
{
    int Number;
    int Weight;

    EdgeNode() : Number(-1), Weight(0) {}
    EdgeNode(int inputNumber, int inputWeight) : Number(inputNumber), Weight(inputWeight) {}
    friend bool operator>(const EdgeNode &E1, const EdgeNode &E2) { return E1.Weight > E2.Weight; }
};

class Map
{
private:
    //图的数据信息
    int VertexNum;                               //顶点数目
    int EdgeNum;                                 //边数
    std::vector<std::vector<EdgeNode>> EdgeList; //边端点和权值

    //从顶点开始到每个点的最短距离储存
    std::vector<std::pair<std::vector<int>, int>> MiniDis;

public:
    //构造函数
    Map(int inputVerNum, int inputEdgeNum);

    //图的构造
    void Build();
    //搜索最短路径
    void Search(int NS, int ND);

    //内部方法实现
private:
    //删除边
    void DeleteEdge(int N1, int N2);
    //删除NS到ND的所有最短路径
    void DeleteAllPath(int NS, int ND);
    //Dijkstra算法
    void Disjkstra(int NS);
    //显示一种最短路径
    void ShowPath(int NS, int ND) const;
    //寻找并显示一条“几乎”最短路径
    void SearchShortPath(int NS, int ND);
};

Map::Map(int inputVerNum, int inputEdgeNum) : VertexNum(inputVerNum), EdgeNum(inputEdgeNum), EdgeList(inputVerNum), MiniDis(inputVerNum)
{
    std::for_each(MiniDis.begin(), MiniDis.end(), [](std::pair<std::vector<int>, int> &tempMini)
                  { tempMini.second = 0x7fffffff; });
}

void Map::Build()
{
    for (int i = 0; i < EdgeNum; i++)
    {
        int N1, N2, e;
        scanf("%d%d%d", &N1, &N2, &e);
        EdgeList[N1].emplace_back(N2, e);
        EdgeList[N2].emplace_back(N1, e);
    }
}

void Map::Search(int NS, int ND)
{
    Disjkstra(NS);
    ShowPath(NS, ND);
    DeleteAllPath(NS, ND);
    SearchShortPath(NS, ND);
}

void Map::Disjkstra(int NS)
{
    std::vector<bool> WalkList(VertexNum, false);
    std::priority_queue<EdgeNode, std::vector<EdgeNode>, std::greater<EdgeNode>> tempEdgeList;
    tempEdgeList.emplace(NS, 0);
    MiniDis[NS].second = 0;

    while (!tempEdgeList.empty())
    {
        EdgeNode tempEdge(tempEdgeList.top());
        tempEdgeList.pop();

        if (WalkList[tempEdge.Number])
            continue;
        WalkList[tempEdge.Number] = true;
        for (auto Edge_i : EdgeList[tempEdge.Number])
        {
            auto nowWeight = Edge_i.Weight + MiniDis[tempEdge.Number].second;
            if (nowWeight > MiniDis[Edge_i.Number].second)
                continue;
            else if (nowWeight < MiniDis[Edge_i.Number].second)
            {
                MiniDis[Edge_i.Number].first.clear();
                MiniDis[Edge_i.Number].first.emplace_back(tempEdge.Number);
                MiniDis[Edge_i.Number].second = nowWeight;
            }
            else
                MiniDis[Edge_i.Number].first.emplace_back(tempEdge.Number);
            if (!WalkList[Edge_i.Number])
                tempEdgeList.emplace(Edge_i.Number, nowWeight);
        }
    }
}

void Map::DeleteEdge(int N1, int N2)
{
    auto temptr = std::find_if(EdgeList[N1].begin(), EdgeList[N1].end(), [N2](const EdgeNode &tempEdge)
                               { return tempEdge.Number == N2; });
    if (temptr != EdgeList[N1].end())
        EdgeList[N1].erase(temptr);
    else
        return;
    temptr = std::find_if(EdgeList[N2].begin(), EdgeList[N2].end(), [N1](const EdgeNode &tempEdge)
                          { return tempEdge.Number == N1; });
    if (temptr != EdgeList[N2].end())
        EdgeList[N2].erase(temptr);
    else
        return;
    EdgeNum -= 1;
}

void Map::DeleteAllPath(int NS, int ND)
{
    if (NS == ND)
        return;
    for (auto i : MiniDis[ND].first)
    {
        DeleteEdge(i, ND);
        DeleteAllPath(NS, i);
    }
}

void Map::ShowPath(int NS, int ND) const
{
    if (MiniDis[ND].second == 0x7fffffff)
        return;

    std::stack<int> ShowNodeList({ND});
    int tempNodeNumber = ND;
    while (ShowNodeList.top() != NS)
    {
        ShowNodeList.emplace(MiniDis[tempNodeNumber].first[0]);
        tempNodeNumber = MiniDis[tempNodeNumber].first[0];
    }
    printf("start\n");
    while (!ShowNodeList.empty())
    {
        printf("%d\n", ShowNodeList.top());
        ShowNodeList.pop();
    }
    printf("end\n%d\n", MiniDis[ND].second);
}

void Map::SearchShortPath(int NS, int ND)
{
    for (auto temptr = MiniDis.begin(); temptr != MiniDis.end(); temptr++)
    {
        temptr->first.clear();
        temptr->second = 0x7fffffff;
    }
    Disjkstra(NS);
    ShowPath(NS, ND);
}

int main()
{
    int N, M, NS, ND;
    scanf("%d%d", &N, &M);
    Map map(N, M);
    map.Build();
    scanf("%d%d", &NS, &ND);
    map.Search(NS, ND);

    return 0;
}