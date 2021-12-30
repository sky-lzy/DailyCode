/*
 * @lc app=leetcode.cn id=91 lang=cpp
 *
 * [91] 解码方法
 */

#include <string>
using std::string;

// @lc code=start
class Solution
{
public:
    int numDecodings(string s)
    {
        int N = s.size();
        if (N == 1)
            return s[0] > '0';
        int x = (s[0] > '0'), y = (s[0] == '1' || (s[0] == '2' && s[1] <= '6')) + x * (s[1] > '0');
        for (int i = 2; i < N; i++)
        {
            int t = (s[i] > '0') * y + (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] <= '6')) * x;
            x = y;
            y = t;
        }
        return y;
    }
};
// @lc code=end
