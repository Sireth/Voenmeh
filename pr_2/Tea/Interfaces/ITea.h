#ifndef TERM_2_ITEA_H
#define TERM_2_ITEA_H

#include <string>
#include <iostream>
#include <utility>

using namespace std;

class ITea {
protected:
    string _producerCountry;
    double _bergamotContent;
    string _manufactureDate;
    double _volume;
public:
    ITea() {}

    ITea(string producerCountry, double bergamotContent, string manufactureDate, double volume);

    virtual void brew() = 0;

    virtual void displayInfo();

    virtual void drink() = 0;

    virtual void brewWithMilk() = 0;

    virtual void microwave() = 0;

    virtual void special() = 0;

    virtual ~ITea() = default;
};


#endif //TERM_2_ITEA_H
