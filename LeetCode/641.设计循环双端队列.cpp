/*
 * @lc app=leetcode.cn id=641 lang=cpp
 *
 * [641] 设计循环双端队列
 */

// @lc code=start
class MyCircularDeque
{
private:
    int *data;
    int size;
    int num;
    int head;
    int end;

public:
    MyCircularDeque(int k) : size(k), num(0), head(0), end(0) { data = new int[k]; }

    bool insertFront(int value)
    {
        if (isFull())
            return false;
        data[head] = value;
        head = (head + 1) % size;
        num++;
        return true;
    }

    bool insertLast(int value)
    {
        if (isFull())
            return false;
        end = (end + size - 1) % size;
        data[end] = value;
        num++;
        return true;
    }

    bool deleteFront()
    {
        if (isEmpty())
            return false;
        head = (head + size - 1) % size;
        num--;
        return true;
    }

    bool deleteLast()
    {
        if (isEmpty())
            return false;
        end = (end + 1) % size;
        num--;
        return true;
    }

    int getFront()
    {
        if (isEmpty())
            return -1;
        return data[(head + size - 1) % size];
    }

    int getRear()
    {
        if (isEmpty())
            return -1;
        return data[end];
    }

    bool isEmpty() { return num == 0; }

    bool isFull() { return num == size; }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
// @lc code=end
