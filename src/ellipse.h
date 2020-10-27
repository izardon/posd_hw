#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <iostream>
#include <sstream>
#include <math.h>
#include "shape.h"

using namespace std;

class Ellipse : public Shape {
public:
Ellipse(string id, double semiMajorAxes, double semiMinorAxes) :
        Shape (id), _semiMajorAxes (semiMajorAxes), _semiMinorAxes (semiMinorAxes)
{
        if ((_semiMajorAxes < 1) || (_semiMinorAxes < 1) || (_semiMajorAxes < _semiMinorAxes)) {
                throw string ("This is not an ellipse!");
        }
}

Ellipse(string id, double semiMajorAxes, double semiMinorAxes, string color) :
        Shape (id, color), _semiMajorAxes (semiMajorAxes), _semiMinorAxes (semiMinorAxes)
{
        if ((_semiMajorAxes < 1) || (_semiMinorAxes < 1) || (_semiMajorAxes < _semiMinorAxes)) {
                throw string ("This is not an ellipse!");
        }
}


double area () const
{
        return(M_PI * _semiMajorAxes * _semiMinorAxes);
}


double perimeter () const
{
        return(2 * M_PI * _semiMinorAxes + 4 * (_semiMajorAxes - _semiMinorAxes));
}


string info () const
{
        ostringstream stream;

        stream << "Ellipse (" << fixed << setprecision (3) << _semiMajorAxes << ", " << _semiMinorAxes << ")";

        return(stream.str ());
}

string type () const
{
        return "Ellipse";
}

private:
double _semiMajorAxes, _semiMinorAxes;
};

#endif
