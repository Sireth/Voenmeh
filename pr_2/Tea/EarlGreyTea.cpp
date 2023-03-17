#include "EarlGreyTea.h"

#include <utility>

EarlGreyTea::EarlGreyTea(): ITea() {

}

EarlGreyTea::EarlGreyTea(string producerCountry, double bergamotContent, string manufactureDate, double volume) : ITea(
        std::move(producerCountry), bergamotContent, std::move(manufactureDate), volume) {

}

void EarlGreyTea::brew() {
    cout << "Brewing Earl Grey tea" << endl;
}

void EarlGreyTea::brewWithMilk() {
    cout << "Brewing Earl Grey tea with milk" << endl;
}

void EarlGreyTea::microwave() {
    cout << "Microwaving Earl Grey tea" << endl;
    cout << "Adding a slice of lemon" << endl;
}

void EarlGreyTea::displayInfo() {
    cout << "Earl Grey Tea: " << endl;
    ITea::displayInfo();
}

void EarlGreyTea::drink() {
    cout << "Drinking Earl Grey tea" << endl;
}
