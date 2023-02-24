#include "Triangle.h"
#include "iostream"
#include <cmath>
#include "funcs.h"


using namespace std;


Triangle::Triangle() {
    this->a = 3;
    this->b = 4;
    this->c = 5;
#ifdef DEBUG
    cout << "DEBUG(Triangle): " << "Length of all sides: " << a << ", " << b << ", " << c << endl;
#endif
}

Triangle::Triangle(double a, double b, double c) {
    if (a + b > c && a + c > b && b + c > a && (a > 0 && b > 0 && c > 0)) {
        this->a = a;
        this->b = b;
        this->c = c;
#ifdef DEBUG
        cout << "DEBUG(Triangle): " << "Length of all sides: " << a << ", " << b << ", " << c << endl;
#endif
    } else {
        throw invalid_argument("It is not possible to create a triangle with these parameters!");
    }
}

Triangle::~Triangle() {

}

Triangle::Triangle(const Triangle &triangle) {
    this->a = triangle.a;
    this->b = triangle.b;
    this->c = triangle.c;
#ifdef DEBUG
    cout << "DEBUG(Triangle): " << "Length of all sides: " << a << ", " << b << ", " << c << endl;
#endif
}

double Triangle::getSmallestAngle() const {
    double s;
    if ((a < b) && (a < c)) {
        s = (b * b + c * c - a * a) / (2 * b * c);
    } else if ((b < a) && (b < c)) {
        s = (a * a + c * c - b * b) / (2 * a * c);
    } else {
        s = (a * a + b * b - c * c) / (2 * a * b);
    }
#ifdef DEBUG
    cout << "DEBUG(getSmallestAngle): " << "Smallest angle: " << acos(s) << endl;
#endif
    return acos(s);
}

double *Triangle::getSides() {
#ifdef DEBUG
    cout << "DEBUG(getSides): " << "Length of all sides: " << a << ", " << b << ", " << c << endl;
#endif
    return new double[3]{a, b, c};
}

double *Triangle::getAngleBisectors() const {
    auto *bisectors = new double[3];
    bisectors[0] = (1 / (a + b) * pow(a * b * (a + b + c) * (a + b - c), 0.5));
    bisectors[1] = (1 / (a + c) * pow(a * c * (a + c + b) * (a + c - b), 0.5));
    bisectors[2] = (1 / (b + c) * pow(b * c * (b + c + a) * (b + c - a), 0.5));
#ifdef DEBUG
    cout << "DEBUG: " << "Length of all bisectors: " << bisectors[0] << ", " << bisectors[1] << ", " << bisectors[2] << endl;
#endif
    return bisectors;
}

double Triangle::getPerimeter() const {
#ifdef DEBUG
    cout << "DEBUG(getPerimeter): " << "Perimeter: " << (a + b + c) << endl;
#endif
    return a + b + c;
}

void Triangle::outputSides() const {
#ifdef DEBUG
    cout << "DEBUG(outputSides): " << "Length of all sides: " << a << ", " << b << ", " << c << endl;
#endif
    cout << "Length of all sides: " << a << ", " << b << ", " << c << endl;
}

void Triangle::setSides(double s1, double s2, double s3) {
    if (s1 + s2 > s3 && s1 + s3 > s2 && s2 + s3 > s1 && (s1 > 0 && s2 > 0 && s3 > 0)) {
        this->a = s1;
        this->b = s2;
        this->c = s3;
#ifdef DEBUG
        cout << "DEBUG(Triangle): " << "Length of all sides: " << s1 << ", " << s2 << ", " << s3 << endl;
#endif
    } else {
        throw invalid_argument("It is not possible to create s1 triangle with these parameters!");
    }
}

void Triangle::inputSides() {
    double s1, s2, s3;

    cout << "Enter the lengths of the sides of the triangle" << endl;
    cout << "Enter the length of side 1: ";
    s1 = readDouble();
    cout << "Enter the length of side 2: ";
    s2 = readDouble();
    cout << "Enter the length of side 3: ";
    s3 = readDouble();
    if (s1 + s2 > s3 && s1 + s3 > s2 && s2 + s3 > s1 && (s1 > 0 && s2 > 0 && s3 > 0)) {
        this->a = s1;
        this->b = s2;
        this->c = s3;
#ifdef DEBUG
        cout << "DEBUG(inputSides): " << "Length of all sides: " << a << ", " << b << ", " << c << endl;
#endif
    } else {
        throw invalid_argument("It is not possible to create a triangle with these parameters!");
    }
}

Triangle operator*=(Triangle &input, double x) {
    if (x <= 0) {
        throw std::invalid_argument("It is impossible to multiply the sides by a number less than or equal to zero");
    }
    input.a *= x;
    input.b *= x;
    input.c *= x;
#ifdef DEBUG
    cout << "DEBUG(operator*=): " << "New length of all sides: " << input.a << ", " << input.b << ", " << input.c << endl;
#endif
    return input;
}








