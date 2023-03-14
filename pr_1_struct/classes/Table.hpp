#ifndef MAIN_CPP_TABLE_HPP
#define MAIN_CPP_TABLE_HPP

#include <fstream>

#include "LinkedList.hpp"
#include <iostream>
#include <cstring>
#include <clocale>
#include <regex>
#include <csignal>
#include <ncurses.h>

#define MENU_HINT 0
#define SEARCH_HINT 1
#define SORT_HINT 2
#define TABLE_HINT 3
#define LOADING_HINT 4
#define ADD_HINT 5
#define DELETE_HINT 6
#define EDIT_HINT 7


using namespace std;

template<typename T>
class Table {

public:
    unsigned char countColumns;

    char *filename;
    char *types;
    wchar_t *nameOfColumns;
    wchar_t **names;
    const wchar_t *menuNames[4] = {L"Добавление элемента", L"Сохранить файл", L"Помощь", L"Выход"};

    LinkedList<T> list;
    LinkedList<Node<T>> rows;
    LinkedList<Node<Node<T>>> searchedRows;
    LinkedList<Node<Node<Node<T>>>> sortedRows;
    Node<Node<Node<Node<T>>>> *startOutput;
    Node<Node<Node<Node<T>>>> *endOutput;


    WINDOW *wScreen;
    WINDOW *wMenu;
    WINDOW *wSearch;
    WINDOW *wSort;
    WINDOW *wTable;
    WINDOW *wHint;
private:
    long long number;

public:

    Table(char *filename, const wchar_t *nameOfColumns, unsigned char countColumns, const char *types);

    void selectSearch(int index);

    void selectMenu();

    void selectSort(int index);

    void selectTable();

    void selectEdit(Node<T> *node, int indexRow);

    void addElement();

    void initCurses();

    void deinitCurses();

    void drawHint(int index);

    void sidesScreen();

    void redrawScreen();

    int readListFromFile();

    int writeListToFile();

    void redrawTable();

    void outputMenu(int highlight);

    void outputRow(WINDOW *window, wchar_t **values, int y, int highlight);

    void outputRow(WINDOW *window, wchar_t **values, int y, int highlight, int color);

    void outputTopOfTable(WINDOW *window, int y);

    void outputBottomOfTable(WINDOW *window, int y);

    void outputTopOfRow(WINDOW *window, int y, int x);

    void splitNames();

    wchar_t ***getData();

    wchar_t ***getDataByIndex(int index);

    wchar_t ***getDataNext();

    wchar_t ***getDataPrev();

    void centeringString(wchar_t *dest, int sizeOfDest, const wchar_t *value);

    void search(int index, wchar_t *data);

    void sort(int index, char direction);

private:

    void mergeSort(Node<Node<Node<Node<T>>>> **head, int index, char direction);

    void split(Node<Node<Node<Node<T>>>> *head, Node<Node<Node<Node<T>>>> **left, Node<Node<Node<Node<T>>>> **right);

    Node<Node<Node<Node<T>>>> *
    merge(Node<Node<Node<Node<T>>>> *left, Node<Node<Node<Node<T>>>> *right, int index, char direction);
};

template<typename T>
void Table<T>::addElement() {
    sortedRows.eraseAll();
    searchedRows.eraseAll();
    startOutput = nullptr;
    T t = T();
    sortedRows.pushBack(searchedRows.pushBack(rows.pushBack(list.pushBack(t))));
    return selectTable();
}

