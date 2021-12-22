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
    void Kruskal() const;
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

struct CompairEdge
{
    bool operator()(const std::tuple<int, int, int> &t1, const std::tuple<int, int, int> &t2) { return std::get<2>(t1) > std::get<2>(t2); }
};

void Graph::Kruskal() const
{
    std::vector<int> rootNode(NodeNum, 0x7fffffff);
    std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, CompairEdge> tempEdge;
    std::vector<std::tuple<int, int, int>> tempMST;
    for (int i = 0; i < NodeNum; i++)
        std::for_each(EdgeList[i].begin(), EdgeList[i].end(), [&tempEdge, &i](const std::pair<int, int> &t)
                      {
                          if (t.first > i)
                              tempEdge.emplace(i, t.first, t.second);
                      });
    while (!tempEdge.empty())
    {
        auto temp = tempEdge.top();
        tempEdge.pop();
        bool flag = true;
        if (rootNode[std::get<0>(temp)] < NodeNum && rootNode[std::get<1>(temp)] < NodeNum && rootNode[std::get<0>(temp)] == rootNode[std::get<1>(temp)])
            flag = false;
        else
        {
            if (rootNode[std::get<0>(temp)] > NodeNum && rootNode[std::get<1>(temp)] > NodeNum)
                rootNode[std::get<0>(temp)] = rootNode[std::get<1>(temp)] = std::get<0>(temp);
            else if (rootNode[std::get<0>(temp)] < NodeNum && rootNode[std::get<1>(temp)] > NodeNum)
                rootNode[std::get<1>(temp)] = rootNode[std::get<0>(temp)];
            else if (rootNode[std::get<0>(temp)] > NodeNum && rootNode[std::get<1>(temp)] < NodeNum)
                rootNode[std::get<0>(temp)] = rootNode[std::get<1>(temp)];
            else
            {
                int t = rootNode[std::get<0>(temp)];
                for (int i = 0; i < NodeNum; i++)
                    if (rootNode[i] == t)
                        rootNode[i] = rootNode[std::get<1>(temp)];
            }
        }

        if (flag)
            tempMST.emplace_back(std::get<0>(temp), std::get<1>(temp), std::get<2>(temp));
    }
    std::for_each(tempMST.begin(), tempMST.end(), [](const std::tuple<int, int, int> &t)
                  { std::cout << std::get<0>(t) << " -> " << std::get<1>(t) << "  cost: " << std::get<2>(t) << "\n"; });
}

int main()
{
    int NodeNum, EdgeNum;
    std::cin >> NodeNum >> EdgeNum;
    Graph graph(NodeNum, EdgeNum);
    // graph.Prim();
    graph.Kruskal();
    return 0;
}

/* ******
测例
8 12
0 1 32
0 2 29
0 5 60
0 6 51
0 7 31
1 7 21
3 4 34
3 5 18
4 5 40
4 6 51
4 7 46
6 7 25
****** */