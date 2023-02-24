#ifndef MAIN_CPP_TABLE_HPP
#define MAIN_CPP_TABLE_HPP

#include <fstream>

#include "LinkedList.hpp"
#include <iostream>
#include <cstring>
#include <clocale>
#include <regex>
#include <termios.h>
#include <csignal>
#include <ncurses.h>


using namespace std;

template<typename T>
class Table {
public:
    unsigned char countColumns;
    const unsigned char outputLength = 20;

    char *filename;
    char *types;
    wchar_t *nameOfColumns;
    wchar_t **names;
    const wchar_t *menuNames[3] = {L"Добавление элемента", L"Удаление элемента", L"Выход"};

    LinkedList<T> list;
    LinkedList<Node<T>> rows;
    LinkedList<Node<Node<T>>> sortedRows;
    Node<Node<Node<T>>> *startOutput;

    WINDOW *screen;
    WINDOW *menu;
    WINDOW *search;
    WINDOW *sort;
    WINDOW *table;


    Table(const char *filename, const wchar_t *nameOfColumns, unsigned char countColumns, const char *types);

    void initCurses();

    void sidesScreen();

    void redrawScreen();

    void selectMenu();

    void selectSearch();

    void selectSort();

    void selectTable();

    void finitCurses();

    int readListFromFile();

    void choiceMenu();

    void outputRow(WINDOW *window, wchar_t **values, int y);

    void outputTopOfTable(WINDOW *window, int y);

    void outputBottomOfTable(WINDOW *window, int y);

    void outputTopOfRow(WINDOW *window, int y, int x);

    void splitNames();
};

template<typename T>
void Table<T>::outputBottomOfTable(WINDOW *window, int y) {
    wmove(window, y, 0);
    wprintw(window, "%ls", L"└─");
    for (int i = 0; i < countColumns; i++) {
        for (int j = 0; j < ::wcslen(names[i]); j++) {
            wprintw(window, "%ls", L"─");
        }
        if (i != countColumns - 1) {
            wprintw(window, "%ls", L"─┴─");
        }
    }
    wprintw(window, "%ls", L"─┘");
}

template<typename T>
void Table<T>::outputTopOfTable(WINDOW *window, int y) {
    wmove(window, y, 0);
    wprintw(window, "%ls", L"┌─");
    for (int i = 0; i < countColumns; i++) {
        for (int j = 0; j < ::wcslen(names[i]); j++) {
            wprintw(window, "%ls", L"─");
        }
        if (i != countColumns - 1) {
            wprintw(window, "%ls", L"─┬─");
        }
    }
    wprintw(window, "%ls", L"─┐");
}

template<typename T>
void Table<T>::outputRow(WINDOW *window, wchar_t **values, int y) {
    outputTopOfRow(window, y, 0);
    wmove(window, y + 1, 0);
    wprintw(window, "%ls", L"│ ");
    for (int i = 0; i < countColumns; i++) {
        wprintw(window, "%ls", values[i]);
        if (i != countColumns - 1) {
            wprintw(window, "%ls", L" │ ");
        }
    }
    wprintw(window, "%ls", L" │");
}

template<typename T>
void Table<T>::outputTopOfRow(WINDOW *window, int y, int x) {
    wmove(window, y, x);
    wprintw(window, "%ls", L"├─");
    for (int i = 0; i < countColumns; i++) {
        for (int j = 0; j < ::wcslen(names[i]); j++) {
            wprintw(window, "%ls", L"─");
        }
        if (i != countColumns - 1) {
            wprintw(window, "%ls", L"─┼─");
        }
    }
    wprintw(window, "%ls", L"─┤");
}


