#ifndef TERM_2_CEYLONTEA_H
#define TERM_2_CEYLONTEA_H


#include "Interfaces/ITea.h"

class CeylonTea : public ITea {
public:
    CeylonTea();

    CeylonTea(string producerCountry, double bergamotContent, string manufactureDate, double volume);

    void brew() override;

    void drink() override;

    void brewWithMilk() override;

    void microwave() override;

    void displayInfo() override;
};


#endif //TERM_2_CEYLONTEA_H
