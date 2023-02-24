#ifndef POLYGON_H
#define POLYGON_H
#include "iostream"
using namespace std;

/**
*Использование union/struct/class на примере многоугольника
*/
///проводим анализ предметной области и приходим к выводу
///  что если не сказано иного то многоугольник весьма сподручно
/// представлять с помощью координат его вершин

///camelCaseName, альтернатива cebab-case-name

/*!
 Основное назначение - хранение координат вершин многоугольника
 */
struct point
{
    int x;
    int y;
};

///Описание класса "многоугольник"
/// количество вершин нам заранее не ясно поэтому будем считать что их число - динамическое
class polygon
{
    unsigned int numberOfVertex;
    point *vertex;
public:
    polygon();///конструктор по умолчанию
    polygon(unsigned int numberOfVertex=3);///конструктор с параметром
    polygon(const polygon &src);///конструктор копирования
    ~polygon();
    unsigned int getNumberOfVertex();
    bool setNumberOfVertex(unsigned int newNumberOfVertex);


    friend ostream& operator<< (ostream &out, const polygon &output);
    friend istream& operator>> (istream &in, polygon &input);


    friend double operator+ (const polygon& input);//вычисление площади

    friend const polygon operator++ (polygon& input);//увеличение многоугольника постфиксный -> A++


    friend const polygon operator+(const polygon& left, const polygon& right);

    operator float();
};
#endif // POLYGON_H