template<typename T>
void Table<T>::selectEdit(Node<T> *node, int indexRow) {
    drawHint(EDIT_HINT);
    curs_set(0);
    ::wint_t c = 0;
    int choice = 1;
    bool editFlag = false;
    wchar_t *str;
    int countOfSymbols;
    auto **fieldsEdit = new wchar_t *[countColumns];
    for (int i = 0; i < countColumns; i++) {
        int charLength = ::wcslen(names[i]);
        fieldsEdit[i] = new wchar_t[charLength + 1];
    }
    do {
        switch (c) {
            case KEY_RIGHT: {
                if (!editFlag) {
                    choice++;
                    if (choice > countColumns - 1) choice = countColumns - 1;
                }
                break;
            }
            case KEY_LEFT: {
                if (!editFlag) {
                    choice--;
                    if (choice < 1) choice = 1;
                }
                break;
            }
            case 10: {
                editFlag = !editFlag;
                if (editFlag) {

                    str = new wchar_t[::wcslen(names[choice]) + 1];
                    countOfSymbols = 0;
                    str[0] = 0;
                } else {
                    T t = node->getData();
                    t.set(str, choice - 1);
                    node->editData(t);
                    delete[] str;
                    str = nullptr;
                }
                break;
            }
            case KEY_BACKSPACE: {
                if (countOfSymbols != 0) {
                    countOfSymbols--;
                    str[countOfSymbols] = 0;
                }
                break;
            }
            default: {
                if (editFlag && (::wcslen(names[choice]) > countOfSymbols) &&
                    (c >= 44 && c < 176 || c == 32 || c >= 0x400)) {
                    str[countOfSymbols] = c;
                    countOfSymbols++;
                    str[countOfSymbols] = 0;
                }
                break;
            }
        }
        auto *value = new wchar_t[::wcslen(names[0]) + 1];
        ::swprintf(value, ::wcslen(names[0]) + 1, L"Edit");
        centeringString(fieldsEdit[0], ::wcslen(names[0]) + 1, value);
        T t = node->getData();
        for (int j = 0; j < countColumns - 1; j++) {
            delete[] value;
            int lengthOfStr = ::wcslen(names[j + 1]);
            value = new wchar_t[lengthOfStr + 1];
            if (editFlag && (j + 1 == choice)) {
                ::wcsncpy(value, str, countOfSymbols + 1);
            } else {
                auto *ptr = new wchar_t[lengthOfStr + 1];
                t.get(ptr, j);
                ::wcsncpy(value, ptr, lengthOfStr + 1);
                delete[] ptr;
                ptr = nullptr;
            }

            fieldsEdit[j + 1] = new wchar_t[lengthOfStr + 1];
            centeringString(fieldsEdit[j + 1], lengthOfStr + 1, value);
        }
        delete[] value;
        value = nullptr;
        if (!editFlag)
            outputRow(wTable, fieldsEdit, indexRow * 2, choice);
        else
            outputRow(wTable, fieldsEdit, indexRow * 2, choice, 1);
        wrefresh(wTable);
        get_wch(&c);
    } while (c != 27);

    for (int i = 0; i < countColumns; i++) {
        delete[] fieldsEdit[i];
        fieldsEdit[i] = nullptr;
    }
    delete[] fieldsEdit;
    fieldsEdit = nullptr;
}

template<typename T>
void Table<T>::deinitCurses() {
    curs_set(1);
    clear();
    delwin(wMenu);
    delwin(wSearch);
    delwin(wSort);
    delwin(wTable);
    delwin(wHint);
    delwin(wScreen);

    endwin();
}

template<typename T>
void Table<T>::drawHint(int index) {
    wmove(wHint, 0, 0);
    move(29, 0);
    clrtoeol();
    switch (index) {
        case 0: {//Menu
            wprintw(wHint, "%ls", L"←→↑↓: Перемещение.    ↵: Выбор.    ↹: Переход к таблице.");
            break;
        }
        case 1: {//Search
            wprintw(wHint, "%ls", L"←→↑↓: Перемещение.    ↵: Ввод.   ↹: Переход к таблице.");
            break;
        }
        case 2: {//Sort
            wprintw(wHint, "%ls", L"←→↑↓: Перемещение.    ↵: Сортировка по полю.   ↹: Переход к таблице.");
            break;
        }
        case 3: {//Table
            wprintw(wHint, "%ls", L"↑↓: Перемещение.    ↵: Редактирование.   ↹: Выход из таблицы.    DEL: Удаление.");
            break;
        }
        case 4: {//Loading
            wprintw(wHint, "%ls", L"Обработка данных.");
            break;
        }
        case 5: {//Delete
            wprintw(wHint, "%ls", L"");
            break;
        }
        case 6: {//Add
            wprintw(wHint, "%ls", L"");
            break;
        }
        case 7: {//Edit
            wprintw(wHint, "%ls", L"←→: Перемещение.    ↵: Редактирование.   ESC: Выход из редактирования.");
            break;
        }
        default: {
            break;
        }
    }
    wrefresh(wHint);
}

