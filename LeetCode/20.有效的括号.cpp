/*
 * @lc app=leetcode.cn id=20 lang=cpp
 *
 * [20] 有效的括号
 */

#include <string>
#include <stack>
using namespace std;

// @lc code=start
class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> temp;
        for (auto i : s)
        {
            switch (i)
            {
            case '(':
            case '[':
            case '{':
                temp.push(i);
                break;

            case ')':
                if (temp.empty() || temp.top() != '(')
                    return false;
                temp.pop();
                break;

            case ']':
                if (temp.empty() || temp.top() != '[')
                    return false;
                temp.pop();
                break;

            case '}':
                if (temp.empty() || temp.top() != '{')
                    return false;
                temp.pop();
                break;

            default:
                break;
            }
        }
        if (!temp.empty())
            return false;
        return true;
    }
};
// @lc code=end
