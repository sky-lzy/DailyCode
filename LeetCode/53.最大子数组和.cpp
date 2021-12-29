/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子数组和
 */

#include <vector>
using namespace std;

// @lc code=start
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int N = nums.size(), maxsum = -0x7fffffff;
        int tempsum = 0;
        for (int i = 0; i < N; i++)
        {
            tempsum = max(nums[i], tempsum + nums[i]);
            if (tempsum > maxsum)
                maxsum = tempsum;
        }
        return maxsum;
    }
};
// @lc code=end
