#include <iostream>

struct Node
{
    int key;
    bool color; //true: 黑  false: 红
    Node *left;
    Node *right;
    Node *parent;

    Node() : key(0), color(true), left(nullptr), right(nullptr), parent(nullptr) {}
    Node(int inputKey) : key(inputKey), color(true), left(nullptr), right(nullptr), parent(nullptr) {}
    Node(int inputKey, bool inputColor) : key(inputKey), color(inputColor), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree
{
private:
    Node *root;
    int BlackHeight;

public:
    RBTree() {}

    //修改操作
    void InsertNode(int inputKey);

private:
    void LeftRotate(Node *r1, Node *r2);
    void RightRotate(Node *r1, Node *r2);
};
