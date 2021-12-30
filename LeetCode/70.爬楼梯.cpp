/*
 * @lc app=leetcode.cn id=70 lang=cpp
 *
 * [70] 爬楼梯
 */

// @lc code=start
class Solution
{
public:
    int climbStairs(int n)
    {
        if (n == 1) return 1;
        int x = 1, y = 2;
        for (int i = 3; i <= n; i++)
        {
            int t = y;
            y = x + y;
            x = t;
        }
        return y;
    }
};
// @lc code=end
