//全源最短路径：Floyd算法，有向图

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

class Graph
{
private:
    int NodeNum;
    int EdgeNum;
    std::vector<std::vector<int>> Cost;

public:
    Graph() : NodeNum(0), EdgeNum(0) {}
    Graph(int inputNodeNum, int inputEdgeNum);

    void Floyd();
    void print() const;
};

Graph::Graph(int inputNodeNum, int inputEdgeNum) : NodeNum(inputNodeNum), EdgeNum(inputEdgeNum), Cost(inputNodeNum, std::vector<int>(inputNodeNum, 0x0fffffff))
{
    for (int i = 0; i < NodeNum; i++)
        Cost[i][i] = 0;
    for (int i = 0; i < EdgeNum; i++)
    {
        int N1, N2, value;
        std::cin >> N1 >> N2 >> value;
        Cost[N1][N2] = value;
        // Cost[N2][N1] = value;
    }
}

void Graph::Floyd()
{
    for (int i = 0; i < NodeNum; i++)
        for (int j = 0; j < NodeNum; j++)
            for (int k = 0; k < NodeNum; k++)
                if (Cost[i][j] + Cost[k][i] < Cost[k][j])
                    Cost[k][j] = Cost[i][j] + Cost[k][i];
}

void Graph::print() const
{
    std::cout << std::setw(4);
    std::cout << "    ";
    for (int i = 0; i < NodeNum; i++)
        std::cout << std::setw(4) << i;
    std::cout << "\n";
    for (int i = 0; i < NodeNum; i++)
    {
        std::cout << std::setw(4) << i;
        for (int j = 0; j < NodeNum; j++)
            std::cout << std::setw(4) << Cost[i][j];
        std::cout << "\n";
    }
}

int main()
{
    int NodeNum, EdgeNum;
    std::cin >> NodeNum >> EdgeNum;
    Graph graph(NodeNum, EdgeNum);
    graph.Floyd();
    graph.print();
    return 0;
}

/* ******
测例：
6 11
0 1 41
0 5 29
1 2 51
1 4 32
2 3 50
3 0 45
3 5 38
4 2 32
4 3 36
5 1 29
5 4 21
****** */