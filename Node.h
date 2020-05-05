#ifndef NODE_H_
#define NODE_H_

#include <iostream>
using namespace std;

template <class T>
class Node{
    public:
    Node();
    Node(const T Data);
    Node(const T Data, Node<T>* Point);
    Node(const Node<T> & other);
    void setData(T & Data);
    void setNext(Node<T> * Point);
    T getData();
    Node<T>* getNext()const;

    private:
    T data;
    Node<T> * next;
};
#include "Node.cpp"
#endif