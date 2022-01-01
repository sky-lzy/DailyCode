/*
 * @lc app=leetcode.cn id=98 lang=cpp
 *
 * [98] 验证二叉搜索树
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

class Solution
{
public:
    bool isValidBST(TreeNode *root)
    {
        // int temp = -0x7fffffff;
        long long temp = -0x7fffffffffffffff;
        stack<TreeNode *> list;
        while (root || !list.empty())
        {
            while (root)
            {
                list.emplace(root);
                root = root->left;
            }
            root = list.top();
            list.pop();
            if (root->val <= temp)
                return false;
            temp = root->val;
            root = root->right;
        }
        return true;
    }
};
// @lc code=end