template<typename T>
wchar_t ***Table<T>::getData() {
    if (startOutput == nullptr) return getDataByIndex(0);
    auto *value = new wchar_t[::wcslen(names[0]) + 1];
    auto ***values = new wchar_t **[11];
    Node<Node<Node<Node<T>>>> *nT;
    nT = startOutput;
    T t;
    if (nT != nullptr)
        t = nT->getData().getData().getData().getData();

    for (int i = 0; i < 11; i++) {
        values[i] = new wchar_t *[countColumns];
        values[i][0] = new wchar_t[::wcslen(names[0]) + 1];

        ::swprintf(value, ::wcslen(names[0]) + 1, L"%d", number);
        centeringString(values[i][0], ::wcslen(names[0]) + 1, value);

        for (int j = 0; j < countColumns - 1; j++) {
            delete[] value;
            int lengthOfStr = ::wcslen(names[j + 1]);
            value = new wchar_t[lengthOfStr + 1];
            if (nT != nullptr) {
                auto *ptr = new wchar_t[lengthOfStr + 1];
                t.get(ptr, j);
                ::wcsncpy(value, ptr, lengthOfStr + 1);
                delete[] ptr;
                ptr = nullptr;
            } else
                ::swprintf(value, lengthOfStr + 1, L"—");

            values[i][j + 1] = new wchar_t[lengthOfStr + 1];
            centeringString(values[i][j + 1], lengthOfStr + 1, value);
        }
        if (nT != nullptr)
            nT = (*nT).next;

        if (nT != nullptr && i != 10) {
            t = nT->getData().getData().getData().getData();
            endOutput = nT;
        }
        number++;
    }
    delete[] value;
    value = nullptr;
    number -= 11;
    return values;
}

template<typename T>
void Table<T>::selectTable() {
    drawHint(TABLE_HINT);
    curs_set(1);
    move(7, 1);
    wmove(wTable, 1, 1);
    wrefresh(wTable);
    wchar_t ***fieldsValues = getData();
    int c = 0, currentRow = 0;
    do {
        M1:
        curs_set(1);
        switch (c) {
            case KEY_UP: {
                currentRow--;
                if (currentRow < 0) {
                    currentRow = 0;
                    fieldsValues = getDataPrev();
                }
                break;
            }
            case KEY_DOWN: {
                currentRow++;
                if (currentRow > 10) {
                    currentRow = 10;
                    fieldsValues = getDataNext();
                }
                break;
            }
            case 10: {
                Node<Node<Node<Node<T>>>> *node = startOutput;
                if (node != nullptr) {
                    for (int i = 0; i < currentRow; i++) {
                        if (node->next != nullptr)
                            node = node->next;
                        else goto M1;
                    }
                    Node<T> *nodeEl = node->getData().getData().getData().next;
                    if (nodeEl == nullptr) nodeEl = list.getTail();
                    else nodeEl = nodeEl->prev;
                    selectEdit(nodeEl, currentRow);
                }
                fieldsValues = getData();
                c = 99;
                drawHint(TABLE_HINT);
                move(7, 1);
                currentRow = 0;
                wmove(wTable, currentRow * 2 + 1, 1);
                goto M1;
                break;
            }
            case KEY_DC: { //DELETE
                Node<Node<Node<Node<T>>>> *node = startOutput->getAddress();
                if (node != nullptr) {
                    for (int i = 0; i < currentRow; i++) {
                        node = node->next;
                    }
                    if (currentRow == 0) startOutput = nullptr;

                    list.erase(node->getData().getData().getData().getAddress());
                    rows.erase(node->getData().getData().getAddress());
                    searchedRows.erase(node->getData().getAddress());
                    sortedRows.erase(node);
                }

                fieldsValues = getData();
                c = 99;
                goto M1;
                break;
            }
            default: {
                break;
            }
        }
        wmove(wTable, 0, 0);
        for (int i = 0; i < 11; i++) {
            outputRow(wTable, fieldsValues[i], i * 2, 99);
        }
        int y = getcury(wTable);
        outputBottomOfTable(wTable, y + 1);
        wmove(wTable, currentRow * 2 + 1, 1);
        wrefresh(wTable);
    } while ((c = getch()) != 9);
    curs_set(0);
    return selectSort(0);
}

template<typename T>
void Table<T>::selectSort(int index) {
    drawHint(SORT_HINT);
    outputRow(wSort, names, 0, index + 1);
    wrefresh(wSort);
    int c, choice = index + 1;
    bool sortFlag = false;
    noecho();
    while ((c = getch()) != 9) {
        switch (c) {
            case KEY_RIGHT: {
                choice++;
                if (choice > countColumns - 1) choice = countColumns - 1;
                break;
            }
            case KEY_LEFT: {
                choice--;
                if (choice < 1) choice = 1;
                break;
            }
            case 10: {
                sortFlag = !sortFlag;
                if (!sortFlag) {
                    drawHint(LOADING_HINT);
                    sort(choice - 1, 1);
                    redrawTable();
                    wrefresh(wTable);
                    drawHint(SORT_HINT);
                } else {
                    drawHint(LOADING_HINT);
                    sort(choice - 1, -1);
                    redrawTable();
                    wrefresh(wTable);
                    drawHint(SORT_HINT);
                }
                break;
            }
            case KEY_UP: {
                outputRow(wSort, names, 0, 99);
                wrefresh(wSort);
                return selectSearch(choice);
            }
            default: {
                break;
            }
        }
        wmove(wSort, 0, 0);
        outputRow(wSort, names, 0, choice);
        outputTopOfTable(wSearch, 0);
        wrefresh(wSort);
    }
    outputRow(wSort, names, 0, 99);
    wrefresh(wSort);
    return selectTable();
}

