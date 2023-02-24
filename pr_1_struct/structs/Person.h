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

    wchar_t *get(int index);

    void set(const wchar_t *str, int index);


    wchar_t *operator[] (int index);

};




#endif //TERM_2_PERSON_H
