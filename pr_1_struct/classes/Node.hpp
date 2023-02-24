#ifndef TERM_2_NODE_HPP
#define TERM_2_NODE_HPP

#include "Data.hpp"

template<typename T>
class Node {
public:
    Data<T> data;
    Node *prev;
    Node *next;

    explicit Node(Data<T> data);

    T getData();

    int editData(T data);

    int editData(T *data);
};


template<typename T>
Node<T>::Node(Data<T> data): data(data) {
    this->prev = this->next = nullptr;
}

template<typename T>
T Node<T>::getData() {
    return data.getData();
}

template<typename T>
int Node<T>::editData(T data) {
    return this->data.editData(data);
}

template<typename T>
int Node<T>::editData(T *data) {
    return this->data.editData(data);
}


#endif //TERM_2_NODE_HPP
