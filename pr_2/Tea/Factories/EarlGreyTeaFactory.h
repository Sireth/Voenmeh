#ifndef TERM_2_EARLGREYTEAFACTORY_H
#define TERM_2_EARLGREYTEAFACTORY_H


#include "Interfaces/ITeaFactory.h"

class EarlGreyTeaFactory: public ITeaFactory{
public:
    ITea *createTea() override;

    ITea *createTea(string producerCountry, double bergamotContent, string manufactureDate, double volume) override;
};


#endif //TERM_2_EARLGREYTEAFACTORY_H
