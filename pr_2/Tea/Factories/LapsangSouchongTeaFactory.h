#ifndef TERM_2_LAPSANGSOUCHONGTEAFACTORY_H
#define TERM_2_LAPSANGSOUCHONGTEAFACTORY_H


#include "Interfaces/ITeaFactory.h"

class LapsangSouchongTeaFactory: public ITeaFactory{
public:
    ITea *createTea() override;

    ITea *createTea(string producerCountry, double bergamotContent, string manufactureDate, double volume) override;
};


#endif //TERM_2_LAPSANGSOUCHONGTEAFACTORY_H
