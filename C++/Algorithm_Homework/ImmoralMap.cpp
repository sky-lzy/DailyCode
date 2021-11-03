#include <iostream>
#include <vector>
#include <queue>
#include <forward_list>
#include <algorithm>

struct EdgeNode
{
    int Number;
    int Weight;

    EdgeNode(int inputNumber, int inputWeight) : Number(inputNumber), Weight(inputWeight) {}
    friend bool operator>(const EdgeNode &E1, const EdgeNode &E2) {return E1.Weight > E2.Weight;}
};

class Map
{
private:
    int VertexNum;
    int EdgeNum;
    std::vector<std::forward_list<EdgeNode>> EdgeList;

public:
    //构造函数
    Map(int inputVerNum, int inputEdgeNum) : VertexNum(inputVerNum), EdgeNum(inputEdgeNum), EdgeList(inputVerNum) {}

    //图的构造
    void Build();
    //搜索最短路径
    void Search(int NS, int ND);

//内部方法实现
private:
    void DeleteEdge(int N1, int N2);
};

void Map::Build()
{
    for (int i = 0; i < EdgeNum; i++)
    {
        int N1, N2, e;
        scanf("%d%d%d", &N1, &N2, &e);
        EdgeList[N1].emplace_front(N2, e);
        EdgeList[N2].emplace_front(N1, e);
    }
}

void Map::Search(int NS, int ND)
{
    std::vector<int> WalkList({NS});
    std::priority_queue<EdgeNode, std::vector<EdgeNode>, std::greater<EdgeNode>> tempEdge;
    for (auto temptr = EdgeList[NS].begin(); temptr != EdgeList[NS].end(); temptr++)
        tempEdge.emplace(*temptr);
    
    while (!tempEdge.empty())
    {
        WalkList.emplace_back(tempEdge.top().Number);
    }
    
}

void Map::DeleteEdge(int N1, int N2)
{
    auto temptr = std::find_if(EdgeList[N1].begin(), EdgeList[N1].end(), [N2](const EdgeNode &tempEdge)
                               { return tempEdge.Number == N2; });
    if (temptr != EdgeList[N1].end())
        EdgeList[N1].erase_after(temptr);
    else
        throw("Edge Not Exist!");
    temptr = std::find_if(EdgeList[N2].begin(), EdgeList[N2].end(), [N1](const EdgeNode &tempEdge)
                          { return tempEdge.Number == N1; });
    if (temptr != EdgeList[N2].end())
        EdgeList[N2].erase_after(temptr);
    else
        throw("Edge Not Exist!");
    EdgeNum -= 1;
}

int main()
{
    int N, M;
    scanf("%d%d", &N, &M);
    Map map(N, M);
    map.Build();

    return 0;
}