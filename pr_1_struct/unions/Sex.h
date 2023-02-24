#ifndef TERM_2_SEX_H
#define TERM_2_SEX_H
#include "iostream"

union Sex {
    wchar_t str;
    char digit=0;

public:
    Sex();
    explicit Sex(wchar_t sex);
    Sex& operator=(wchar_t sex);
};


#endif //TERM_2_SEX_H
