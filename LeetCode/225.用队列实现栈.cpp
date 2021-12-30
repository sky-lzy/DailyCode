/*
 * @lc app=leetcode.cn id=225 lang=cpp
 *
 * [225] 用队列实现栈
 */

#include <queue>
using namespace std;

// @lc code=start
class MyStack
{
private:
    queue<char> data;

public:
    MyStack() {}

    void push(int x)
    {
        char len = data.size();
        data.push(x);
        while (len--)
        {
            data.push(data.front());
            data.pop();
        }
    }

    int pop()
    {
        int t = data.front();
        data.pop();
        return t;
    }

    int top() { return data.front(); }

    bool empty() { return data.empty(); }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
// @lc code=end
