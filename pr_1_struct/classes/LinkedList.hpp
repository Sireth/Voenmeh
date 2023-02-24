#ifndef TERM_2_LINKEDLIST_HPP
#define TERM_2_LINKEDLIST_HPP

#include "Node.hpp"
#include "Data.hpp"


template<typename T>
class LinkedList {

private:
    Node<T> *head_, *tail_;
    int length_;

public:
    LinkedList();

    ~LinkedList();

    Node<T> *pushFront(Data<T> data);

    Node<T> *pushBack(Data<T> data);

    void popFront();

    void popBack();

    Node<T> *getAt(int index);

    Node<T> *insert(int index, Data<T> data);

    void erase(int index);

    int len();

    Node<T> *operator[](int index);
};

template<typename T>
LinkedList<T>::LinkedList() {
    this->length_ = 0;
    this->head_ = this->tail_ = nullptr;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    while (head_ != nullptr) {
        popFront();
    }
}

template<typename T>
Node<T> *LinkedList<T>::pushFront(Data<T> data) {
    auto *ptr = new Node<T>(data);
    ptr->next = this->head_;
    if (head_ != nullptr) {
        head_->prev = ptr;
    }
    if (tail_ == nullptr) {
        tail_ = ptr;
    }
    head_ = ptr;
    length_++;
    return ptr;
}

template<typename T>
Node<T> *LinkedList<T>::pushBack(Data<T> data) {
    auto *ptr = new Node<T>(data);
    ptr->prev = this->tail_;
    if (tail_ != nullptr) {
        tail_->next = ptr;
    }
    if (head_ == nullptr) {
        head_ = ptr;
    }
    tail_ = ptr;
    length_++;
    return ptr;
}

template<typename T>
void LinkedList<T>::popFront() {
    if (head_ == nullptr) return;

    Node<T> *ptr = head_->next;
    if (ptr != nullptr) {
        ptr->prev = nullptr;
    } else {
        tail_ = ptr;
    }
    length_--;
    delete head_;
    head_ = ptr;
}

template<typename T>
void LinkedList<T>::popBack() {
    if (tail_ == nullptr) return;

    Node<T> *ptr = tail_->prev;
    if (ptr != nullptr) {
        ptr->next = nullptr;
    } else {
        head_ = ptr;
    }
    length_--;
    delete tail_;
    tail_ = ptr;
}

template<typename T>
Node<T> *LinkedList<T>::getAt(int index) {
    Node<T> *ptr = head_;
    if (index == len()) return tail_;
    int i = 0;

    while (i != index) {
        if (ptr == nullptr) return ptr;
        ptr = ptr->next;
        i++;
    }

    return ptr;
}

template<typename T>
Node<T> *LinkedList<T>::insert(int index, Data<T> data) {
    Node<T> *right = getAt(index);
    if (right == nullptr) return pushBack(data);

    Node<T> *left = right->prev;
    if (left == nullptr) return pushFront(data);

    auto *ptr = new Node<T>(data);

    ptr->prev = left;
    ptr->next = right;
    left->next = ptr;
    right->prev = ptr;
    length_++;
    return ptr;
}

template<typename T>
Node<T> *LinkedList<T>::operator[](int index) {
    return getAt(index);
}

template<typename T>
void LinkedList<T>::erase(int index) {
    Node<T> *ptr = getAt(index);
    if (ptr == nullptr) return;

    if (ptr->prev == nullptr)
        popFront();
    else if (ptr->next == nullptr)
        popBack();
    else {
        Node<T> *left = ptr->prev;
        Node<T> *right = ptr->next;

        left->next = right;
        right->prev = left;
        length_--;
        delete ptr;
    }
}

template<typename T>
int LinkedList<T>::len() {
    return length_;
}


#endif //TERM_2_LINKEDLIST_HPP
