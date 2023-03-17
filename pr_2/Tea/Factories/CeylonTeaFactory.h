#ifndef TERM_2_CEYLONTEAFACTORY_H
#define TERM_2_CEYLONTEAFACTORY_H


#include "Interfaces/ITeaFactory.h"

class CeylonTeaFactory : public ITeaFactory {
public:
    ITea *createTea() override;

    ITea *createTea(string producerCountry, double bergamotContent, string manufactureDate, double volume) override;
};


#endif //TERM_2_CEYLONTEAFACTORY_H
