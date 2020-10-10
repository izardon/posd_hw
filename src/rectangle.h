#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>
#include <sstream>
#include "shape.h"

using namespace std;

class Rectangle : public Shape {
public:
Rectangle(std::string id, double length, double width) :
        Shape (id), _length (length), _width (width)
{
        if ((_length < 1) || (_width < 1)) {
                throw string ("This is not a rectangle!");
        }
}

Rectangle(std::string id, double length, double width, string color) :
        Shape (id, color), _length (length), _width (width)
{
        if ((_length < 1) || (_width < 1)) {
                throw string ("This is not a rectangle!");
        }
}

double area () const
{
        return(_length * _width);
}

double perimeter () const
{
        return((_length + _width) * 2);
}

string info () const
{
        ostringstream stream;

        stream << "Rectangle (" << fixed << setprecision (3) << _length << ", " << _width << ")";

        return(stream.str ());
}

private:
double _length, _width;
};

#endif
