
#include <iostream>

#include "Queue.h"

template<typename T>
Queue<T>::Queue() { // Contructor
    head = nullptr;
    tail = nullptr;
    size = 0;
    totalBought = 0;
}

template<typename T>
Queue<T>::Queue(Queue<T> *pQueue) { // Copy contructor
    this->head = pQueue->head;
    this->tail = pQueue->tail;
    this->size = pQueue->size;
    this->totalBought = pQueue->totalBought;
};

template<typename T>
void Queue<T>::Enqueue(T *data) {
    auto newNode = new Node<T>(data);
    if (this->GetTail() == nullptr) {
        this->SetHead(newNode);
        this->SetTail(newNode);
    } else {
        this->GetTail()->SetNext(newNode);
        this->SetTail(this->GetTail()->GetNext());
    }
    this->SetSize(this->GetSize() + 1);
}

template<typename T>
T *Queue<T>::Dequeue() {
    if (tail == nullptr) {
        return nullptr;
    }

    Node<T> *help = head;
    T* ans = head->GetData();
    head = head->GetNext();
    delete help;
    size--;
    if (size == 0) {
        head = nullptr;
        tail = nullptr;
    }
    return ans;
}

template<typename T>
Node<T> *Queue<T>::GetHead() const {
    return head;
}

template<typename T>
void Queue<T>::SetHead(Node<T> *head) {
    Queue::head = head;
}

template<typename T>
Node<T> *Queue<T>::GetTail() const {
    return tail;
}

template<typename T>
void Queue<T>::SetTail(Node<T> *tail) {
    Queue::tail = tail;
}

template<typename T>
int Queue<T>::GetSize() const {
    return size;
}

template<typename T>
void Queue<T>::SetSize(int size) {
    Queue::size = size;
}

template<typename T>
int Queue<T>::GetTotalBought() const {
    return totalBought;
}

template<typename T>
void Queue<T>::SetTotalBought(int totalBought) {
    Queue::totalBought = totalBought;
}

template
class Queue<InventoryRecord>;