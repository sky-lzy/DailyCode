/*
 * @lc app=leetcode.cn id=232 lang=cpp
 *
 * [232] 用栈实现队列
 */

#include <stack>
using namespace std;

// @lc code=start
class MyQueue
{
private:
    stack<char> data;

public:
    MyQueue() {}

    void push(int x)
    {
        stack<char> temp;
        while (!data.empty())
        {
            temp.push(data.top());
            data.pop();
        }
        data.push(x);
        while (!temp.empty())
        {
            data.push(temp.top());
            temp.pop();
        }
    }

    int pop()
    {
        char temp = data.top();
        data.pop();
        return temp;
    }

    int peek() { return data.top(); }

    bool empty() { return data.empty(); }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
// @lc code=end