template<typename T>
void Table<T>::outputMenu(int highlight) {
    wmove(wMenu, 0, 0);
    int x = 0;
    for (int i = 0; i < 4; i++) {
        if (i == highlight) {
            wattr_on(wMenu, A_REVERSE, nullptr);
        }
        wprintw(wMenu, "%ls", menuNames[i]);
        wattr_off(wMenu, A_REVERSE, nullptr);
        x += ::wcslen(menuNames[i]) + 4;
        wmove(wMenu, 0, x);
    }
    wrefresh(wMenu);
}

template<typename T>
void Table<T>::selectMenu() {
    drawHint(MENU_HINT);
    noecho();
    outputMenu(0);
    int c, choice = 0;
    while ((c = getch()) != 9) {
        switch (c) {
            case KEY_RIGHT: {
                choice++;
                if (choice > 3) choice = 3;
                break;
            }
            case KEY_LEFT: {
                choice--;
                if (choice < 0) choice = 0;
                break;
            }
            case 10: {
                switch (choice) {
                    case 0: {
                        outputMenu(99);
                        return addElement();
                    }
                    case 1: {
                        drawHint(LOADING_HINT);
                        writeListToFile();
                        drawHint(MENU_HINT);
                        break;
                    }
                    case 2: {
                        clear();
                        WINDOW *wHelp = subwin(stdscr, 30, 120, 0, 0);
                        box(wHelp, 0, 0);
                        wrefresh(wHelp);
                        getch();
                        clear();
                        delwin(wHelp);
                        return redrawScreen();
                    }
                    case 3: {
                        deinitCurses();
                        ::exit(1);
                    }
                    default: {
                        break;
                    }
                }
                break;
            }
            case KEY_DOWN: {
                outputMenu(99);
                return selectSearch(1);
            }
            default: {
                break;
            }
        }
        outputMenu(choice);
        wrefresh(wMenu);
    }
    outputMenu(99);
    return selectTable();

}

template<typename T>
void Table<T>::redrawTable() {
    wmove(wTable, 0, 0);
    auto ***fieldsValues = getDataByIndex(0);
    for (int i = 0; i < 11; i++) {
        outputRow(wTable, fieldsValues[i], i * 2, 99);
    }
    int y = getcury(wTable);
    outputBottomOfTable(wTable, y + 1);
    wrefresh(wTable);
    delete fieldsValues;
}

