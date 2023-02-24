#include "cstring"

#include "Sex.h"

Sex::Sex(char sex) {
    if(strchr("МЖмжMFmf", sex) != nullptr){
        this->str = sex;
    }
    else{
        this->digit = sex;
    }
}

Sex::Sex() {
    this->str = 'M';
}

Sex &Sex::operator=(char sex) {
    Sex s = Sex(sex);
    memcpy(this, &s, sizeof(s));
    return *this;
}
