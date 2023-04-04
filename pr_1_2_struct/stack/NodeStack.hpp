#ifndef TERM_2_NODESTACK_HPP
#define TERM_2_NODESTACK_HPP

template<typename T>
class NodeStack {
public:
    T m_data = nullptr;
    NodeStack *m_next = nullptr;

    NodeStack() = default;

    explicit NodeStack(const T &data);
};

template<typename T>
NodeStack<T>::NodeStack(const T &data): m_data(data) {}


#endif //TERM_2_NODESTACK_HPP
