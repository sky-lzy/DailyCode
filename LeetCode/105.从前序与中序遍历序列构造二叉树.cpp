/*
 * @lc app=leetcode.cn id=105 lang=cpp
 *
 * [105] 从前序与中序遍历序列构造二叉树
 */

#include <vector>
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
    TreeNode *buildTree(const vector<int> &preorder, const vector<int> &inorder)
    {
        if (preorder.size() == 0)
            return nullptr;
        TreeNode *temp = new TreeNode(preorder[0]);
        auto ptr = find(inorder.begin(), inorder.end(), preorder[0]);
        temp->left = buildTree(vector<int>(preorder.begin() + 1, preorder.begin() + (ptr - inorder.begin()) + 1), vector<int>(inorder.begin(), ptr));
        temp->right = buildTree(vector<int>(preorder.begin() + (ptr - inorder.begin()) + 1, preorder.end()), vector<int>(ptr + 1, inorder.end()));
        return temp;
    }
};
// @lc code=end
