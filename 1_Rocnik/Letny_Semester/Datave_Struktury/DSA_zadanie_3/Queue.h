
#ifndef DATASTRUCTURES_ZADANIE_3_QUEUE_H
#define DATASTRUCTURES_ZADANIE_3_QUEUE_H


#include "Node.h"

template<typename T>
class Queue {
private:
    Node<T> *head;
    Node<T> *tail;
    int size;
    int totalBought;
public:
    Queue();
    Queue(Queue<T> *pQueue); // Copy constructor

    void Enqueue(T *data);
    T *Dequeue();

    // Getters and setters
    int GetTotalBought() const;

    void SetTotalBought(int totalBought);

    int GetSize() const;

    void SetSize(int size);

    Node<T> *GetHead() const;

    void SetHead(Node<T> *head);

    Node<T> *GetTail() const;

    void SetTail(Node<T> *tail);
};


#endif