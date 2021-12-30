/*
 * @lc app=leetcode.cn id=622 lang=cpp
 *
 * [622] 设计循环队列
 */

// @lc code=start
class MyCircularQueue
{
private:
    int *data;
    int size;
    int head;
    int end;
    int num;

public:
    MyCircularQueue(int k) : size(k), head(0), end(0), num(0) { data = new int[k]; }

    bool enQueue(int value)
    {
        if (num == size) return false;
        end = (end + size - 1) % size;
        data[end] = value;
        num++;
        return true;
    }

    bool deQueue()
    {
        if (num == 0) return false;
        head = (head + size - 1) % size;
        num--;
        return true;
    }

    int Front()
    {
        if (num)
            return data[(head + size - 1) % size];
        else
            return -1;
    }

    int Rear()
    {
        if (num)
            return data[end];
        else
            return -1;
    }

    bool isEmpty() { return num == 0; }

    bool isFull() { return num == size; }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
// @lc code=end
