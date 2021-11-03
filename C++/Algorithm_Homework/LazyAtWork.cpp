#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

//快速I/O函数
long long FastRead()
{
    char temp = getchar();
    while (temp < '0' || temp > '9')
        temp = getchar();
    long long v = 0;
    while (temp >= '0' && temp <= '9')
    {
        v = v * 10 + temp - '0';
        temp = getchar();
    }
    return v;
};

void FastWrite(long long output)
{
    char temp[10];
    long long n = 0;
    if (output == 0)
    {
        putchar('0');
        putchar('\n');
        return;
    }
    while (output)
    {
        temp[n++] = output % 10;
        output /= 10;
    }
    for (long long i = n - 1; i >= 0; i--)
        putchar('0' + temp[i]);
    putchar('\n');
};

//结点类
struct Node
{
    long long x;
    long long y;
    long long id;
    long long x_min;
    long long x_max;
    long long y_min;
    long long y_max;
    bool cut;
    Node *left;
    Node *right;
    // Node *parent;

    Node() : x(0), y(0), id(0), left(nullptr), right(nullptr) {}
    Node(long long input_x, long long input_y, long long input_id) : x(input_x), y(input_y), id(input_id), left(nullptr), right(nullptr) {}
};

//结点距离类
struct Distance
{
    long long distance;
    long long id;

    Distance() : distance(-1), id(-1) {}
    Distance(long long input_dis, long long input_id) : distance(input_dis), id(input_id) {}
    // friend bool operator<(const Distance &d1, const Distance &d2) { return d1.distance < d2.distance || (d1.distance == d2.distance && d1.id < d2.id); }
    friend bool operator>(const Distance &d1, const Distance &d2) { return d1.distance > d2.distance || (d1.distance == d2.distance && d1.id < d2.id); }
};

//KD树类
struct KDTree
{
    Node *root;
    std::priority_queue<Distance, std::vector<Distance>, std::greater<Distance>> FarDistance;
    std::stack<Node *> NodeList;

    KDTree() : root(nullptr) {}
    // ~KDTree();

    void Build(long long N, long long x_max, long long y_max);
    long long Query_BFS(long long x, long long y, long long k);
    long long Query_DFS(long long x, long long y, long long k);

private:
    void DeleteAll(Node *r);
    long long NodeDistance(long long x, long long y, Node *n);
    long long AreaDistance(long long x, long long y, Node *n);
    Node *DetailBuild(Node *p, Node *q, bool NowCut, long long x_min, long long x_max, long long y_min, long long y_max);
    void DetailQuery_BFS(Node *r, long long x, long long y, long long k);
    void DetailQuery_DFS(Node *r, long long x, long long y, long long k);
};

long long KDTree::NodeDistance(long long x, long long y, Node *n)
{
    return (long long)(x - n->x) * (long long)(x - n->x) + (long long)(y - n->y) * (long long)(y - n->y);
}

long long KDTree::AreaDistance(long long x, long long y, Node *n)
{
    long long x1 = (long long)(x - n->x_min) * (long long)(x - n->x_min);
    long long x2 = (long long)(x - n->x_max) * (long long)(x - n->x_max);
    long long y1 = (long long)(y - n->y_min) * (long long)(y - n->y_min);
    long long y2 = (long long)(y - n->y_max) * (long long)(y - n->y_max);
    return (x1 > x2 ? x1 : x2) + (y1 > y2 ? y1 : y2);
}

Node *KDTree::DetailBuild(Node *p, Node *q, bool NowCut, long long x_min, long long x_max, long long y_min, long long y_max)
{
    if (q <= p)
        return nullptr;
    if (q == p + 1)
    {
        p->x_min = x_min;
        p->x_max = x_max;
        p->y_min = y_min;
        p->y_max = y_max;
        return p;
    }

    Node *tempNode = p + (q - p) / 2;

    if (NowCut)
    {
        std::nth_element(p, tempNode, q, [](Node &temp1, Node &temp2)
                         { return temp1.x < temp2.x; });
        tempNode->x_min = x_min;
        tempNode->x_max = x_max;
        tempNode->y_min = y_min;
        tempNode->y_max = y_max;
        tempNode->left = DetailBuild(p, tempNode, !NowCut, x_min, tempNode->x, y_min, y_max);
        tempNode->right = DetailBuild(tempNode + 1, q, !NowCut, tempNode->x, x_max, y_min, y_max);
    }
    else
    {
        std::nth_element(p, tempNode, q, [](Node &temp1, Node &temp2)
                         { return temp1.y < temp2.y; });
        tempNode->x_min = x_min;
        tempNode->x_max = x_max;
        tempNode->y_min = y_min;
        tempNode->y_max = y_max;
        tempNode->left = DetailBuild(p, tempNode, !NowCut, x_min, x_max, y_min, tempNode->y);
        tempNode->right = DetailBuild(tempNode + 1, q, !NowCut, x_min, x_max, tempNode->y, y_max);
    }
    tempNode->cut = NowCut;
    return tempNode;
}

