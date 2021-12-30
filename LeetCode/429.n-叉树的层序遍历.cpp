/*
 * @lc app=leetcode.cn id=429 lang=cpp
 *
 * [429] N 叉树的层序遍历
 */

// @lc code=start

#include <vector>
#include <queue>
using namespace std;

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
}; */

class Solution
{
public:
    vector<vector<int>> levelOrder(Node *root)
    {
        vector<vector<int>> data;
        queue<Node *> temp({root, nullptr});
        if (!root)
            return data;

        int height = 0;
        while (temp.front())
        {
            Node *ptr = temp.front();
            temp.pop();
            data.emplace_back();
            while (ptr)
            {
                data[height].push_back(ptr->val);
                for (auto i : ptr->children)
                    temp.push(i);
                ptr = temp.front();
                temp.pop();
            }
            temp.push(nullptr);
            height++;
        }
        return data;
    }
};
// @lc code=end
