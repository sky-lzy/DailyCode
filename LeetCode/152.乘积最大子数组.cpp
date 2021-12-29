/*
 * @lc app=leetcode.cn id=152 lang=cpp
 *
 * [152] 乘积最大子数组
 */

#include <vector>
using namespace std;

// @lc code=start
class Solution
{
public:
    int maxProduct(vector<int> &nums)
    {
        int N = nums.size();
        if (N == 1)
            return nums[0];
        int PR0 = max(0, nums[0]), NR0 = min(0, nums[0]), PR1, NR1;
        int mul = PR0;
        for (int i = 1; i < N; i++)
        {
            if (nums[i] > 0)
            {
                PR1 = max(nums[i], PR0 * nums[i]);
                NR1 = NR0 * nums[i];
            }
            else
            {
                PR1 = NR0 * nums[i];
                NR1 = min(PR0 * nums[i], nums[i]);
            }
            if (PR1 > mul)
                mul = PR1;
            PR0 = PR1;
            NR0 = NR1;
        }
        return mul;
    }
};
// @lc code=end
