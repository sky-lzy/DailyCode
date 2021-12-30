/*
 * @lc app=leetcode.cn id=1381 lang=cpp
 *
 * [1381] 设计一个支持增量操作的栈
 */

// @lc code=start
class CustomStack
{
private:
    int *data;
    int Size;
    int top;

public:
    CustomStack(int maxSize) : Size(maxSize), top(0) { data = new int[maxSize]; }

    void push(int x)
    {
        if (top < Size)
            data[top++] = x;
    }

    int pop()
    {
        if (top > 0)
            return data[--top];
        else
            return -1;
    }

    void increment(int k, int val)
    {
        for (int i = 0; i < k && i < top; i++)
            data[i] += val;
    }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */
// @lc code=end
