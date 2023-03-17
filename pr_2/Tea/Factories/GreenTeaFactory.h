#ifndef TERM_2_GREENTEAFACTORY_H
#define TERM_2_GREENTEAFACTORY_H


#include "Interfaces/ITeaFactory.h"

class GreenTeaFactory: public ITeaFactory{
public:
    ITea *createTea(string producerCountry, double bergamotContent, string manufactureDate, double volume) override;
    ITea *createTea() override;
};


#endif //TERM_2_GREENTEAFACTORY_H
