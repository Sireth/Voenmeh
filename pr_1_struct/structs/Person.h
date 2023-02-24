#ifndef TERM_2_PERSON_H
#define TERM_2_PERSON_H

#include "../unions/Sex.h"
#include "iostream"
#include <variant>



struct Person {
    char surname[20]{};
    char math;
    char rus;
    char en;
    Sex sex;


    Person(const char *surname, char math, char rus, char en, char sex);

    char *get(int index);

    void set(const char *str, int index);


    char *operator[] (int index);

};




#endif //TERM_2_PERSON_H
