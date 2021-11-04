#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <utility>
#include <forward_list>
#include <algorithm>

struct EdgeNode
{
    int Number1;
    int Number2;
    int Weight;

    EdgeNode() : Number1(-1), Number2(-1), Weight(0) {}
    EdgeNode(int inputNumber1, int inputNumber2, int inputWeight) : Number1(inputNumber1), Number2(inputNumber2), Weight(inputWeight) {}
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
        EdgeList[N1].emplace_back(N1, N2, e);
        EdgeList[N2].emplace_back(N2, N1, e);
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
    std::vector<int> WalkList({NS});
    std::priority_queue<EdgeNode, std::vector<EdgeNode>, std::greater<EdgeNode>> tempEdgeList;
    for (auto temptr = EdgeList[NS].begin(); temptr != EdgeList[NS].end(); temptr++)
        tempEdgeList.emplace(*temptr);
    MiniDis[NS].second = 0;

    while (!tempEdgeList.empty())
    {
        EdgeNode tempEdge(tempEdgeList.top());
        tempEdgeList.pop();
        if (MiniDis[tempEdge.Number1].second + tempEdge.Weight < MiniDis[tempEdge.Number2].second)
        {
            MiniDis[tempEdge.Number2].first.clear();
            MiniDis[tempEdge.Number2].first.emplace_back(tempEdge.Number1);
            MiniDis[tempEdge.Number2].second = MiniDis[tempEdge.Number1].second + tempEdge.Weight;
        }
        else if (MiniDis[tempEdge.Number1].second + tempEdge.Weight == MiniDis[tempEdge.Number2].second)
            MiniDis[tempEdge.Number2].first.emplace_back(tempEdge.Number1);
        else
            continue;

        if (std::find_if(WalkList.begin(), WalkList.end(), [&tempEdge](const int tempN)
                         { return tempN == tempEdge.Number2; }) == WalkList.end())
        {
            WalkList.emplace_back(tempEdge.Number2);
            for (auto temptr = EdgeList[tempEdge.Number2].begin(); temptr != EdgeList[tempEdge.Number2].end(); temptr++)
                if (std::find_if(WalkList.begin(), WalkList.end(), [temptr](const int tempN)
                                 { return tempN == temptr->Number2; }) == WalkList.end())
                    tempEdgeList.emplace(*temptr);
        }
    }
}

void Map::DeleteEdge(int N1, int N2)
{
    auto temptr = std::find_if(EdgeList[N1].begin(), EdgeList[N1].end(), [N2](const EdgeNode &tempEdge)
                               { return tempEdge.Number2 == N2; });
    if (temptr != EdgeList[N1].end())
        EdgeList[N1].erase(temptr);
    else
        throw("Edge Not Exist!");
    temptr = std::find_if(EdgeList[N2].begin(), EdgeList[N2].end(), [N1](const EdgeNode &tempEdge)
                          { return tempEdge.Number2 == N1; });
    if (temptr != EdgeList[N2].end())
        EdgeList[N2].erase(temptr);
    else
        throw("Edge Not Exist!");
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
    std::stack<int> PathNodeNumber({ND});
    int tempNumber = ND;
    while (PathNodeNumber.top() != NS)
    {
        if (!MiniDis[tempNumber].first.size())
            return;
        tempNumber = MiniDis[tempNumber].first[0];
        PathNodeNumber.push(tempNumber);
    }
    printf("start\n");
    while (!PathNodeNumber.empty())
    {
        printf("%d\n", PathNodeNumber.top());
        PathNodeNumber.pop();
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