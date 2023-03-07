#include "cstring"
#include "Person.h"

Person::Person(const wchar_t *surname, char math, char rus, char en, wchar_t sex) {
    wcscpy(this->surname, surname);
    this->math = math;
    this->rus = rus;
    this->en = en;
    this->sex = Sex(sex);
}

void Person::get(wchar_t* dest, int index) {
    switch (index) {
        case 0: {
//            dest = new wchar_t [20];
            ::wcsncpy(dest, this->surname, 20);
            break;
        }
        case 1: {
//            dest = new wchar_t[4];
            ::swprintf(dest, 4, L"%d", this->math);
            break;
        }
        case 2: {
//            dest = new wchar_t[4];
            ::swprintf(dest, 4, L"%d", this->rus);
            break;
        }
        case 3: {
//            dest = new wchar_t[4];
            ::swprintf(dest, 4, L"%d", this->en);
            break;
        }
        case 4: {
//            dest = new wchar_t[2];
            if (this->sex.str == 0 || this->sex.str == 1) {
                ::swprintf(dest, 2, L"%d", this->sex.str);
            } else {
                ::swprintf(dest, 2, L"%lc", this->sex.str);
            }
            break;
        }
        default: {
            return;
        }
    }
}

void Person::set(const wchar_t *str, int index) {
    switch (index) {
        case 0: {
            ::wcsncpy(this->surname, str, sizeof(this->surname));
            break;
        }
        case 1: {
            this->math = wcstol(str, nullptr, 10);
            break;
        }
        case 2: {
            this->rus = wcstol(str, nullptr, 10);
            break;
        }
        case 3: {
            this->en = wcstol(str, nullptr, 10);
            break;
        }
        case 4: {
            this->sex = str[0];
            break;
        }
        default: {
            return;
        }
    }
}

Person::Person() : Person(L"qwerty", 89, 89, 89, 1) {}

int Person::comparison(int index, wchar_t *data) {
    switch (index) {
        case 0: {
            return ::wcscmp(surname, data);
        }
        case 1: {
            char tempData = wcstol(data, nullptr, 10);
            if (math < tempData) return -1;
            else if (math > tempData) return 1;
            return 0;
        }
        case 2: {
            char tempData = wcstol(data, nullptr, 10);
            if (rus < tempData) return -1;
            else if (rus > tempData) return 1;
            return 0;
        }
        case 3: {
            char tempData = wcstol(data, nullptr, 10);
            if (en < tempData) return -1;
            else if (en > tempData) return 1;
            return 0;
        }
        case 4: {
            char temp = sex.digit;
            if (sex.digit > 2) {
                if (wcschr(L"МмMm", data[0]) != nullptr) temp = 1;
                else temp = 0;
            }

            if (data[0] < 2) {
                if (temp < data[0]) return -1;
                else if (temp > data[0]) return 1;
                return 0;
            } else {
                char tempData;
                if (wcschr(L"МмMm", data[0]) != nullptr) tempData = 1;
                else tempData = 0;
                if (temp < tempData) return -1;
                else if (temp > tempData) return 1;
                return 0;
            }

        }
        default: {
            return 0;
        }
    }
}


