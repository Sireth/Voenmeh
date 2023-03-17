#include "LapsangSouchongTea.h"

#include <utility>

LapsangSouchongTea::LapsangSouchongTea() = default;

LapsangSouchongTea::LapsangSouchongTea(string producerCountry, double bergamotContent, string manufactureDate,
                                       double volume) : ITea(std::move(producerCountry), bergamotContent,
                                                             std::move(manufactureDate),
                                                             volume) {

}

void LapsangSouchongTea::brew() {
    cout << "Brewing Lapsang Souchong tea" << endl;
}

void LapsangSouchongTea::drink() {
    cout << "Drinking Lapsang Souchong tea" << endl;
}

void LapsangSouchongTea::brewWithMilk() {
    cout << "Brewing Lapsang Souchong tea with milk" << endl;
}

void LapsangSouchongTea::microwave() {
    cout << "Microwaving Lapsang Souchong tea" << endl;
}


void LapsangSouchongTea::displayInfo() {
    cout << "Lapsang Souchong Tea: " << endl;
    ITea::displayInfo();
}
