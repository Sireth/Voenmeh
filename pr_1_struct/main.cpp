#include "make.h"
#include "iostream"
#include "classes/Table.hpp"
#include "typeinfo"
#include <type_traits>


using namespace std;

int main() {

    Table<Person> table = Table<Person>(" ", L"  Name  :   mamaam   :        wer4        :   123   :   hhhfj", 5, "  ");
    table.redrawScreen();
    /*Person p = Person("ef",100,100,100, 'm');
    char a, *pi;
    pi = &a;
    *pi =5;*/
    /*decltype(p.sex) *s;

    s = (decltype(p.sex) *)p[4];

    *s = 1;*/

//    (decltype(p.sex))(p[4])) = 1;

    /*char s;
    s = p[1];

    printf("%d", *(s));*/
    /*p.set("fuhhrf", 0);
    printf("%s",p[0]);*/

    return 0;
}