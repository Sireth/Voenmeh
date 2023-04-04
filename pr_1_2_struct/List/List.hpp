#ifndef TERM_2_LIST_HPP
#define TERM_2_LIST_HPP

#include <cstddef>

template<typename T>
class List {
private:
    struct Node {
        T m_data;
        Node* m_next;
        Node* m_prev;

        Node(const T& data) : m_data(data), m_next(nullptr), m_prev(nullptr) {}
    };

    Node* m_head;
    Node* m_tail;
    size_t m_size;

public:
    List() : m_head(nullptr), m_tail(nullptr), m_size(0) {}

    ~List();

    List(const List& other);

    List& operator=(const List& other);

    void push_back(const T& data);

    void push_front(const T& data);

    void pop_back();

    void pop_front();

    [[nodiscard]] size_t getSize() const;

    [[nodiscard]] bool empty() const;

    void clear();

    class Iterator {
    private:
        Node* current;

    public:
        explicit Iterator(Node* node) : current(node) {}

        Iterator& operator++();

        const Iterator operator++(int);

        Iterator& operator--();

        const Iterator operator--(int);

        T& operator*() const;

        bool operator==(const Iterator& other) const;

        bool operator!=(const Iterator& other) const;
    };

    Iterator begin() const;

    Iterator end() const;
};

template<typename T>
typename List<T>::Iterator &List<T>::Iterator::operator++() {
    current = current->m_next;
    return *this;
}

template<typename T>
const typename List<T>::Iterator List<T>::Iterator::operator++(int) {
    Iterator temp(current);
    current = current->m_next;
    return temp;
}

template<typename T>
const typename List<T>::Iterator List<T>::Iterator::operator--(int) {
    Iterator temp(current);
    current = current->m_prev;
    return temp;
}

template<typename T>
T &List<T>::Iterator::operator*() const {
    return current->m_data;
}

template<typename T>
bool List<T>::Iterator::operator==(const List::Iterator &other) const {
    return current == other.current;
}

template<typename T>
bool List<T>::Iterator::operator!=(const List::Iterator &other) const {
    return !(this->operator==(other));
}

template<typename T>
typename List<T>::Iterator &List<T>::Iterator::operator--() {
    current = current->m_prev;
    return *this;
}

template<typename T>
List<T>::~List() {
    while (m_head) {
        Node* temp = m_head;
        m_head = m_head->m_next;
        delete temp;
    }
    m_tail = nullptr;
    m_size = 0;
}

template<typename T>
List<T>::List(const List &other) : m_head(nullptr), m_tail(nullptr), m_size(0) {
    for (auto it = other.begin(); it != other.end(); ++it) {
        push_back(*it);
    }
}

template<typename T>
List<T> &List<T>::operator=(const List &other) {
    if (&other == this) {
        return *this;
    }

    clear();
    for (auto it = other.begin(); it != other.end(); ++it) {
        push_back(*it);
    }

    return *this;
}

template<typename T>
void List<T>::push_back(const T &data) {
    Node* newNode = new Node(data);
    if (m_tail == nullptr) {
        m_head = newNode;
        m_tail = newNode;
    }
    else {
        m_tail->m_next = newNode;
        newNode->m_prev = m_tail;
        m_tail = newNode;
    }
    ++m_size;
}

template<typename T>
void List<T>::push_front(const T &data) {
    Node* newNode = new Node(data);
    if (m_head == nullptr) {
        m_head = newNode;
        m_tail = newNode;
    }
    else {
        m_head->m_prev = newNode;
        newNode->m_next = m_head;
        m_head = newNode;
    }
    ++m_size;
}

template<typename T>
void List<T>::pop_back() {
    if (m_tail == nullptr) {
        return;
    }

    Node* temp = m_tail;
    m_tail = m_tail->m_prev;
    if (m_tail != nullptr) {
        m_tail->m_next = nullptr;
    }
    else {
        m_head = nullptr;
    }
    delete temp;
    --m_size;
}

template<typename T>
void List<T>::pop_front() {
    if (m_head == nullptr) {
        return;
    }

    Node* temp = m_head;
    m_head = m_head->m_next;
    if (m_head != nullptr) {
        m_head->m_prev = nullptr;
    }
    else {
        m_tail = nullptr;
    }
    delete temp;
    --m_size;
}

template<typename T>
size_t List<T>::getSize() const {
    return m_size;
}

template<typename T>
bool List<T>::empty() const {
    return m_size == 0;
}

template<typename T>
void List<T>::clear() {
    while (m_head) {
        Node* temp = m_head;
        m_head = m_head->m_next;
        delete temp;
    }
    m_tail = nullptr;
    m_size = 0;
}

template<typename T>
typename List<T>::Iterator List<T>::begin() const {
    return Iterator(m_head);
}

template<typename T>
typename List<T>::Iterator List<T>::end() const {
    return Iterator(nullptr);
}


#endif //TERM_2_LIST_HPP
