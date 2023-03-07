#include "make.h"
#include "iostream"
#include "classes/Table.hpp"
#include "typeinfo"
#include <type_traits>


using namespace std;

int main() {

    Table<Person> table = Table<Person>("", L"       Фамилия       :Математика:Русский:Английский:Пол", 5, "  ");
    table.initCurses();
    table.sidesScreen();
    for (int i = 0; i < 999999; i++){
        table.sortedRows.pushBack(table.searchedRows.pushBack(table.rows.pushBack(table.list.pushBack(Person(L"qwerty", i%100, -i%100, i%101, L'м')))));
    }
    /*wchar_t *q = L"q";
    table.search(1,q);*/

   /* wchar_t ***a = table.getDataByIndex(0);
    for (int i = 0; i < 11; i++) {
        for (int j =0; j < table.countColumns; j++){
            delete[] a[i][j];
            a[i][j] = nullptr;
        }
        delete[] a[i];
        a[i] = nullptr;
    }
    delete[] a;*/
    table.redrawScreen();

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
