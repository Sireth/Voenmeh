#ifndef TERM_2_TRIANGLE_H
#define TERM_2_TRIANGLE_H


class Triangle {
private:
    double a, b, c;
public:
    Triangle();

    Triangle(double a, double b, double c);

    Triangle(const Triangle &triangle);

    ~Triangle();

    double getSmallestAngle() const;

    double *getSides();

    double *getAngleBisectors() const;

    double getPerimeter() const;

    void setSides(double s1, double s2, double s3);

    void outputSides() const;

    void inputSides();

    friend Triangle operator*= (Triangle& input,double x);
};


#endif //TERM_2_TRIANGLE_H
