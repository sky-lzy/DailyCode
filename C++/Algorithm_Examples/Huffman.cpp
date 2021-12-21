//霍夫曼编码

#include <iostream>
#include <vector>
#include <string>
#include <queue>

struct Node
{
    int key;
    Node *left;
    Node *right;

    Node() : key(0), left(nullptr), right(nullptr) {}
    Node(int inputKey) : key(inputKey), left(nullptr), right(nullptr) {}
    Node(int inputKey, Node *inputLeft, Node *inputRight) : key(inputKey), left(inputLeft), right(inputRight) {}
};

struct CompareNode
{
    bool operator()(const Node *N1, const Node *N2) { return N1->key > N2->key; };
};

class Huffman
{
private:
    int N;
    Node *root;
    std::vector<Node> NodeList;
    std::priority_queue<Node *, std::vector<Node *>, CompareNode> NodeQueue;

public:
    Huffman() : N(0), root(nullptr) {}
    Huffman(int *inputValue, int inputN);

    void Construct();
    void print() const;

private:
    void print(Node *r, std::string str) const;
};

Huffman::Huffman(int *inputValue, int inputN) : N(inputN), root(nullptr), NodeList(2 * inputN - 1)
{
    for (int i = 0; i < inputN; i++)
    {
        NodeList[i] = Node(inputValue[i]);
        NodeQueue.emplace(&NodeList[i]);
    }
}

void Huffman::Construct()
{
    int i = N;
    while (NodeQueue.size() > 1)
    {
        auto tempNode1 = NodeQueue.top();
        NodeQueue.pop();
        auto tempNode2 = NodeQueue.top();
        NodeQueue.pop();
        NodeList[i] = Node(tempNode1->key + tempNode2->key, tempNode1, tempNode2);
        NodeQueue.emplace(&NodeList[i]);
        i++;
    }
    root = NodeQueue.top();
}

void Huffman::print() const
{
    print(root, std::string(""));
}

void Huffman::print(Node *r, std::string str) const
{
    if (!r)
        return;
    if (!r->left && !r->right)
    {
        std::cout << r->key << ": " << str << "\n";
        return;
    }
    print(r->left, str + "0");
    print(r->right, str + "1");
}

int main()
{
    int a[8] = {5, 29, 7, 8, 14, 23, 3, 11};
    Huffman huffman(a, 8);
    huffman.Construct();
    huffman.print();
    return 0;
}