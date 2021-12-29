/*
 * @lc app=leetcode.cn id=718 lang=cpp
 *
 * [718] 最长重复子数组
 */

#include <vector>
using namespace std;

// @lc code=start
class Solution
{
public:
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        int N1 = nums1.size(), N2 = nums2.size(), maxlen = 0;
        vector<vector<int>> Length(N1, std::vector<int>(N2, 0));
        for (int i = 0; i < N1; i++)
        {
            for (int j = 0; j < N2; j++)
            {
                if (i > 0 && j > 0 && Length[i - 1][j - 1] > 0)
                    Length[i][j] = nums1[i] == nums2[j] ? Length[i - 1][j - 1] + 1 : 0;
                else if (nums1[i] == nums2[j])
                    Length[i][j] = 1;
                if (Length[i][j] > maxlen)
                    maxlen = Length[i][j];
            }
        }
        return maxlen;
    }
};
// @lc code=end
