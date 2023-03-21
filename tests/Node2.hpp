#ifndef TERM_2_NODE2_HPP
#define TERM_2_NODE2_HPP

#include "Node1.hpp"

template<typename T>
struct Node2 {
    Node<T> *data = nullptr;

    void push(T data);

    T *getDataAddress();

    T getData(T *node);

    T get();
};

template<typename T>
void Node2<T>::push(T data){
    this->data = new Node<T>(data);
}

template<typename T>
T *Node2<T>::getDataAddress() {
    return &(data->next->data);
}

template<typename T>
T Node2<T>::getData(T *node) {
    return *node;
}

template<typename T>
T Node2<T>::get() {
    return getData(getDataAddress());
}


#endif //TERM_2_NODE2_HPP
