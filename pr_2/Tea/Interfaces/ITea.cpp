
#include "ITea.h"

ITea::ITea(string producerCountry, double bergamotContent, string manufactureDate, double volume) :
        _producerCountry(std::move(producerCountry)), _bergamotContent(bergamotContent),
        _manufactureDate(std::move(manufactureDate)),
        _volume(volume) {}

void ITea::displayInfo() {
    cout << "Producer Country: " << _producerCountry << endl;
    cout << "Bergamot Content: " << _bergamotContent << endl;
    cout << "Manufacture Date: " << _manufactureDate << endl;
    cout << "Volume: " << _volume << endl;
}
