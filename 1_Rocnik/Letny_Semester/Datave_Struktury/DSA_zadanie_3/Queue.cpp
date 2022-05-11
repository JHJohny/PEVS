
#include "Queue.h"

template<typename T>
Queue<T>::Queue() {
    head = nullptr;
    tail = nullptr;
    size = 0;
    totalBought = 0;
}

template<typename T>
Queue<T>::Queue(Queue<InventoryRecord> *pQueue) {
    this->head = pQueue->head;
    this->tail = pQueue->tail;
    this->size = pQueue->size;
};

template<typename T>
void Queue<T>::Push(T* data) {
    Node<InventoryRecord> newNode = new Node<T>(data);

    if (this->getTail() == nullptr) {   // When que is empty
        this->setHead(newNode);
        this->setTail(newNode);
    } else {                            // When que is not empty
        this->getTail()->setNext(newNode);
        this->setTail(this->getTail()->getNext());
    }

    this->setSize(this->getSize() + 1);
}

template<typename T>
T *Queue<T>::Pop() {
    if (tail == nullptr) {
        return nullptr;
    }

    Node<T> *help = head;
    T* ans = head->getData();
    head = head->getNext();
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
