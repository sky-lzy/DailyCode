/*
 * @lc app=leetcode.cn id=674 lang=cpp
 *
 * [674] 最长连续递增序列
 */

#include <vector>
#include <algorithm>
using namespace std;

// @lc code=start
class Solution
{
public:
    int findLengthOfLCIS(vector<int> &nums)
    {
        int N = nums.size();
        vector<int> Length(N, 1);
        for (int i = 1; i < N; i++)
        {
            if (nums[i] > nums[i - 1])
                Length[i] = Length[i - 1] + 1;
        }
        return *max_element(Length.begin(), Length.end());
    }
};
// @lc code=end
