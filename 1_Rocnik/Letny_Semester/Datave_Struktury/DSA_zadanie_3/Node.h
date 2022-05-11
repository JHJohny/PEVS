
#ifndef NODE_H
#define NODE_H

#include "InventoryRecord.h"

template<typename T>
class Node {

private:
    T* data;
    Node<T> *next;
public:
    Node(T *data);

    T *GetData() const;

    void SetData(T *data);

    Node<T> *GetNext() const;

    void SetNext(Node<T> *next);
};

#endif