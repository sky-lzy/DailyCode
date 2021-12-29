/*
 * @lc app=leetcode.cn id=5 lang=cpp
 *
 * [5] 最长回文子串
 */

#include <string>
#include <vector>
using namespace std;

// @lc code=start
class Solution
{
public:
    string longestPalindrome(string s)
    {
        int len = s.size();
        vector<int> List(len, 1);
        for (int i = 1; i < len; i++)
        {
            if (i - 1 - List[i - 1] >= 0 && s[i] == s[i - 1 - List[i - 1]])
                List[i] = List[i - 1] + 2;
            else if (([&s, &List, i]() -> bool
                      {
                          int j = i - List[i - 1];
                          while (j < i)
                          {
                              if (s[j] != s[j + 1])
                                  return false;
                              j++;
                          }
                          return true;
                      })())
                List[i] = List[i - 1] + 1;
            else if (s[i] == s[i - 1])
                List[i] = 2;
        }

        int maxlen = 0, maxidx = 0;
        for (int i = 0; i < len; i++)
            if (List[i] > maxlen)
            {
                maxlen = List[i];
                maxidx = i;
            }

        string tem = "";
        for (int i = maxidx - maxlen + 1; i <= maxidx; i++)
            tem += s[i];
        return tem;
    }
};
// @lc code=end
