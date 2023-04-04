#ifndef TERM_2_ISTACKFACTORY_H
#define TERM_2_ISTACKFACTORY_H


#include "IStack.hpp"

template<typename T>
class IStackFactory {
public:
    virtual ~IStackFactory() = default;
    virtual IStack<T> *createStack(long size = 10) = 0;
};


#endif //TERM_2_ISTACKFACTORY_H