template<typename T>
void Table<T>::selectSearch(int index) {
    drawHint(SEARCH_HINT);
    auto **fieldsSearch = new wchar_t *[countColumns];
    for (int i = 0; i < countColumns; i++) {
        int charLength = ::wcslen(names[i]);
        fieldsSearch[i] = new wchar_t[charLength + 1];
    }
    int choice = index, findIndex = 99;
    ::wint_t c = 0;
    bool writeFlag = false;
    noecho();
    wchar_t *str = nullptr;
    int countOfSymbols = 0;
    do {
        switch (c) {
            case KEY_RIGHT: {
                if (!writeFlag) {
                    choice++;
                    if (choice > countColumns - 1) choice = countColumns - 1;
                }
                break;
            }
            case KEY_LEFT: {
                if (!writeFlag) {
                    choice--;
                    if (choice < 1) choice = 1;
                }
                break;
            }
            case 10: {
                writeFlag = !writeFlag;
                if (writeFlag) {
                    delete[] str;
                    str = new wchar_t[::wcslen(names[choice]) + 1];
                    countOfSymbols = 0;
                    str[0] = 0;
                } else {
                    drawHint(LOADING_HINT);
                    search(choice - 1, str);
                    redrawTable();
                    drawHint(SEARCH_HINT);
                }
                break;
            }
            case KEY_BACKSPACE: {
                if (countOfSymbols != 0) {
                    countOfSymbols--;
                    str[countOfSymbols] = 0;
                }
                break;
            }
            case KEY_UP: {
                outputRow(wSearch, fieldsSearch, 0, 99);
                outputTopOfTable(wSearch, 0);
                wrefresh(wSearch);

                for (int i = 0; i < countColumns; i++) {
                    delete[] fieldsSearch[i];
                    fieldsSearch[i] = nullptr;
                }
                delete[] fieldsSearch;
                delete[] str;
                str = nullptr;

                return selectMenu();
            }
            case KEY_DOWN: {
                outputRow(wSearch, fieldsSearch, 0, 99);
                outputTopOfTable(wSearch, 0);
                wrefresh(wSearch);

                for (int i = 0; i < countColumns; i++) {
                    delete[] fieldsSearch[i];
                    fieldsSearch[i] = nullptr;
                }
                delete[] fieldsSearch;
                delete[] str;
                str = nullptr;

                return selectSort(choice - 1);
            }
            default: {
                if (writeFlag && (countOfSymbols) < (::wcslen(names[choice])) &&
                    (c >= 44 && c < 176 || c == 32 || c >= 0x400)) {
                    str[countOfSymbols] = c;
                    countOfSymbols++;
                    str[countOfSymbols] = 0;
                }
                break;
            }
        }
        auto *value = new wchar_t[::wcslen(names[0]) + 1];
        ::swprintf(value, ::wcslen(names[0]) + 1, L"%d", searchedRows.len());
        centeringString(fieldsSearch[0], ::wcslen(names[0]) + 1, value);

        for (int j = 1; j < countColumns; j++) {
            delete[] value;
            int lengthOfStr = ::wcslen(names[j]);
            value = new wchar_t[lengthOfStr + 1];
            value[0] = L'⌕';
            value[1] = 0;
            if (writeFlag && (j == choice)) {
                ::wcsncpy(value, str, countOfSymbols + 1);
            }
            centeringString(fieldsSearch[j], lengthOfStr + 1, value);
        }
        delete[] value;
        value = nullptr;
        wmove(wSearch, 0, 0);
        if (!writeFlag)
            outputRow(wSearch, fieldsSearch, 0, choice);
        else
            outputRow(wSearch, fieldsSearch, 0, choice, 1);
        outputTopOfTable(wSearch, 0);
        wrefresh(wSearch);
        get_wch(&c);
    } while (c != 9);
    outputRow(wSearch, fieldsSearch, 0, 99);
    outputTopOfTable(wSearch, 0);
    wrefresh(wSearch);

    for (int i = 0; i < countColumns; i++) {
        delete[] fieldsSearch[i];
        fieldsSearch[i] = nullptr;
    }
    delete[] fieldsSearch;
    delete[] str;
    str = nullptr;

    return selectTable();
}

template<typename T>
void Table<T>::search(int index, wchar_t *data) {
    Node<Node<T>> *element = rows[0];
    searchedRows.eraseAll();
    int lengthOfStr = ::wcslen(names[index + 1]);
    /*data[lengthOfStr + 1] = 0;*/
    sortedRows.eraseAll();
    while (element != nullptr) {
        T t = element->getData().getData();
        auto *ptr = new wchar_t[lengthOfStr + 1];
        t.get(ptr, index);
        if (::wcsstr(ptr, data) != nullptr) {
            sortedRows.pushBack(searchedRows.pushBack(element));
        }
        delete[] ptr;
        ptr = nullptr;
        element = element->next;
    }
}

template<typename T>
void Table<T>::sort(int index, char direction) {
    Node<Node<Node<Node<T>>>> *head = sortedRows.getHead();
    if (head != nullptr) {
        mergeSort(&head, index, direction);
        sortedRows.resetList(head);
    }
}

template<typename T>
void
Table<T>::split(Node<Node<Node<Node<T>>>> *head, Node<Node<Node<Node<T>>>> **left, Node<Node<Node<Node<T>>>> **right) {
    Node<Node<Node<Node<T>>>> *slow = head;
    Node<Node<Node<Node<T>>>> *fast = head->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *left = head;
    *right = slow->next;
    slow->next = NULL;
    (*right)->prev = NULL;
}


