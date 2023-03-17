#include "cstring"

#include "Sex.h"

Sex::Sex(wchar_t sex) {
    if (wcschr(L"МЖмжMFmf", sex) != nullptr) {
        this->str = sex;
    } else if (sex == L'0' || sex == L'1') {
        this->digit = (char)(sex - L'0');
    } else {
        this->str = L'M';
    }
}

Sex::Sex() {
    this->str = L'M';
}

Sex &Sex::operator=(wchar_t sex) {
    Sex s = Sex(sex);
    memcpy(this, &s, sizeof(s));
    return *this;
}
