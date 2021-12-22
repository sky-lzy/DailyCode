#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <tuple>
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

void Graph::Prim() const
{
    std::vector<bool> tempNode(NodeNum, false);
    std::vector<std::tuple<int, int, int>> tempMST;
    tempNode[0] = true;
    for (int i = 0; i < NodeNum - 1; i++)
    {
        std::tuple<int, int, int> tempEdge(0, 0, 0x7fffffff);
        for (int j = 0; j < NodeNum; j++)
            if (tempNode[j])
                std::for_each(EdgeList[j].begin(), EdgeList[j].end(), [&tempNode, &tempEdge, &j](const std::pair<int, int> &t) -> void
                              {
                                  if (!tempNode[t.first] && t.second < std::get<2>(tempEdge))
                                      tempEdge = std::make_tuple(j, t.first, t.second);
                              });
        tempNode[std::get<1>(tempEdge)] = true;
        tempMST.emplace_back(tempEdge);
    }

    std::for_each(tempMST.begin(), tempMST.end(), [](const std::tuple<int, int, int> &t)
                  { std::cout << std::get<0>(t) << " -> " << std::get<1>(t) << "  cost: " << std::get<2>(t) << "\n"; });
}

int main()
{
    int NodeNum, EdgeNum;
    std::cin >> NodeNum >> EdgeNum;
    Graph graph(NodeNum, EdgeNum);
    graph.Prim();
    return 0;
}