#ifndef TERM_2_ISTACK_HPP
#define TERM_2_ISTACK_HPP

#include <iterator>

template<typename T>
class IStack {
protected:
    long m_size = 0;
    long m_maxSize = 0;

public:
    explicit IStack(long size = 10);

    virtual ~IStack() = default;

    virtual void push(const T &value) = 0;

    virtual T pop() = 0;

    virtual T peek() = 0;

    bool isEmpty();

    bool isFull();

    long size();

    virtual void clear() = 0;
};

template<typename T>
IStack<T>::IStack(long size):m_maxSize(size) {}

template<typename T>
bool IStack<T>::isEmpty() {
    return m_size == 0;
}

template<typename T>
bool IStack<T>::isFull() {
    return m_size == m_maxSize;
}

template<typename T>
long IStack<T>::size() {
    return m_size;
}

#endif //TERM_2_ISTACK_HPP
