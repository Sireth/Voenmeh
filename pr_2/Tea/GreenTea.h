#ifndef TERM_2_GREENTEA_H
#define TERM_2_GREENTEA_H


#include "Interfaces/ITea.h"

class GreenTea: public ITea{
public:
    GreenTea();

    GreenTea(string producerCountry, double bergamotContent, string manufactureDate, double volume);

    void brew() override;

    void drink() override;

    void brewWithMilk() override;

    void displayInfo() override;

    void microwave() override;

    static void addGinger();

    void special() override;
};


#endif //TERM_2_GREENTEA_H
