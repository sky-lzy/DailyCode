/*
 * @lc app=leetcode.cn id=155 lang=cpp
 *
 * [155] 最小栈
 */

#include <stack>
using std::stack;

// @lc code=start
class MinStack
{
private:
    stack<int> data;
    stack<int> min;

public:
    MinStack() {}

    void push(int val)
    {
        data.push(val);
        if (!min.empty() && min.top() < val)
            min.push(min.top());
        else
            min.push(val);
    }

    void pop()
    {
        data.pop();
        min.pop();
    }

    int top() { return data.top(); }

    int getMin() { return min.top(); }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
// @lc code=end
