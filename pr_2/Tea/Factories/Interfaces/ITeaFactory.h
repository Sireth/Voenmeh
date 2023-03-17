#ifndef TERM_2_ITEAFACTORY_H
#define TERM_2_ITEAFACTORY_H


#include "../../Interfaces/ITea.h"

class ITeaFactory {
public:
    virtual ITea *createTea() = 0;

    virtual ITea *createTea(string producerCountry, double bergamotContent, string manufactureDate, double volume) = 0;
};


#endif //TERM_2_ITEAFACTORY_H
