#ifndef LISTINTERFACE_H_
#define LISTINTERFACE_H_

#include <iostream>
#include "Node.h"
using namespace std;

template<class T>
class ListInterface{
    public:
    virtual bool isEmpty() const = 0;
    virtual int getLength() const = 0;
    virtual T insert(int index, T & item) = 0;
    virtual bool remove(int index) = 0;
    virtual void clear() = 0;
    virtual T replace(int index, T & item) = 0;

};


#endif