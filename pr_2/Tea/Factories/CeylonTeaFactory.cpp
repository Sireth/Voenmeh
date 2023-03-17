#include "CeylonTeaFactory.h"
#include "../CeylonTea.h"

ITea *CeylonTeaFactory::createTea() {
    return new CeylonTea();
}

ITea *
CeylonTeaFactory::createTea(string producerCountry, double bergamotContent, string manufactureDate, double volume) {
    return new CeylonTea(producerCountry, bergamotContent, manufactureDate, volume);
}
