#ifndef TERM_2_STACKLINKEDFACTORY_H
#define TERM_2_STACKLINKEDFACTORY_H

#include "../interfaces/IStackFactory.h"
#include "../StackLinked.h"

template<typename T>
class StackLinkedFactory : public IStackFactory<T> {
public:
    ~StackLinkedFactory() override = default;
    IStack<T> *createStack(long size) override;
};

template<typename T>
IStack<T> *StackLinkedFactory<T>::createStack(long size) {
    return new StackLinked<T>(size);
}


#endif //TERM_2_STACKLINKEDFACTORY_H