template<typename T>
// Слияние двух отсортированных списков
Node<Node<Node<Node<T>>>> *
Table<T>::merge(Node<Node<Node<Node<T>>>> *left, Node<Node<Node<Node<T>>>> *right, int index, char direction) {
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }
    Node<Node<Node<Node<T>>>> *result = NULL;
    Node<Node<Node<Node<T>>>> *cur = NULL;
    int lengthOfStr = ::wcslen(names[index + 1]);
    auto *str = new wchar_t[lengthOfStr + 1];
    right->getData().getData().getData().getData().get(str, index);
    char ptr = left->getData().getData().getData().getData().comparison(index, str) * direction;

    delete[] str;
    str = nullptr;

    if (ptr <= 0) {
        result = left;
        left = left->next;
    } else {
        result = right;
        right = right->next;
    }
    cur = result;
    while (left != NULL && right != NULL) {
        str = new wchar_t[lengthOfStr + 1];
        right->getData().getData().getData().getData().get(str, index);
        ptr = left->getData().getData().getData().getData().comparison(index, str) * direction;

        delete[] str;
        str = nullptr;

        if (ptr <= 0) {
            cur->next = left;
            left->prev = cur;
            left = left->next;
        } else {
            cur->next = right;
            right->prev = cur;
            right = right->next;
        }
        cur = cur->next;
    }
    if (left != NULL) {
        cur->next = left;
        left->prev = cur;
    }
    if (right != NULL) {
        cur->next = right;
        right->prev = cur;
    }
    return result;
}


template<typename T>
// Сортировка слиянием
void Table<T>::mergeSort(Node<Node<Node<Node<T>>>> **head, int index, char direction) {
    Node<Node<Node<Node<T>>>> *cur = *head;
    Node<Node<Node<Node<T>>>> *left = NULL;
    Node<Node<Node<Node<T>>>> *right = NULL;
    if (cur == NULL || cur->next == NULL) {
        return;
    }
    split(cur, &left, &right);
    mergeSort(&left, index, direction);
    mergeSort(&right, index, direction);
    *head = merge(left, right, index, direction);
}

template<typename T>
void Table<T>::centeringString(wchar_t *dest, int sizeOfDest, const wchar_t *value) {
    auto *str = new wchar_t[sizeOfDest + 1];
    int len = wcslen(value);
    int padding = (sizeOfDest - len) / 2;
    ::swprintf(str, sizeOfDest, L"%*s%ls%*s", padding, "", value, sizeOfDest - padding - len, "");
    ::wcsncpy(dest, str, sizeOfDest - 1);
    dest[sizeOfDest - 1] = 0;
    delete[] str;
    str = nullptr;
}

template<typename T>
wchar_t ***Table<T>::getDataNext() {
    auto *value = new wchar_t[::wcslen(names[0]) + 1];
    auto ***values = new wchar_t **[11];
    Node<Node<Node<Node<T>>>> *nT;
    if (endOutput->next != nullptr && startOutput != nullptr) {
        nT = startOutput->next;
        startOutput = nT;
        number += 1;
    } else
        nT = startOutput;

    T t;
    if (nT != nullptr)
        t = nT->getData().getData().getData().getData();

    for (int i = 0; i < 11; i++) {
        values[i] = new wchar_t *[countColumns];
        values[i][0] = new wchar_t[::wcslen(names[0]) + 1];

        ::swprintf(value, ::wcslen(names[0]) + 1, L"%d", number);
        centeringString(values[i][0], ::wcslen(names[0]) + 1, value);

        for (int j = 0; j < countColumns - 1; j++) {
            delete[] value;
            int lengthOfStr = ::wcslen(names[j + 1]);
            value = new wchar_t[lengthOfStr + 1];
            if (nT != nullptr) {
                auto *ptr = new wchar_t[lengthOfStr + 1];
                t.get(ptr, j);
                ::wcsncpy(value, ptr, lengthOfStr + 1);
                delete[] ptr;
                ptr = nullptr;
            } else
                ::swprintf(value, lengthOfStr + 1, L"—");

            values[i][j + 1] = new wchar_t[lengthOfStr + 1];
            centeringString(values[i][j + 1], lengthOfStr + 1, value);
        }
        if (nT != nullptr)
            nT = (*nT).next;

        if (nT != nullptr && i != 10) {
            t = nT->getData().getData().getData().getData();
            endOutput = nT;
        }

        number++;
    }
    delete[] value;
    value = nullptr;
    number -= 11;
    return values;
}

