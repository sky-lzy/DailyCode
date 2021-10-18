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
    Node *Successor(Node *r) const;     //后继
    Node *Predecessor(Node *r) const;   //前驱
    void Print() const;                 //按序打印信息

    //修改操作
    void Insert(int k);   //插入
    void Delete(Node *r); //删除

    //树的构建
    void Build(int *keys, int n);

//内部实现方法
private:
    void Transplant(Node *r1, Node *r2); //移植子树
    void Inorder_walk(Node *r) const;    //中序遍历
    void DeleteAll(Node *r);             //删除子树
};

BSTree::~BSTree()
{
    DeleteAll(root);
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
        std::cout << r->key << " ";
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

void BSTree::Delete(Node *r)
{
    if (r->left == nullptr)
        Transplant(r->right, r);
    else if (r->right == nullptr)
        Transplant(r->left, r);
    else
    {
        Node *y = Minimum(r->right);
        if (y->parent != r)
        {
            Transplant(y->right, y);
            y->right = r->right;
            y->right->parent = y;
        }

        Transplant(y, r);
        y->left = r->left;
        y->left->parent = y;
    }
    delete r;
}

void BSTree::DeleteAll(Node *r)
{
    if (r != nullptr)
    {
        if (!r && r == r->parent->left)
            r->parent->left = nullptr;
        else if (!r && r == r->parent->right)
            r->parent->right = nullptr;
        DeleteAll(r->left);
        DeleteAll(r->right);
        delete r;
    }
}

void BSTree::Transplant(Node *r1, Node *r2)
{
    if (r2->parent == nullptr)
        root = r1;
    else if (r2 == r2->parent->left)
        r2->parent->left = r1;
    else
        r2->parent->right = r1;
    if (r1 != nullptr)
        r1->parent = r2->parent;
}

void BSTree::Print() const
{
    Inorder_walk(root);
}

//测试代码
int main()
{
    int a[10] = {3, 8, 9, 6, 1, 0, 5, 2, 7, 4};
    BSTree tree;
    tree.Build(a, 10);
    tree.Insert(10);
    tree.Delete(tree.Search(tree.root, 5));
    tree.Delete(tree.Search(tree.root, 3));
    tree.Delete(tree.Search(tree.root, 8));
    tree.Print();
    return 0;
}