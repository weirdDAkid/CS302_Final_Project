#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include "Node.h"
#include "ListInterface.h"
using namespace std;

template <class T>
class List:public ListInterface<T>{
    private:
        Node<T> * head;
        Node<T> * tail;
        int itemCount;
    public:
        List();
        List(const List<T> & other);
        ~List();
        bool isEmpty() const;
        int getLength() const;
        T insert(const int index, T & item);
        bool remove(const int index);
        void clear();
        T getEntry(const int index);
        T replace(int index, T & item);
        int getPosition(const T item);

};


#include "List.cpp"
#endif
