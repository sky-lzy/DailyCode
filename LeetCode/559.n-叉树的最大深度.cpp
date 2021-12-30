/*
 * @lc app=leetcode.cn id=559 lang=cpp
 *
 * [559] N 叉树的最大深度
 */

#include <vector>
#include <stack>
using namespace std;

// @lc code=start

/* // Definition for a Node.
class Node
{
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, vector<Node *> _children)
    {
        val = _val;
        children = _children;
    }
};
 */

class Solution
{
public:
    int maxDepth(Node *root)
    {
        if (!root)
            return 0;
        int depth = 0;
        stack<pair<Node *, int>> temp({make_pair(root, 1)});
        while (!temp.empty())
        {
            auto ptr = temp.top();
            temp.pop();
            for (auto i : ptr.first->children)
                temp.emplace(i, ptr.second + 1);
            if (ptr.second > depth)
                depth = ptr.second;
        }
        return depth;
    }
};
// @lc code=end
