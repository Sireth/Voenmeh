#include <iostream>
#include "Node2.hpp"

int main(){
    Node2<int> *node2;

    node2->push(10);
    int *p =&(node2->data->next->data);
    std::cout << p << "\t" << *p << node2->get() <<std::endl;

    return 0;
}