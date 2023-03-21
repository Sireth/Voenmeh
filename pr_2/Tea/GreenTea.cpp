#include "GreenTea.h"

#include <utility>

GreenTea::GreenTea() : ITea() {

}

GreenTea::GreenTea(string producerCountry, double bergamotContent, string manufactureDate, double volume) : ITea(
        std::move(producerCountry), bergamotContent, std::move(manufactureDate), volume) {

}

void GreenTea::brew() {
    cout << "Brewing Green tea" << endl;
}

void GreenTea::drink() {
    cout << "Drinking Green tea" << endl;
}

void GreenTea::brewWithMilk() {
    cout << "Brewing Green tea with milk" << endl;
}

void GreenTea::microwave() {
    cout << "Microwaving Green tea" << endl;
}

void GreenTea::displayInfo() {
    cout << "Green Tea: " << endl;
    ITea::displayInfo();
}

void GreenTea::addGinger() {
    cout << "Adding ginger to your Green tea" << endl;
}

void GreenTea::special() {
    addGinger();
}

