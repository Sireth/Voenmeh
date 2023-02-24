#include "make.h"
#include "iostream"
#include "classes/Table.hpp"
#include "typeinfo"
#include <type_traits>


using namespace std;

int main() {

    Table<Person> table = Table<Person>("", L"       Фамилия       :Математика:Русский:Английский:Пол", 5, "  ");
    for (int i = 0; i < 13; i++){
        table.sortedRows.pushBack(table.rows.pushBack(table.list.pushBack(Person(L"qwerty", 100+i, 100+i, 100+i, L'м'))));
    }
    table.redrawScreen();
    wchar_t ***pString = table.getData(0);
//    table.redrawScreen();
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
