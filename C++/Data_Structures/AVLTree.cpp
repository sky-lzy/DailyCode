#include <iostream>

struct Node
{
    int key;
    Node *left;
    Node *right;
    Node *parent;
    
    Node() : key(0), left(nullptr), right(nullptr), parent(nullptr) {}
    Node(int inputkey) : key(inputkey), left(nullptr), right(nullptr), parent(nullptr) {}
};

class AVLTree
{
private:
    Node *root;
public:
    AVLTree() {}
};
