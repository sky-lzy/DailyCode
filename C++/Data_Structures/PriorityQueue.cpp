#include <iostream>
#include <vector>

class Heap
{
private:
    int Num;
    std::vector<int> Data;

public:
    Heap() : Num(0), Data() {}
    Heap(int inputNum, int *inputData);
    void Insert(int input);
    int top() const;
    void pop();
    void printOrder();

private:
    void MaxHeap(int root);
    void BuildHeap();
};

Heap::Heap(int inputNum, int *inputData) : Num(inputNum), Data(inputNum)
{
    for (int i = 0; i < Num; i++)
        Data[i] = inputData[i];
    BuildHeap();
}

void Heap::Insert(int input)
{
    Data.emplace_back(input);
    Num++;
    for (int i = (Num - 2) / 2; i >= 0; i--)
        MaxHeap(i);
}

int Heap::top() const
{
    return Data[0];
}

void Heap::pop()
{
    std::swap(Data[0], Data[Num - 1]);
    Num--;
    Data.erase(Data.end() - 1);
    MaxHeap(0);
}

void Heap::printOrder()
{
    while (Num != 0)
    {
        std::cout << top() << " ";
        pop();
    }
    std::cout << "\n";
}

void Heap::MaxHeap(int root)
{
    if (root * 2 + 1 >= Num)
        return;

    int left = root * 2 + 1;
    int large = Data[left] > Data[root] ? left : root;
    if (root * 2 + 2 < Num)
    {
        int right = root * 2 + 2;
        large = Data[large] > Data[right] ? large : right;
    }

    if (large != root)
    {
        std::swap(Data[large], Data[root]);
        MaxHeap(large);
    }
}

void Heap::BuildHeap()
{
    for (int i = Num / 2; i >= 0; i--)
        MaxHeap(i);
}

int main()
{
    int a[10] = {3, 2, 6, 4, 9, 7, 0, 1, 5, 8};
    Heap heap(10, a);
    heap.Insert(666);
    heap.Insert(5);
    heap.pop();
    heap.printOrder();
    return 0;
}