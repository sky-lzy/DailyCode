/*
 * @lc app=leetcode.cn id=500 lang=cpp
 *
 * [500] 键盘行
 */

#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// @lc code=start
class Solution
{
public:
    vector<string> findWords(vector<string> &words)
    {
        vector<string> result;
        unordered_map<char, int> keyboard;
        for (char i = 'a'; i <= 'z'; i++)
        {
            switch (i)
            {
            case 'q':
            case 'w':
            case 'e':
            case 'r':
            case 't':
            case 'y':
            case 'u':
            case 'i':
            case 'o':
            case 'p':
                keyboard.insert(make_pair(i, 1));
                keyboard.insert(make_pair(i + 'A' - 'a', 1));
                break;

            case 'a':
            case 's':
            case 'd':
            case 'f':
            case 'g':
            case 'h':
            case 'j':
            case 'k':
            case 'l':
                keyboard.insert(make_pair(i, 2));
                keyboard.insert(make_pair(i + 'A' - 'a', 2));
                break;

            case 'z':
            case 'x':
            case 'c':
            case 'v':
            case 'b':
            case 'n':
            case 'm':
                keyboard.insert(make_pair(i, 3));
                keyboard.insert(make_pair(i + 'A' - 'a', 3));
            default:
                break;
            }
        }
        for (auto i : words)
        {
            int k = keyboard[i[0]];
            int s = i.size();
            bool flag = true;
            for (int j = 1; j < s && flag; j++)
                if (keyboard[i[j]] != k)
                    flag = false;
            if (flag)
                result.emplace_back(i);
        }
        return result;
    }
};
// @lc code=end
