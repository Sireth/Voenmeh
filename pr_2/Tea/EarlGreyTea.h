#ifndef TERM_2_EARLGREYTEA_H
#define TERM_2_EARLGREYTEA_H


#include "Interfaces/ITea.h"

class EarlGreyTea : public ITea{
public:
    EarlGreyTea();

    EarlGreyTea(string producerCountry, double bergamotContent, string manufactureDate, double volume);
    
    void brew() override;

    void brewWithMilk() override;

    void drink() override;

    void microwave() override;

    void displayInfo() override;

    static void addHoney();

    void special() override;
};


#endif //TERM_2_EARLGREYTEA_H
