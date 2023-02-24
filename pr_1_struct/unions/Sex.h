#ifndef TERM_2_SEX_H
#define TERM_2_SEX_H


union Sex {
    char str;
    char digit=0;

public:
    Sex();
    explicit Sex(char sex);
    Sex& operator=(char sex);
};


#endif //TERM_2_SEX_H
