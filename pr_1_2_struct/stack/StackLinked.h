#ifndef TERM_2_STACKLINKED_H
#define TERM_2_STACKLINKED_H


#include "interfaces/IStack.hpp"
#include "NodeStack.hpp"

template<typename T>
class StackLinked : public IStack<T> {
private:
    NodeStack<T> *m_head = nullptr;
    NodeStack<T> *m_tail = nullptr;

public:

    explicit StackLinked(long size = 10);

    ~StackLinked() override;

    void push(const T &value) override;

    T pop() override;

    T peek() override;

    void clear() override;
};

template<typename T>
void StackLinked<T>::push(const T &value) {
    if (this->isFull()) throw std::out_of_range("StackLinked::push() Stack is full");
    auto *ptr = new NodeStack<T>(value);

    ptr->m_next = this->m_head;

    if (this->m_tail == nullptr) {
        this->m_tail = ptr;
    }

    this->m_head = ptr;
    this->m_size++;
}

template<typename T>
T StackLinked<T>::pop() {
    if (this->isEmpty()) throw std::out_of_range("StackLinked::pop() Stack is empty");
    NodeStack<T> *ptr = this->m_head->m_next;

    if (ptr == nullptr) {
        this->m_tail = ptr;
    }

    T temp = this->m_head->m_data;

    this->m_size--;

    delete this->m_head;
    this->m_head = ptr;

    return temp;
}

template<typename T>
T StackLinked<T>::peek() {
    return this->m_head->m_data;
}

template<typename T>
void StackLinked<T>::clear() {
    while (!this->isEmpty()) pop();
}

template<typename T>
StackLinked<T>::StackLinked(long size):IStack<T>::IStack(size) {}

template<typename T>
StackLinked<T>::~StackLinked() {
    clear();
}


#endif //TERM_2_STACKLINKED_H