template<typename T>
void Table<T>::sidesScreen() {
    WINDOW *sides = subwin(screen, 30, 120, 0, 0);
    curs_set(0);
    int c = 0, h, w;
    getmaxyx(sides, h, w);
    while (c != 10) {
        for (int y = 0; y < 30; y++) {
            for (int x = 0; x < 120; x++) {
                if ((x == 0) || (y == 0) || (x == 119) || (y == 29)) {
                    wattron(sides, A_REVERSE);
                }
                mvwaddstr(sides, y, x, " ");
                wattroff(sides, A_REVERSE);
            }
        }
        mvwaddwstr(sides, h / 2, w / 2 - 18, L"Растяните экран, чтобы прямоугольник");
        mvwaddwstr(sides, h / 2 + 1, w / 2 - 20, L"был виден полностью, затем нажмите ENTER");
        wrefresh(sides);
        c = getch();
    }
    curs_set(1);
    /*delwin(sides);*/
    clear();
}

template<typename T>
void Table<T>::initCurses() {
    initscr();
    cbreak();
    this->screen = stdscr;
    this->menu = subwin(screen, 2, 120, 0, 0);
    this->search = subwin(screen, 2, 120, 2, 0);
    this->sort = subwin(screen, 2, 120, 4, 0);
    this->table = subwin(screen, 24, 120, 6, 0);
    sidesScreen();

}

template<typename T>
void Table<T>::redrawScreen() {
    auto **fieldsSearch = new wchar_t *[countColumns];
    for (int i = 0; i < countColumns; i++) {
        int charLength = ::wcslen(names[i]);
        fieldsSearch[i] = new wchar_t[charLength + 1];
        for (int j = 0; j < charLength; j++) {
            fieldsSearch[i][j] = L' ';
        }
    }

    outputRow(search, fieldsSearch, 0);
    outputTopOfTable(search, 0);
    outputRow(sort, names, 0);

    for (int i = 0; i < 22; i += 2) {
        outputRow(table, fieldsSearch, i);
    }
    int y = getcury(table);
    outputBottomOfTable(table, y + 1);

    box(menu, 0, 0);
    wrefresh(menu);
    wrefresh(search);
    wrefresh(sort);
    wrefresh(table);
    getch();

}

template<typename T>
void Table<T>::selectMenu() {

}

template<typename T>
void Table<T>::selectSearch() {

}

template<typename T>
void Table<T>::selectSort() {

}

template<typename T>
void Table<T>::selectTable() {

}


template<typename T>
void Table<T>::finitCurses() {
    endwin();
}


template<typename T>
void Table<T>::choiceMenu() {

}


template<typename T>
int Table<T>::readListFromFile() {
    std::ifstream in(filename, std::ios::binary);
    if (!in) throw std::ifstream::failure("Can't open file");
    in.seekg(0, std::ios_base::end);
    long long countElements = in.tellg() / sizeof(T);
    in.seekg(0, std::ios_base::beg);
    in.clear();
    for (long long i = 0; i < countElements; i++) {
        T element;
        in.read((char *) &element, sizeof(T));
        Node<T> *node = list.pushBack(element);
        rows.pushBack(node);
    }
    in.close();
    return 0;
}

template<typename T>
void Table<T>::splitNames() {

    wchar_t *lex, i = 0;
    wchar_t *ptr;

    this->names = new wchar_t *[countColumns];
    this->names[i] = new wchar_t[8];
    ::wcscpy(this->names[i], L"   №   ");
    i++;
    lex = std::wcstok(this->nameOfColumns, L":", &ptr);

    while (lex != NULL) {
        this->names[i] = new wchar_t[::wcslen(lex) + 1];
        ::wcscpy(this->names[i], lex);

        lex = std::wcstok(NULL, L":", &ptr);
        i++;
    }
}

template<typename T>
Table<T>::Table(const char *filename, const wchar_t *nameOfColumns, unsigned char countColumns, const char *types) {
    ::setlocale(LC_ALL, "");

    size_t countChars = strlen(filename) + 1;
    this->filename = new char[countChars];
    std::strcpy(this->filename, filename);

    countChars = ::wcslen(nameOfColumns) + 1;

    this->nameOfColumns = new wchar_t[countChars];
    std::wcscpy(this->nameOfColumns, nameOfColumns);

    countChars = strlen(types) + 1;
    this->types = new char[countChars];
    std::strcpy(this->types, types);


    this->countColumns = countColumns + 1;
    splitNames();
    initCurses();
}


#endif //MAIN_CPP_TABLE_HPP
