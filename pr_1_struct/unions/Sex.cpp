#include "cstring"

#include "Sex.h"

Sex::Sex(wchar_t sex) {
    if (wcschr(L"МЖмжMFmf", sex) != nullptr) {
        this->str = sex;
    } else if (sex == 0 || sex == 1) {
        this->digit = sex;
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
