//
// Created by sireth on 18.03.2023.
//

#ifndef TERM_2_NODE1_HPP
#define TERM_2_NODE1_HPP

template <typename T>
struct Node {
    T data{};
    Node<T> *next;

    Node(T data): data(data){
        next = this;
    };


};


#endif //TERM_2_NODE1_HPP