//广度优先搜索
void KDTree::DetailQuery_BFS(Node *r, long long x, long long y, long long k)
{
    if (r == nullptr)
        return;

    long long dis = NodeDistance(x, y, r);
    if (Distance(dis, r->id) > FarDistance.top())
    {
        FarDistance.pop();
        FarDistance.emplace(dis, r->id);
    }

    if (r->left != nullptr && AreaDistance(x, y, r->left) >= FarDistance.top().distance)
        DetailQuery_BFS(r->left, x, y, k);
    if (r->right != nullptr && AreaDistance(x, y, r->right) >= FarDistance.top().distance)
        DetailQuery_BFS(r->right, x, y, k);
}

//深度优先搜索
void KDTree::DetailQuery_DFS(Node *r, long long x, long long y, long long k)
{
    Node *nowNode = r;
    while (nowNode != nullptr)
    {
        if (nowNode != nullptr && Distance(NodeDistance(x, y, nowNode), nowNode->id) > FarDistance.top())
        {
            FarDistance.pop();
            FarDistance.emplace(NodeDistance(x, y, nowNode), nowNode->id);
        }
        if ((nowNode->cut && x < nowNode->x) || (!nowNode->cut && y < nowNode->y))
        {
            if (nowNode->left != nullptr && AreaDistance(x, y, nowNode->left) >= FarDistance.top().distance)
                NodeList.push(nowNode->left);
            if (nowNode->right != nullptr && AreaDistance(x, y, nowNode->right) >= FarDistance.top().distance)
                nowNode = nowNode->right;
            else
                break;
        }
        else
        {
            if (nowNode->right != nullptr && AreaDistance(x, y, nowNode->right) >= FarDistance.top().distance)
                NodeList.push(nowNode->right);
            if (nowNode->left != nullptr && AreaDistance(x, y, nowNode->left) >= FarDistance.top().distance)
                nowNode = nowNode->left;
            else
                break;
        }
    }

    while (!NodeList.empty())
    {
        Node *tempNode = NodeList.top();
        NodeList.pop();
        DetailQuery_DFS(tempNode, x, y, k);
    }
}

void KDTree::Build(long long N, long long x_max, long long y_max)
{
    Node *tempNode = new Node[N];
    for (long long count = 0; count < N; count++)
    {
        long long x = FastRead(), y = FastRead();
        tempNode[count] = Node(x, y, count);
    }

    root = DetailBuild(tempNode, tempNode + N, true, 0, x_max, 0, y_max);
}

long long KDTree::Query_BFS(long long x, long long y, long long k)
{
    for (long long i = 0; i < k; i++)
        FarDistance.emplace();
    DetailQuery_BFS(root, x, y, k);
    long long num = FarDistance.top().id;

    while (!FarDistance.empty())
        FarDistance.pop();
    return num;
}

long long KDTree::Query_DFS(long long x, long long y, long long k)
{
    for (long long i = 0; i < k; i++)
        FarDistance.emplace();
    DetailQuery_DFS(root, x, y, k);
    long long num = FarDistance.top().id;

    while (!FarDistance.empty())
        FarDistance.pop();
    while (!NodeList.empty())
        NodeList.pop();
    return num;
}

int main()
{
    KDTree tree;
    long long N, M;
    scanf("%lld%lld", &N, &M);
    tree.Build(N, 100000000ll, 100000000ll);
    for (long long i = 0; i < M; i++)
    {
        long long x = FastRead(), y = FastRead(), k = FastRead();
        // long long x, y, k;
        // scanf("%d%d%d", &x, &y, &k);
        // FastWrite(tree.Query_BFS(x, y, k));
        FastWrite(tree.Query_DFS(x, y, k));
    }

    return 0;
}
