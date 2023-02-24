#include "cstring"
#include "Person.h"

Person::Person(const wchar_t *surname, char math, char rus, char en, wchar_t sex) {
    wcscpy(this->surname, surname);
    this->math = math;
    this->rus = rus;
    this->en = en;
    this->sex = Sex(sex);
}


wchar_t *Person::operator[](int index) {
    return get(index);
}

wchar_t *Person::get(int index) {
    switch (index) {
        case 0: {
            return this->surname;
        }
        case 1: {
            static wchar_t str[4];
            ::swprintf(str, 4, L"%d", this->math);

            return str;
        }
        case 2: {
            static wchar_t str[4];
            ::swprintf(str, 4, L"%d", this->rus);
            return str;
        }
        case 3: {
            static wchar_t str[4];
            ::swprintf(str, 4, L"%d", this->en);
            return str;
        }
        case 4: {
            static wchar_t str[2];
            if (this->sex.str == 0 || this->sex.str == 1) {
                ::swprintf(str,2, L"%d", this->sex.str);
            } else {
                ::swprintf(str,2, L"%lc", this->sex.str);
            }
            return str;
        }
        default: {
            return nullptr;
        }
    }
}

void Person::set(const wchar_t *str, int index) {
    switch (index) {
        case 0: {
            ::wcsncpy(this->surname, str, sizeof(this->surname));
        }
        case 1: {
            this->math = wcstol(str, nullptr,10);
        }
        case 2: {
            this->rus = wcstol(str, nullptr,10);
        }
        case 3: {
            this->en = wcstol(str, nullptr,10);
        }
        case 4: {
            this->sex = str[0];
        }
        default: {
            return;
        }
    }
}

Person::Person(): Person(L"qwerty", 89,89,89,1) { }


