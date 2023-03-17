#include "EarlGreyTeaFactory.h"
#include "../EarlGreyTea.h"

ITea *EarlGreyTeaFactory::createTea() {
    return new EarlGreyTea();
}

ITea *
EarlGreyTeaFactory::createTea(string producerCountry, double bergamotContent, string manufactureDate, double volume) {
    return new EarlGreyTea(producerCountry, bergamotContent, manufactureDate, volume);
}
