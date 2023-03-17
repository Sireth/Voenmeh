#include <limits>
#include "iostream"
#include "funcs.h"

using namespace std;

void ignoreLine() {
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt() {
    while (true) {
        int x{};
        cin >> x;

        if (cin.fail()) {
            cin.clear();
            ignoreLine();
            cout << "Bad numeric string--try again\n";
        } else {
            ignoreLine();
            return x;
        }
    }
}

double readDouble() {
    while (true) {
        double x{};
        cin >> x;

        if (cin.fail()) {
            cin.clear();
            ignoreLine();
            cout << "Bad numeric string--try again\n";
        } else {
            ignoreLine();
            return x;
        }
    }
}

template<typename T>
T readT(){
    while (true) {
        T x{};
        cin >> x;

        if (cin.fail()) {
            cin.clear();
            ignoreLine();
            cout << "Bad numeric string--try again\n";
        } else {
            ignoreLine();
            return x;
        }
    }
}



void clear_screen() {
#ifdef DEBUG
#else
#ifdef __WIN32
    system("cls");
#elif defined(__linux)
    system("clear");
#endif
#endif
}

void wait_on_enter() {
#ifdef __WIN32
    system("pause");
#elif defined(__linux)
    std::string dummy;
    std::cout << "Enter to continue..." << std::endl;
    std::getline(std::cin, dummy);
#endif
}