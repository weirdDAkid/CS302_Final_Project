#ifndef NODE_CPP_
#define NODE_CPP_

#include "Node.h"
#include <iostream>
using namespace std;
template <class T>
Node<T>::Node():next(nullptr){

}
template <class T>
Node<T>::Node(T Data): data(Data), next(nullptr){

}
template <class T>
Node<T>::Node(T Data, Node<T>* Point): data(Data), next(Point){

}
template <class T>
Node<T>::Node(const Node<T> & other):data(other->data), next(other->next){

}
template <class T>
void Node<T>::setData(T & Data){
    data = Data;
}
template <class T>
void Node<T>::setNext(Node<T> * Point){
    next = Point;
}
template <class T>
T Node<T>::getData(){
    return data;
}
template <class T>
Node<T>* Node<T>::getNext()const{
    return next;
}

#endif