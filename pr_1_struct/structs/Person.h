#ifndef TERM_2_PERSON_H
#define TERM_2_PERSON_H

#include "../unions/Sex.h"
#include "iostream"
#include <variant>



struct Person {
    wchar_t surname[20]{};
    char math;
    char rus;
    char en;
    Sex sex;


    Person(const wchar_t *surname, char math, char rus, char en, wchar_t sex);

    Person();

    static char comparison(int index, Person *left, Person *right);

    static void get(wchar_t *dest, int index, Person *element);

    static void set(wchar_t *str, int index, Person *element);
};




#endif //TERM_2_PERSON_H
