/*
 * @lc app=leetcode.cn id=1441 lang=cpp
 *
 * [1441] 用栈操作构建数组
 */

#include <vector>
#include <string>
using namespace std;

// @lc code=start
class Solution
{
public:
    vector<string> buildArray(vector<int> &target, int n)
    {
        vector<string> oper;
        int temp = 0;
        for (auto i : target)
        {
            oper.emplace_back("Push");
            while (i - temp++ > 1)
            {
                oper.emplace_back("Pop");
                oper.emplace_back("Push");
            }
        }
        return oper;
    }
};
// @lc code=end
