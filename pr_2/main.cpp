#include "Tea/Interfaces/ITea.h"
#include "Tea/Factories/Interfaces/ITeaFactory.h"

#include "Tea/Factories/CeylonTeaFactory.h"
#include "Tea/Factories/EarlGreyTeaFactory.h"
#include "Tea/Factories/GreenTeaFactory.h"
#include "Tea/Factories/LapsangSouchongTeaFactory.h"

#include "funcs.h"

#define SIZE 5

#define CEYLON_TEA 1
#define EARL_GREY_TEA 2
#define GREEN_TEA 3
#define LAPSANG_SOUCHONG_TEA 4

#define BREW_ACTION 1
#define DISPLAY_INFO_ACTION 2
#define DRINK_ACTION 3
#define BREW_WITH_MILK_ACTION 4
#define MICROWAVE_ACTION 5


#define EXIT_PROGRAM 999


static ITeaFactory *createTeaFactoryByName(const string &name);

static ITeaFactory *createTeaFactoryById(int id);

void selectMainMenu();

void createTea();

ITea *requestTeaParameters(ITeaFactory *factory);

void deleteTea();

void selectActionOnTea();

void exitProgram();

ITea *teas[SIZE];

int teasLength = 0;

int main() {
    selectMainMenu();
    return 0;
}

void selectMainMenu() {
    int c;

    do {
        clear_screen();
        cout << "Amount of tea: " << teasLength << endl << endl;
        cout << "1. Create new tea" << endl;
        cout << "2. Break a cup of tea" << endl;
        cout << "3. Select action on tea" << endl;
        cout << EXIT_PROGRAM << ". Exit" << endl << endl;
        cout << "Select your desired action: ";

        c = readInt();

        switch (c) {
            case 1: {
                return createTea();
            }
            case 2: {
                return deleteTea();
            }
            case 3: {
                return selectActionOnTea();
            }
            default: {
                break;
            }
        }
    } while (c != EXIT_PROGRAM);
}

void createTea() {
    int c;
    ITeaFactory *factory;
    clear_screen();

    if(teasLength == SIZE){
        cout << "The maximum number of cups of tea has been reached, break some!" << endl;
        wait_on_enter();
        return selectMainMenu();
    }

    cout << CEYLON_TEA << ". Ceylon tea" << endl;
    cout << EARL_GREY_TEA << ". Earl grey tea" << endl;
    cout << GREEN_TEA << ". Green tea" << endl;
    cout << LAPSANG_SOUCHONG_TEA << ". Lapsang souchong tea" << endl;
    cout << EXIT_PROGRAM << ". Back" << endl << endl;
    cout << "Select your desired tea: ";
    c = readInt();

    if (c == EXIT_PROGRAM) return selectMainMenu();
    try {
        factory = createTeaFactoryById(c);
    }
    catch (exception &ex) {
        cout << "This tea does not exist." << endl;
        wait_on_enter();
        return createTea();
    }

    if (teasLength != SIZE) {
        teas[teasLength] = requestTeaParameters(factory);
        teasLength++;
    }
    return selectMainMenu();
}

ITea *requestTeaParameters(ITeaFactory *factory) {
    string producerCountry, manufactureDate;
    double bergamotContent, volume;

    cout << endl << "Enter producer country: ";
    cin >> producerCountry;

    cout << "Enter bergamot content: ";
    bergamotContent = readDouble();

    cout << "Enter manufacture date: ";
    cin >> manufactureDate;

    cout << "Enter volume: ";
    volume = readDouble();

    return factory->createTea(producerCountry, bergamotContent, manufactureDate, volume);
}

void deleteTea() {
    clear_screen();
    int index;
    cout << "Enter the number of the tea cup to be broken or " << EXIT_PROGRAM << " to back: ";
    index = readInt();
    if (index == EXIT_PROGRAM) return selectMainMenu();
    if (index > teasLength) {
        cout << "This tea does not exist." << endl;
        wait_on_enter();
        return selectMainMenu();
    }
    teas[index-1] = nullptr;
    teasLength--;
    cout << "The tea mug was successfully broken" << endl;
    return selectMainMenu();
}

void selectActionOnTea() {
    clear_screen();
    int index, action;
    cout << "Enter the number of the teacup to be acted upon, or " << EXIT_PROGRAM << " to back: ";
    index = readInt();

    if (index == EXIT_PROGRAM) return selectMainMenu();
    if (index > teasLength) {
        cout << "This tea does not exist." << endl;
        wait_on_enter();
        return selectMainMenu();
    }
    index--;
    cout << BREW_ACTION << ". Brew" << endl;
    cout << DISPLAY_INFO_ACTION << ". Display info" << endl;
    cout << DRINK_ACTION << ". Drink" << endl;
    cout << BREW_WITH_MILK_ACTION << ". Brew with milk" << endl;
    cout << MICROWAVE_ACTION << ". Microwave" << endl;
    cout << "Choose the desired action: ";
    do {
        action = readInt();
        if (action <= MICROWAVE_ACTION) {
            break;
        }
        cout << "You entered the number of a non-existent action. Try again: ";
    } while (true);

    switch (action) {
        case BREW_ACTION: {
            teas[index]->brew();
            break;
        }
        case DISPLAY_INFO_ACTION: {
            teas[index]->displayInfo();
            break;
        }
        case DRINK_ACTION: {
            teas[index]->drink();
            break;
        }
        case BREW_WITH_MILK_ACTION: {
            teas[index]->brewWithMilk();
            break;
        }
        case MICROWAVE_ACTION: {
            teas[index]->microwave();
            break;
        }
        default: {
            break;
        }
    }
    wait_on_enter();
    return selectMainMenu();
}

void exitProgram() {
    for (int i = 0; i < SIZE; i++) {
        delete teas[i];
        teas[i] = nullptr;
    }
    exit(0);
}

static ITeaFactory *createTeaFactoryByName(const string &name) {
    if (name == "CeylonTea") {
        return new CeylonTeaFactory();
    } else if (name == "EarlGreyTea") {
        return new EarlGreyTeaFactory();
    } else if (name == "GreenTea") {
        return new GreenTeaFactory();
    } else if (name == "LapsangSouchongTea") {
        return new LapsangSouchongTeaFactory();
    } else {
        throw std::invalid_argument(name + "is unspecified type of tea");
    }
}

static ITeaFactory *createTeaFactoryById(int id) {
    switch (id) {
        case CEYLON_TEA: {
            return new CeylonTeaFactory();
            break;
        }
        case EARL_GREY_TEA: {
            return new EarlGreyTeaFactory();
            break;
        }
        case GREEN_TEA: {
            return new GreenTeaFactory();
            break;
        }
        case LAPSANG_SOUCHONG_TEA: {
            return new LapsangSouchongTeaFactory();
            break;
        }
        default:
            throw std::invalid_argument("Unspecified type of tea");
            break;
    }
}