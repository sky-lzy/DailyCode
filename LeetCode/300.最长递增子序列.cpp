/*
 * @lc app=leetcode.cn id=300 lang=cpp
 *
 * [300] 最长递增子序列
 */

#include <vector>
using namespace std;

// @lc code=start
class Solution
{
public:
    //dp: O(n^2)
    /* int lengthOfLIS(vector<int> &nums)
    {
        int N = nums.size();
        std::vector<int> dp(N, 1);
        for (int i = 1; i < N; i++)
        {
            for (int j = 0; j < i; j++)
                if (nums[i] > nums[j])
                    dp[i] = std::max(dp[i], dp[j] + 1);
        }
        int maxlen = 0;
        for (int i = 0; i < N; i++)
            maxlen = std::max(maxlen, dp[i]);
        return maxlen;
    } */

    //binary-search
    int lengthOfLIS(vector<int> &nums)
    {
        vector<int> List(nums.size());
        int maxlen = 0;
        for (int num : nums)
        {
            int ptr = 0, end = maxlen;
            while (end - ptr > 0)
                num > List[ptr + (end - ptr) / 2] ? (ptr = ptr + (end - ptr) / 2 + 1) : (end = ptr + (end - ptr) / 2);
            List[ptr] = num;
            if (ptr == maxlen)
                maxlen++;
        }
        return maxlen;
    }
};
// @lc code=end
