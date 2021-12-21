//实现二叉树的(非递归)前序、中序、后序遍历

#include <iostream>
#include <utility>
#include <stack>
#include <queue>

class Tree
{
private:
    int *key;
    int n;

public:
    Tree() : key(nullptr), n(0) {}
    Tree(int *input, int inputn);

    ~Tree() { delete[] key; }

    void PreOrder() const;
    void InOrder() const;
    void PostOrder() const;
    void LevelOrder() const;
};

Tree::Tree(int *input, int inputn) : n(inputn)
{
    key = new int[inputn];
    for (int i = 0; i < inputn; i++)
        key[i] = input[i];
}

void Tree::PreOrder() const
{
    std::stack<int> temp;
    int i = 0;
    while (i < n)
    {
        std::cout << key[i] << " ";
        if (2 * i + 2 < n)
            temp.push(2 * i + 2);
        if (2 * i + 1 < n)
            i = 2 * i + 1;
        else if (!temp.empty())
        {
            i = temp.top();
            temp.pop();
        }
        else
            break;
    }
    std::cout << "\n";
}

void Tree::InOrder() const
{
    std::stack<int> temp;
    int i = 0;
    while (i < n || !temp.empty())
    {
        while (i < n)
        {
            temp.push(i);
            i = i * 2 + 1;
        }
        i = temp.top();
        temp.pop();
        std::cout << key[i] << " ";
        i = 2 * i + 2;
    }
    std::cout << "\n";
}

void Tree::PostOrder() const
{
    std::stack<std::pair<int, bool>> temp;
    int i = 0;
    while (i < n || !temp.empty())
    {
        while (i < n)
        {
            temp.push(std::make_pair(i, false));
            i = 2 * i + 1;
        }
        auto t = temp.top();
        i = t.first;
        temp.pop();
        if (t.second)
        {
            std::cout << key[i] << " ";
            i = 0x7fffffff;
        }
        else
        {
            temp.push(std::make_pair(i, true));
            i = 2 * i + 2;
        }
    }
    std::cout << "\n";
}

void Tree::LevelOrder() const
{
    std::queue<int> temp({0});
    while (!temp.empty())
    {
        int i = temp.front();
        temp.pop();
        std::cout << i << " ";
        if (2 * i + 1 < n)
            temp.push(2 * i + 1);
        if (2 * i + 2 < n)
            temp.push(2 * i + 2);
    }
    std::cout << "\n";
}

int main()
{
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Tree tree(a, 10);
    tree.PreOrder();
    tree.InOrder();
    tree.PostOrder();
    tree.LevelOrder();
    return 0;
}