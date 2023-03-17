#include "LapsangSouchongTeaFactory.h"
#include "../LapsangSouchongTea.h"

ITea *LapsangSouchongTeaFactory::createTea() {
    return new LapsangSouchongTea();
}

ITea *LapsangSouchongTeaFactory::createTea(string producerCountry, double bergamotContent, string manufactureDate,
                                           double volume) {
    return new LapsangSouchongTea(producerCountry, bergamotContent, manufactureDate, volume);
}