template<typename T>
wchar_t ***Table<T>::getDataPrev() {

    auto *value = new wchar_t[::wcslen(names[0]) + 1];
    auto ***values = new wchar_t **[11];
    Node<Node<Node<Node<T>>>> *nT;
    if (startOutput != nullptr && startOutput->prev != nullptr) {
        nT = startOutput->prev;
        startOutput = nT;
        number -= 1;
    } else
        nT = startOutput;

    T t;
    if (nT != nullptr)
        t = nT->getData().getData().getData().getData();

    for (int i = 0; i < 11; i++) {
        values[i] = new wchar_t *[countColumns];
        values[i][0] = new wchar_t[::wcslen(names[0]) + 1];

        ::swprintf(value, ::wcslen(names[0]) + 1, L"%d", number);
        centeringString(values[i][0], ::wcslen(names[0]) + 1, value);

        for (int j = 0; j < countColumns - 1; j++) {
            delete[] value;
            int lengthOfStr = ::wcslen(names[j + 1]);
            value = new wchar_t[lengthOfStr + 1];
            if (nT != nullptr) {
                auto *ptr = new wchar_t[lengthOfStr + 1];
                t.get(ptr, j);
                ::wcsncpy(value, ptr, lengthOfStr + 1);
                delete[] ptr;
                ptr = nullptr;
            } else
                ::swprintf(value, lengthOfStr + 1, L"—");

            values[i][j + 1] = new wchar_t[lengthOfStr + 1];
            centeringString(values[i][j + 1], lengthOfStr + 1, value);
        }
        if (nT != nullptr)
            nT = (*nT).next;

        if (nT != nullptr && i != 10) {
            t = nT->getData().getData().getData().getData();
            endOutput = nT;
        }
        number++;
    }
    delete[] value;
    value = nullptr;
    number -= 11;
    return values;
}

template<typename T>
wchar_t ***Table<T>::getDataByIndex(int index) {
    number = index + 1;
    auto *value = new wchar_t[::wcslen(names[0]) + 1];
    auto ***values = new wchar_t **[11];

    startOutput = sortedRows[index];
    Node<Node<Node<Node<T>>>> *nT = startOutput;
    T t;
    if (nT != nullptr)
        t = nT->getData().getData().getData().getData();

    for (int i = 0; i < 11; i++) {
        values[i] = new wchar_t *[countColumns];
        values[i][0] = new wchar_t[::wcslen(names[0]) + 1];

        ::swprintf(value, ::wcslen(names[0]) + 1, L"%d", number);
        centeringString(values[i][0], ::wcslen(names[0]) + 1, value);

        for (int j = 0; j < countColumns - 1; j++) {
            delete[] value;
            int lengthOfStr = ::wcslen(names[j + 1]);
            value = new wchar_t[lengthOfStr + 1];
            if (nT != nullptr) {
                auto *ptr = new wchar_t[lengthOfStr + 1];
                t.get(ptr, j);
                ::wcsncpy(value, ptr, lengthOfStr + 1);
                delete[] ptr;
                ptr = nullptr;
            } else
                ::swprintf(value, lengthOfStr + 1, L"—");

            values[i][j + 1] = new wchar_t[lengthOfStr + 1];
            centeringString(values[i][j + 1], lengthOfStr + 1, value);
        }
        if (nT != nullptr)
            nT = (*nT).next;

        if (nT != nullptr && i != 10) {
            t = nT->getData().getData().getData().getData();
            endOutput = nT;
        }
        number++;
    }
    delete[] value;
    value = nullptr;
    number -= 11;
    return values;
}

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
void Table<T>::outputRow(WINDOW *window, wchar_t **values, int y, int highlight) {
    outputTopOfRow(window, y, 0);
    wmove(window, y + 1, 0);
    wprintw(window, "%ls", L"│ ");
    for (int i = 0; i < countColumns; i++) {
        if (i == highlight) {
            wattr_on(window, A_REVERSE, nullptr);
        }
        wprintw(window, "%ls", values[i]);
        wattr_off(window, A_REVERSE, nullptr);
        if (i != countColumns - 1) {
            wprintw(window, "%ls", L" │ ");
        }
    }
    wprintw(window, "%ls", L" │");
}

template<typename T>
void Table<T>::outputRow(WINDOW *window, wchar_t **values, int y, int highlight, int color) {
    outputTopOfRow(window, y, 0);
    wmove(window, y + 1, 0);
    wprintw(window, "%ls", L"│ ");
    for (int i = 0; i < countColumns; i++) {
        if (i == highlight) {
            if (!has_colors())
                wattr_on(window, A_REVERSE, nullptr);
            else
                wattr_on(window, COLOR_PAIR(color), nullptr);
        }
        wprintw(window, "%ls", values[i]);
        if (!has_colors())
            wattr_off(window, A_REVERSE, nullptr);
        else
            wattr_off(window, COLOR_PAIR(color), nullptr);
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
    WINDOW *sides = subwin(wScreen, 30, 120, 0, 0);
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
        clear();
        mvwaddwstr(sides, h / 2, w / 2 - 8, L"Обработка данных");
        wrefresh(sides);
    }
    clear();
    delwin(sides);
}

