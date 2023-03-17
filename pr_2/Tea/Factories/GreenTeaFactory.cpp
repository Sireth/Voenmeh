#include "GreenTeaFactory.h"
#include "../GreenTea.h"

ITea *GreenTeaFactory::createTea() {
    return new GreenTea();
}

ITea *
GreenTeaFactory::createTea(string producerCountry, double bergamotContent, string manufactureDate, double volume) {
    return new GreenTea(producerCountry, bergamotContent, manufactureDate, volume);
}
