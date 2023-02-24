#ifndef TERM_2_DATAUNION_HPP
#define TERM_2_DATAUNION_HPP

template<typename T>
union DataUnion {
public:
    T data;
    T *ptrData;

    DataUnion(T data);

    DataUnion(T *data);
};

template<typename T>
DataUnion<T>::DataUnion(T data) {
    this->data = data;
}

template<typename T>
DataUnion<T>::DataUnion(T *data) {
    this->ptrData = data;
}


#endif //TERM_2_DATAUNION_HPP