template<typename T>
void Table<T>::initCurses() {
    initscr();
    resize_term(31, 121);
    curs_set(0);
    cbreak();
    keypad(stdscr, true);
    this->wScreen = stdscr;
    this->wMenu = subwin(wScreen, 2, 120, 0, 0);
    this->wSearch = subwin(wScreen, 2, 120, 2, 0);
    this->wSort = subwin(wScreen, 2, 120, 4, 0);
    this->wTable = subwin(wScreen, 24, 120, 6, 0);
    this->wHint = subwin(wScreen, 1, 120, 29, 0);
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_BLACK, 223);
    }
    sidesScreen();
    readListFromFile();

}

template<typename T>
void Table<T>::redrawScreen() {
    auto **fieldsSearch = new wchar_t *[countColumns];
    for (int i = 0; i < countColumns; i++) {
        int charLength = ::wcslen(names[i]);
        fieldsSearch[i] = new wchar_t[charLength + 1];
    }
    auto *value = new wchar_t[::wcslen(names[0]) + 1];
    ::swprintf(value, ::wcslen(names[0]) + 1, L"%d", searchedRows.len());
    centeringString(fieldsSearch[0], ::wcslen(names[0]) + 1, value);

    for (int j = 1; j < countColumns; j++) {
        delete[] value;
        int lengthOfStr = ::wcslen(names[j]);
        value = new wchar_t[lengthOfStr + 1];
        value[0] = L'⌕';
        value[1] = 0;
        centeringString(fieldsSearch[j], lengthOfStr + 1, value);
    }
    delete[] value;
    value = nullptr;

    outputRow(wSearch, fieldsSearch, 0, 99);
    outputTopOfTable(wSearch, 0);
    outputRow(wSort, names, 0, 99);
    for (int i = 0; i < countColumns; i++) {
        delete[] fieldsSearch[i];
        fieldsSearch[i] = nullptr;
    }
    delete[] fieldsSearch;
    fieldsSearch = nullptr;


    auto ***fieldsValues = getDataByIndex(0);

    for (int i = 0; i < 11; i++) {
        outputRow(wTable, fieldsValues[i], i * 2, 99);
        for (int j = 0; j < countColumns; j++) {
            delete[] fieldsValues[i][j];
            fieldsValues[i][j] = nullptr;
        }
        delete[] fieldsValues[i];
        fieldsValues[i] = nullptr;
    }
    delete[] fieldsValues;
    fieldsValues = nullptr;


    int y = getcury(wTable);
    outputBottomOfTable(wTable, y + 1);

    selectMenu();
    wrefresh(wMenu);
    wrefresh(wSearch);
    wrefresh(wSort);
    wrefresh(wTable);

}

template<typename T>
int Table<T>::readListFromFile() {
    std::ifstream in = std::ifstream(filename, ::ios::binary);
    if (!in) {
        ofstream newFile = std::ofstream(filename, ::ios::binary);
        newFile.close();
        in = std::ifstream(filename, ::ios::binary);
    }
    if (!in) {
        throw std::ifstream::failure("Can't open file");
    }
    in.seekg(0, std::ios_base::end);
    long long countElements = in.tellg() / sizeof(T);
    in.seekg(0, std::ios_base::beg);
    in.clear();
    long sizeT = sizeof(T);
    for (long long i = 0; i < countElements; i++) {
        T element;
        in.read((char *) &element, sizeT);
        Node<T> *node = list.pushBack(element);
        rows.pushBack(node);
    }
    in.close();
    return 0;
}

template<typename T>
int Table<T>::writeListToFile() {
    std::ofstream out(filename, ::ios::binary | ::ios::out);
    if (!out) throw std::ifstream::failure("Can't open file");
    Node<T> *node = list.getHead();
    long sizeT = sizeof(T);
    while (node != nullptr) {
        T t = node->getData();
        out.write((char *) &t, sizeT);
        node = node->next;
    }

    out.close();
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
Table<T>::Table(
        char *filename,
        const wchar_t *nameOfColumns,
        unsigned char countColumns,
        const char *types) {
    ::setlocale(LC_ALL, "");

    size_t countChars = ::strlen(filename) + 1;
    this->filename = new char[countChars];
    std::strncpy(this->filename, filename, countChars);

    countChars = ::wcslen(nameOfColumns) + 1;

    this->nameOfColumns = new wchar_t[countChars];
    std::wcsncpy(this->nameOfColumns, nameOfColumns, countChars);

    this->countColumns = countColumns + 1;
    splitNames();

}


#endif //MAIN_CPP_TABLE_HPP
