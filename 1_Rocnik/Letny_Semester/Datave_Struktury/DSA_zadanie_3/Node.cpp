
#include "Node.h"

template<typename T>
Node<T> *Node<T>::GetNext() const {
    return next;
}

template<typename T>
void Node<T>::SetNext(Node<T> *next) {
    Node::next = next;
}

template<typename T>
Node<T>::Node(T *data):data(data) {
    this->data = data;
    next = nullptr;
}

template<typename T>
T *Node<T>::GetData() const {
    return data;
}

template<typename T>
void Node<T>::SetData(T *data) {
    Node::data = data;
}

template
class Node<InventoryRecord>;