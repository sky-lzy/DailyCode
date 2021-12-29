/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */

#include <vector>
#include <unordered_map>
using namespace std;

// @lc code=start
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        //O(n^2)
        /* int N = nums.size();
        for (int i = 0; i < N - 1; i++)
        {
            for (int j = i + 1; j < N; j++)
            {
                if (nums[i] + nums[j] == target)
                    return vector<int>({i, j});
            }
        }
        return vector<int>({0, 0}); */

        //O(n)
        int N = nums.size();
        unordered_map<int, int> Map;
        for (int i = 0; i < N; i++)
        {
            if (Map.find(target - nums[i]) != Map.end())
                return vector<int>({Map[target - nums[i]], i});
            Map.emplace(make_pair(nums[i], i));
        }
        return vector<int>(0, 0);
    }
};
// @lc code=end
