
#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

template<typename T>
class Queue {
private:
    Node<T> *head;
    Node<T> *tail;
    int size;
    int totalBought;
public:
    Queue(); // Constructor
    Queue(Queue<InventoryRecord> *pQueue); // Copy constructor

    void Push(T* data);
    T *Pop();

    int GetSize() const;
    void SetSize(int size);

    Node<T> *GetHead() const;

    void SetHead(Node<T> *head);

    Node<T> *GetTail() const;

    void SetTail(Node<T> *tail);
};

#endif