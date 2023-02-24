#ifndef TERM_2_DATA_HPP
#define TERM_2_DATA_HPP

#include "iostream"

#include "../unions/DataUnion.hpp"

template<typename T>
class Data {
private:
    char _unionType;
    DataUnion<T> data;
public:
    Data();

    Data(T data);

    Data(T *data);

    T getData();

    int editData(T data);

    int editData(T *data);


};

template<typename T>
Data<T>::Data() {
    _unionType = 0;
    data = Data<T>(nullptr);
}

template<typename T>
Data<T>::Data(T data): data(data) {
    _unionType = 0;
}

template<typename T>
Data<T>::Data(T *data): data(data) {
    _unionType = 1;
}

template<typename T>
T Data<T>::getData() {
    if (_unionType) return *(data.ptrData);
    return data.data;
}

template<typename T>
int Data<T>::editData(T data) {
    try {
        if (_unionType) *(this->data.ptrData) = data;
        else this->data.data = data;
    }
    catch (std::exception &ex) { return 0; }
}

template<typename T>
int Data<T>::editData(T *data) {
    if (_unionType) {
        this->data.ptrData = data;
        return 0;
    } else {
        throw std::invalid_argument("Can't change address to value");
    }
}

#endif //TERM_2_DATA_HPP
