#include <iostream>
#include <utility>
#include <vector>
#include <queue>

class Graph
{
private:
    // std::vector<int> NodeList;
    int NodeNum;
    int EdgeNum;
    std::vector<std::vector<std::pair<int, int>>> EdgeList;

public:
    Graph() : NodeNum(0), EdgeList(0) {}
    Graph(int inputNodeNum, int inputEdgeNum);

    void Prim() const;
};

Graph::Graph(int inputNodeNum, int inputEdgeNum) : NodeNum(inputNodeNum), EdgeNum(inputEdgeNum), EdgeList(inputNodeNum)
{
    for (int i = 0; i < EdgeNum; i++)
    {
        int N1, N2, value;
        std::cin >> N1 >> N2 >> value;
        EdgeList[N1].emplace_back(std::make_pair(N2, value));
        EdgeList[N2].emplace_back(std::make_pair(N1, value));
    }
}

struct CompairEdge
{
    bool operator()(const std::pair<int, int> &p1, const std::pair<int, int> &p2) { return p1.second > p2.second; }
};

void Graph::Prim() const
{
    std::vector<bool> tempNode(NodeNum, false);
    std::vector<std::pair<int, int>> tempEdge;
    tempNode[0] = true;
    while (tempEdge.size() < NodeNum)
    {
    }
}