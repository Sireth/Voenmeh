#include "make.h"
//#include "iostream"
#include "classes/Table.hpp"
#include "gen.h"



using namespace std;

int main(int argc, char *argv[]) {
    ::setlocale(LC_ALL, "");
    auto *fileName = new char[1024];
    if (argc > 1) ::strncpy(fileName, argv[1], 1024);
    else {
        ::wcout << L"Введите имя файла (без русских символов): ";
        ::cin >> fileName;
    }
    Table<Person> table = Table<Person>(fileName, L"       Фамилия       :Математика:Русский:Английский:Пол", 5, Person::get, Person::set, Person::comparison);

    delete[] fileName;
    fileName = nullptr;
    table.initCurses();
    table.redrawScreen();


    return 0;
    /*int t;

    Sex s(L'1');

    printf("%d\n%lc", s.digit, s.str);


    cin >> t;*/

    /*const char *filename = "students500.bin";
    std::ofstream out(filename, ::ios::binary | ::ios::out);
    if (!out) throw std::ifstream::failure("Can't open file");

    long sizeT = sizeof(Person);
    for (int i = 0; i < 500000; i++) {
        wchar_t sex = sexGen();
        Person t = Person(surnameGen(sex).c_str(), ballGen(), ballGen(), ballGen(), sex);
        out.write((char *) &t, sizeT);
        cout << i << endl;
    }

    out.close();
    return 0;*/
}

