#include "linkedlist.h"

template<class T>
linkedlist<T>::linkedlist(const linkedlist<T> &aplist)
{
    deepCopy(aplist);
}

template<class T>
linkedlist<T>::~linkedlist()
{
    makeEmpty();
}