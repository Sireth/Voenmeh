#ifndef TERM_2_STACKVECTORFACTORY_H
#define TERM_2_STACKVECTORFACTORY_H

#include "../interfaces/IStackFactory.h"
#include "../StackVector.hpp"

template<typename T>
class StackVectorFactory : public IStackFactory<T>{
public:
    ~StackVectorFactory() override = default;
    IStack<T> *createStack(long size) override;
};

template<typename T>
IStack<T> *StackVectorFactory<T>::createStack(long size) {
    return new StackVector<T>(size);
}


#endif //TERM_2_STACKVECTORFACTORY_H
