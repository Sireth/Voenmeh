#ifndef TERM_2_LAPSANGSOUCHONGTEA_H
#define TERM_2_LAPSANGSOUCHONGTEA_H

#include "string"
#include "Interfaces/ITea.h"

using namespace std;

class LapsangSouchongTea : public ITea {
public:
    LapsangSouchongTea();

    LapsangSouchongTea(string producerCountry, double bergamotContent, string manufactureDate, double volume);

    void brew() override;

    void drink() override;

    void brewWithMilk() override;

    void microwave() override;

    void displayInfo() override;

    static void addCinnamon();

    void special() override;
};


#endif //TERM_2_LAPSANGSOUCHONGTEA_H
