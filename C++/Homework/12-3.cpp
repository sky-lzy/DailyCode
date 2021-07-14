#include <iostream>
using namespace std;

class SNode
{
public:
    SNode(int value);
    ~SNode();
    int m_value;
    SNode *m_next;
};

SNode::SNode(int value) : m_value(value), m_next(NULL) {}

SNode::~SNode() {}

template <class Type>
class TList
{
protected:
    SNode *m_head;

public:
    TList();
    ~TList();
    virtual bool Insert(Type value);
    bool Delete(Type value);
    bool Contain(Type value);
    void print();
};

template <class Type>
TList<Type>::TList() : m_head(NULL) {}

template <class Type>
TList<Type>::~TList()
{
    SNode *p = m_head;
    while (p != NULL)
    {
        m_head = p->m_next;
        delete p;
        p = m_head;
    }
}

template <class Type>
bool TList<Type>::Insert(Type value)
{
    SNode *pTemp = new SNode(value);
    if (pTemp == NULL)
        return false;
    pTemp->m_next = m_head;
    m_head = pTemp;
    return true;
}

template <class Type>
bool TList<Type>::Delete(Type value)
{
    SNode *p1;
    bool flag = false;
    if (m_head->m_value == value)
    {
        p1 = m_head->m_next;
        delete m_head;
        m_head = p1;
        flag = true;
    }
    for (p1 = m_head; p1 != NULL && p1->m_next != NULL; p1 = p1->m_next)
        if (p1->m_next->m_value == value)
        {
            SNode *p2 = p1->m_next->m_next;
            delete p1->m_next;
            p1->m_next = p2;
            flag = true;
        }
    return flag;
}

template <class Type>
bool TList<Type>::Contain(Type value)
{
    bool flag = false;
    for (SNode *p = m_head; p != NULL; p = p->m_next)
        if (p->m_value == value)
            flag = true;
    return flag;
}

template <class Type>
void TList<Type>::print()
{
    cout << "结点的值依次为：" << endl;
    for (SNode *p = m_head; p != NULL; p = p->m_next)
        cout << p->m_value << " ";
    cout << endl;
}

class TSet : public TList<int>
{
public:
    bool Insert(int value);
    bool Insert(int n, int value);
};

bool TSet::Insert(int value)
{
    if (!(Contain(value)) && TList<int>::Insert(value))
        return true;
    else
        return false;
}

bool TSet::Insert(int n, int value)
{
    SNode *p1 = m_head;
    for (int i = 0; i < n - 1; i++)
        p1 = p1->m_next;
    SNode *p2 = new SNode(value);
    if (p2 == NULL)
        return false;
    p2->m_next = p1->m_next;
    p1->m_next = p2;
    return true;
}

int main()
{
    TList<int> sintList;
    sintList.Insert(12);
    sintList.Insert(24);
    sintList.Insert(48);
    sintList.Insert(24);
    sintList.Insert(96);
    sintList.Insert(48);
    sintList.print();

    sintList.Delete(48);
    sintList.print();

    TSet sintSet;
    sintSet.Insert(12);
    sintSet.Insert(24);
    sintSet.Insert(48);
    sintSet.Insert(24);
    sintSet.Insert(96);
    sintSet.Insert(48);
    sintSet.print();

    sintSet.Insert(2, 44);
    sintSet.print();
    return 0;
}