#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <iostream>
#include <sstream>
#include <math.h>
#include "shape.h"

using namespace std;

class Ellipse : public Shape {
public:
Ellipse(double semiMajorAxes, double semiMinorAxes)
{
        _semiMajorAxes = semiMajorAxes;
        _semiMinorAxes = semiMinorAxes;
        if ((semiMajorAxes < 1) || (semiMinorAxes < 1) || (semiMajorAxes < semiMinorAxes)) {
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


private:
double _semiMajorAxes, _semiMinorAxes;
};

#endif
