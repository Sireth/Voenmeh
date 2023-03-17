#include "cstring"
#include "Person.h"

Person::Person(const wchar_t *surname, char math, char rus, char en, wchar_t sex) {
    wcscpy(this->surname, surname);
    this->math = math;
    this->rus = rus;
    this->en = en;
    this->sex = Sex(sex);
}

Person::Person() : Person(L"-New-", 0, 0, 0, 1) {}

char Person::comparison(int index, Person *left, Person *right) {
    switch (index) {
        case 0: {
            return ::wcscmp(left->surname, right->surname);
        }
        case 1: {
            char tempData = right->math;
            if (left->math < tempData) return -1;
            else if (left->math > tempData) return 1;
            return 0;
        }
        case 2: {
            char tempData = right->rus;
            if (left->rus < tempData) return -1;
            else if (left->rus > tempData) return 1;
            return 0;
        }
        case 3: {
            char tempData = right->en;
            if (left->en < tempData) return -1;
            else if (left->en > tempData) return 1;
            return 0;
        }
        case 4: {
            int l, r;
            wchar_t lw = left->sex.str, rw = right->sex.str;

            if(left->sex.digit == 1)
                l = 1;
            else if(left->sex.digit == 0)
                l = 0;
            else if (wcschr(L"МмMm", lw) != nullptr)
                l = 1;
            else
                l = 0;


            if(right->sex.digit == 1)
                r = 1;
            else if(right->sex.digit == 0)
                r = 0;
            else if (wcschr(L"МмMm", rw) != nullptr)
                r = 1;
            else
                r = 0;

            if (l < r) return -1;
            if (l > r) return 1;
            return 0;
        }
        default: {
            return 0;
        }
    }
}

void Person::get(wchar_t *dest, int index, Person *element) {
    switch (index) {
        case 0: {
            ::wcsncpy(dest, element->surname, 20);
            break;
        }
        case 1: {
            ::swprintf(dest, 4, L"%d", element->math);
            break;
        }
        case 2: {
            ::swprintf(dest, 4, L"%d", element->rus);
            break;
        }
        case 3: {
            ::swprintf(dest, 4, L"%d", element->en);
            break;
        }
        case 4: {
            if (element->sex.digit == 0 || element->sex.digit == 1) {
                ::swprintf(dest, 2, L"%d", element->sex.digit);
            } else {
                ::swprintf(dest, 2, L"%lc", element->sex.str);
            }
            break;
        }
        default: {
            return;
        }
    }
}

void Person::set(wchar_t *str, int index, Person *element) {
    switch (index) {
        case 0: {
            ::wcsncpy(element->surname, str, 20);
            break;
        }
        case 1: {
            element->math = wcstol(str, nullptr, 10);
            break;
        }
        case 2: {
            element->rus = wcstol(str, nullptr, 10);
            break;
        }
        case 3: {
            element->en = wcstol(str, nullptr, 10);
            break;
        }
        case 4: {
            element->sex = str[0];
            break;
        }
        default: {
            return;
        }
    }
}


