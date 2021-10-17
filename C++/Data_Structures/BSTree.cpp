#include <iostream>

//结点
struct Node
{
    int key;
    Node *left;
    Node *right;
    Node *parent;

    Node() : key(0), left(nullptr), right(nullptr), parent(nullptr) {}
    Node(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}
};

//二叉搜索树
struct BSTree
{
    //根结点
    Node *root;

    //构造和析构函数
    BSTree() : root(nullptr) {}
    ~BSTree();

    //查询操作
    Node *Search(Node *r, int k) const; //查找
    Node *Maximum(Node *r) const;       //最大结点
    Node *Minimum(Node *r) const;       //最小结点
    void Inorder_walk(Node *r) const;   //中序遍历
    Node *Successor(Node *r) const;     //后继
    Node *Predecessor(Node *r) const;   //前驱

    //修改操作
    void Insert(int k);                 //插入
    void Delete(Node *r);               //删除

    //树的构建
    void Build(int *keys, int n);
};

BSTree::~BSTree()
{
}

void BSTree::Build(int *keys, int n)
{
    for (int i = 0; i < n; i++)
        Insert(keys[i]);
}

Node *BSTree::Search(Node *r, int k) const
{
    if (r == nullptr || k == r->key)
        return r;
    if (k < r->key)
        return Search(r->left, k);
    else
        return Search(r->right, k);
}

Node *BSTree::Maximum(Node *r) const
{
    while (r->right != nullptr)
        r = r->right;
    return r;
}

Node *BSTree::Minimum(Node *r) const
{
    while (r->left != nullptr)
        r = r->left;
    return r;
}

void BSTree::Inorder_walk(Node *r) const
{
    if (r != nullptr)
    {
        Inorder_walk(r->left);
        std::cout << r->key;
        Inorder_walk(r->right);
    }
}

Node *BSTree::Successor(Node *r) const
{
    if (r->right != nullptr)
        return Minimum(r->right);
    Node *temp = r->parent;
    while (temp != nullptr && r == temp->right)
    {
        r = temp;
        temp = temp->parent;
    }
    return temp;
}

Node *BSTree::Predecessor(Node *r) const
{
    if (r->left != nullptr)
        return Maximum(r->left);
    Node *temp = r->parent;
    while (temp != nullptr && r == temp->left)
    {
        r = temp;
        temp = temp->parent;
    }
    return temp;
}

void BSTree::Insert(int k)
{
    Node *temp = new Node(k);
    Node *x = root, *y = nullptr;
    while (x != nullptr)
    {
        y = x;
        if (k < x->key)
            x = x->left;
        else
            x = x->right;
    }

    if (y == nullptr)
        root = temp;
    else if (k < y->key)
    {
        y->left = temp;
        temp->parent = y;
    }
    else
    {
        y->right = temp;
        temp->parent = y;
    }
}

