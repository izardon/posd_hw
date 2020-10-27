#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"
#include "two_dimensional_coordinate.h"

using namespace std;

class Triangle : public Shape {
public:
Triangle(string id, vector<TwoDimensionalCoordinate *> vectors) : Shape (id)
{
        if (vectors.size () != 3) {
                throw string ("This is not a triangle!");
        }

        _vectors.assign (vectors.begin (), vectors.end ());
        _a = sqrt (pow ((vectors.at (0)->getX () - vectors.at (1)->getX ()), 2) + pow ((vectors.at (0)->getY () - vectors.at (1)->getY ()), 2));
        _b = sqrt (pow ((vectors.at (0)->getX () - vectors.at (2)->getX ()), 2) + pow ((vectors.at (0)->getY () - vectors.at (2)->getY ()), 2));
        _c = sqrt (pow ((vectors.at (1)->getX () - vectors.at (2)->getX ()), 2) + pow ((vectors.at (1)->getY () - vectors.at (2)->getY ()), 2));

        if ((_a + _b <= _c) || (_b + _c <= _a) || (_a + _c <= _b)) {
                throw string ("This is not a triangle!");
        }
}

Triangle(string id, vector<TwoDimensionalCoordinate *> vectors, string color) : Shape (id, color)
{
        if (vectors.size () != 3) {
                throw string ("This is not a triangle!");
        }

        _vectors.assign (vectors.begin (), vectors.end ());
        _a = sqrt (pow ((vectors.at (0)->getX () - vectors.at (1)->getX ()), 2) + pow ((vectors.at (0)->getY () - vectors.at (1)->getY ()), 2));
        _b = sqrt (pow ((vectors.at (0)->getX () - vectors.at (2)->getX ()), 2) + pow ((vectors.at (0)->getY () - vectors.at (2)->getY ()), 2));
        _c = sqrt (pow ((vectors.at (1)->getX () - vectors.at (2)->getX ()), 2) + pow ((vectors.at (1)->getY () - vectors.at (2)->getY ()), 2));

        if ((_a + _b <= _c) || (_b + _c <= _a) || (_a + _c <= _b)) {
                throw string ("This is not a triangle!");
        }
}

double area () const
{
        double s = (_a + _b + _c) / 2;

        return(sqrt (s * (s - _a) * (s - _b) * (s - _c)));
}

double perimeter () const
{
        return(_a + _b + _c);
}

string info () const
{
        ostringstream stream;

        stream << "Triangle (";
        for (int i = 0; i < _vectors.size (); i++) {
                stream << "[" << fixed << setprecision (3) << _vectors.at (i)->getX () << ", " << _vectors.at (i)->getY () << "]";
                if (i != _vectors.size () - 1) {
                        stream << ", ";
                }
        }
        stream << ")";

        return(stream.str ());
}

string type () const
{
        return "Triangle";
}

private:
double _a, _b, _c;
vector<TwoDimensionalCoordinate *> _vectors;
};

#endif
