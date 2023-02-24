#include "polygon.h"
#include "memory.h"

polygon::polygon()
{
    this->numberOfVertex=0;
    this->vertex=nullptr;
}

///конструктор с параметром
polygon::polygon(unsigned int numberOfVertex)
{
    this->numberOfVertex=numberOfVertex;
    this->vertex = new point[numberOfVertex];
}

polygon::polygon(const polygon &src)
{
    this->numberOfVertex = src.numberOfVertex;
    this->vertex = new point[this->numberOfVertex];
    memcpy(this->vertex,src.vertex,sizeof(point)*this->numberOfVertex);
}

polygon::~polygon()
{
    this->numberOfVertex=0;
    delete[] this->vertex;
}

unsigned int polygon::getNumberOfVertex()
{
    return this->numberOfVertex;
}

bool polygon::setNumberOfVertex(unsigned int newNumberOfVertex)
{
    point *ptr = new point[newNumberOfVertex];
    if(ptr==nullptr)
        return false;
    delete[] this->vertex;
    this->numberOfVertex = newNumberOfVertex;
    this->vertex = ptr;//динамическая память не имеет области видимости
}

ostream& operator<< (ostream &out, const polygon &output)
{
    // Поскольку operator<< является другом класса polygon, то мы имеем прямой доступ к членам polygon
    out<<"Number of vertex polygon "<<output.numberOfVertex<<endl;
    for (int i=0;i<output.numberOfVertex;i++)
    {
        out<<"vertex number "<<i+1<<" is pos X "<<output.vertex[i].x<<" Y "<<output.vertex[i].y<<endl;
    }
    return out;
}



//так как я считаю что объект уже точно есть и всё с ним будет понятно
istream& operator>> (istream &in, polygon &input)
{
    // Поскольку operator>> является другом класса polygon, то мы имеем прямой доступ к членам polygon.
    // Обратите внимание, параметр input (объект класса polygon) должен быть неконстантным, чтобы мы имели возможность изменить члены класса
    cout<<"enter "<< input.numberOfVertex <<" vertex"<<endl;
    for (unsigned int i=0;i<input.numberOfVertex;i++)
    {
        cout<<"enter pos X vertex of["<<i+1<<"/"<<input.numberOfVertex<<"] ";
        in >>input.vertex[i].x;
        cout<<"enter pos Y vertex of["<<i+1<<"/"<<input.numberOfVertex<<"] ";
        in >>input.vertex[i].y;
    }

    return in;
}

double operator+ (const polygon& input)
{
    cout<<"read this"<<endl<<"https://gospodaretsva.com/urok-34-ploshhad-mnogougolnika-2.html"<<endl;
    return 0.0;
}

const polygon operator++(polygon& input)
{
    for (unsigned int i=0;i<input.numberOfVertex;i++)
    {
        input.vertex[i].x++;
        input.vertex[i].y++;
    }
    return input;
}


const polygon operator+(const polygon& left, const polygon& right)
{
    unsigned int min = left.numberOfVertex>right.numberOfVertex?right.numberOfVertex:left.numberOfVertex;

    polygon newPoligon(min);

    for(unsigned int i=0;i<min;i++)
    {
        newPoligon.vertex[i].x = left.vertex[i].x+right.vertex[i].x;
        newPoligon.vertex[i].y = left.vertex[i].y+right.vertex[i].y;
    }

    return newPoligon;
}

polygon::operator float()
{
    return this->numberOfVertex/7.;
}
