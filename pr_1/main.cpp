#include "Triangle.h"
#include "iostream"
#include "funcs.h"

using namespace std;


int main() {
    int menu = 1;
    double s1, s2, s3;
    Triangle triangle = Triangle();

    while (true) {
        try {
            clear_screen();
            cout << "Enter the lengths of the sides of the triangle" << endl;
            cout << "Enter the length of side 1: ";
            s1 = readDouble();
            cout << "Enter the length of side 2: ";
            s2 = readDouble();
            cout << "Enter the length of side 3: ";
            s3 = readDouble();

            triangle = Triangle(s1, s2, s3);
            clear_screen();
        } catch (const invalid_argument &e) {
            clear_screen();
            cout << "It is not possible to create a triangle with sides: " << s1 << ", " << s2 << ", " << s3 << endl;
            wait_on_enter();
            continue;
        }

        break;
    }

    while (menu != 0) {
        double *sides = triangle.getSides();
        cout << "Length of all sides: " << sides[0] << ", " << sides[1] << ", " << sides[2] << endl;
        cout << "Select the menu item by writing a number:" << endl
             << "1. Get smallest angle" << endl
             << "2. Get sides" << endl
             << "3. Get angle bisectors" << endl
             << "4. Get perimeter" << endl
             << "5. Zooming in on the triangle" << endl
             << "6. Input sides" << endl
             << "0. Exit from program" << endl;

        menu = readInt();
        clear_screen();

        switch (menu) {
            case 1: {
                cout << "Smallest angle: " << triangle.getSmallestAngle() << endl;
                wait_on_enter();
                break;
            }
            case 2: {
                sides = triangle.getSides();
                cout << "Length of all sides: " << sides[0] << ", " << sides[1] << ", " << sides[2] << endl;
                wait_on_enter();
                break;
            }
            case 3: {
                double *bisectors = triangle.getAngleBisectors();
                cout << "Length of all bisectors: " << bisectors[0] << ", " << bisectors[1] << ", " << bisectors[2]
                     << endl;
                wait_on_enter();
                break;
            }
            case 4: {
                cout << "Perimeter: " << triangle.getPerimeter() << endl;
                wait_on_enter();
                break;
            }
            case 5: {
                double multiplier;
                try {
                    cout << "How many times to increase the sides of the triangle?" << endl;
                    cout << "Enter a value: ";
                    multiplier = readDouble();
                    triangle *= multiplier;
                    sides = triangle.getSides();
                    cout << "New length of all sides: " << sides[0] << ", " << sides[1] << ", "
                         << sides[2] << endl;
                    wait_on_enter();
                } catch (const invalid_argument &e) {
                    clear_screen();
                    cout << "It is impossible to multiply by " << multiplier << endl;
                    wait_on_enter();
                }
                break;
            }
            case 6:{
                while (true){
                    try{
                        triangle.inputSides();
                    }
                    catch (const invalid_argument &e) {
                        clear_screen();
                        cout << "It is not possible to create a triangle with these sides" << endl;
                        wait_on_enter();
                        continue;
                    }
                    break;
                }
                break;
            }
            case 0: {
                break;
            }
            default : {
                cout << "You have selected a non-existent menu item" << endl;
                wait_on_enter();
                break;
            }
        }
        clear_screen();
    }

    return 0;
}


