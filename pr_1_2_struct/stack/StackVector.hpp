#ifndef TERM_2_STACKVECTOR_HPP
#define TERM_2_STACKVECTOR_HPP

#include "interfaces/IStack.hpp"

template<typename T>
class StackVector : public IStack<T> {
private:
    T *m_vector;
public:

    explicit StackVector(long size = 10);

    ~StackVector() override;

    void push(const T &value) override;

    T pop() override;

    T peek() override;

    void clear() override;
};

template<typename T>
void StackVector<T>::push(const T &value) {
    if (this->isFull()) throw std::invalid_argument("Stack is full");
    this->m_vector[this->m_size] = value;
    this->m_size++;
}

template<typename T>
T StackVector<T>::pop() {
    if (this->isEmpty()) throw std::invalid_argument("Stack is empty");
    T temp = this->m_vector[this->m_size-1];
    this->m_size++;
    return temp;
}

template<typename T>
T StackVector<T>::peek() {
    return this->m_vector[this->m_size-1];
}

template<typename T>
void StackVector<T>::clear() {
    while (!this->isEmpty()) pop();
}

template<typename T>
StackVector<T>::StackVector(long size):IStack<T>::IStack(size) {
    this->m_vector = new T[size];
}

template<typename T>
StackVector<T>::~StackVector() {
    clear();
    delete[] this->m_vector;
}


#endif //TERM_2_STACKVECTOR_HPP
