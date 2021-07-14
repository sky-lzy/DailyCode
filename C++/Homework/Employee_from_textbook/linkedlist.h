#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <class T>
struct node
{
    T data;
    node<T> *next;
};

template <class T>
class linkedlist
{
private:
    node<T> *head;
    node<T> *current;
    inline void deepCopy(const linkedlist<T> &original);

public:
    linkedlist();
    linkedlist(const linkedlist &aplist);
    ~linkedlist();

    void insert(node<T> *newNode);
    void insert_end(node<T> *newNode);
    node<T> *getFirst() const;
    inline node<T> *getNext() const;
    bool find(const T &element) const;
    bool retrieve(T &element) const;
    bool replace(const T &newElement);
    bool remove(node<T> *node);
    void makeEmpty();
    linkedlist<T> &operator=(const linkedlist<T> &rlist);
};

#endif