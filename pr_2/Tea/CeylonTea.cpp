#include "CeylonTea.h"

#include <utility>

CeylonTea::CeylonTea(string producerCountry, double bergamotContent, string manufactureDate, double volume) : ITea(
        std::move(producerCountry), bergamotContent, std::move(manufactureDate), volume) {

}

CeylonTea::CeylonTea(): ITea() {

}

void CeylonTea::brew() {
    cout << "Brewing Ceylon tea" << endl;
}

void CeylonTea::drink() {
    cout << "Drinking Ceylon tea" << endl;
}

void CeylonTea::brewWithMilk() {
    cout << "Brewing Ceylon tea with milk" << endl;
}

void CeylonTea::microwave() {
    cout << "Microwaving Ceylon tea" << endl;
}

void CeylonTea::displayInfo() {
    cout << "Ceylon Tea: " << endl;
    ITea::displayInfo();
}
