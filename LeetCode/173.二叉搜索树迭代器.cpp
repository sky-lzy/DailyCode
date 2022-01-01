/*
 * @lc app=leetcode.cn id=173 lang=cpp
 *
 * [173] 二叉搜索树迭代器
 */

#include <stack>
using namespace std;

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

/* struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
}; */

class BSTIterator
{
private:
    TreeNode *ptr;
    stack<TreeNode *> list;

public:
    BSTIterator(TreeNode *root) : ptr(root) {}

    int next()
    {
        while (ptr)
        {
            list.emplace(ptr);
            ptr = ptr->left;
        }
        ptr = list.top();
        list.pop();
        int temp = ptr->val;
        ptr = ptr->right;
        return temp;
    }

    bool hasNext() { return ptr || !list.empty(); }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
// @lc code=end
