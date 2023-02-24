#include "cstring"
#include "Person.h"

Person::Person(const char *surname, char math, char rus, char en, char sex) {
    strcpy(this->surname, surname);
    this->math = math;
    this->rus = rus;
    this->en = en;
    this->sex = Sex(sex);
}


char *Person::operator[](int index) {
    return get(index);
}

char *Person::get(int index) {
    switch (index) {
        case 0: {
            return this->surname;
        }
        case 1: {
            static char str[4];
            sprintf(str, "%d", this->math);
            return str;
        }
        case 2: {
            static char str[4];
            sprintf(str, "%d", this->rus);
            return str;
        }
        case 3: {
            static char str[4];
            sprintf(str, "%d", this->en);
            return str;
        }
        case 4: {
            static char str[2];
            if (this->sex.str == 0 || this->sex.str == 1) {
                sprintf(str, "%d", this->sex.str);
            } else {
                sprintf(str, "%c", this->sex.str);
            }
            return str;
        }
        default: {
            return nullptr;
        }
    }
}

void Person::set(const char *str, int index) {
    switch (index) {
        case 0: {
            strncpy(this->surname, str, sizeof(this->surname));
        }
        case 1: {
            this->math = strtol(str, nullptr,10);
        }
        case 2: {
            this->rus = strtol(str, nullptr,10);
        }
        case 3: {
            this->en = strtol(str, nullptr,10);
        }
        case 4: {
            this->sex = str[0];
        }
        default: {
            return;
        }
    }
}


