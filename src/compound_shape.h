#ifndef COMPOUND_SHAPE_H
#define COMPOUND_SHAPE_H

#include <vector>
#include "shape.h"

using namespace std;

class CompoundShape : public Shape {
public:
CompoundShape(string id, vector<Shape *> *shapes) : Shape (id, "transparent"), _shapes (shapes)
{
        if (shapes->size () == 0) {
                throw string ("This is not a compound shape!");
        }
}

double area () const
{
        double sum = 0;
        vector<Shape *>::iterator ptr;

        for (ptr = _shapes->begin (); ptr < _shapes->end (); ptr++) {
                sum += (*ptr)->area ();
        }
        return sum;
}

double perimeter () const
{
        double sum = 0;
        vector<Shape *>::iterator ptr;

        for (ptr = _shapes->begin (); ptr < _shapes->end (); ptr++) {
                sum += (*ptr)->perimeter ();
        }
        return sum;
}

string info () const
{
        ostringstream stream;
        vector<Shape *>::iterator ptr;

        stream << "Compound Shape {";

        for (ptr = _shapes->begin (); ptr < _shapes->end (); ptr++) {
                stream << (*ptr)->info ();

                if (ptr != (_shapes->end () - 1)) {
                        stream << ", ";
                }
        }

        stream << "}";

        return(stream.str ());
}

void addShape (Shape* shape)
{
        _shapes->push_back (shape);
}

void deleteShapeById (string id)
{
        try {
                getShapeById (id);
        } catch (string e) {
                throw string ("Expected delete shape but shape not found");
        }

        double oriPerimeter = perimeter ();
        vector<Shape *>::iterator ptr;

        for (ptr = _shapes->begin (); ptr < _shapes->end (); ptr++) {
                if (id.compare ((*ptr)->id ()) == 0) {
                        _shapes->erase (ptr);
                        break;
                }
                try {
                        (*ptr)->deleteShapeById (id);
                        if (oriPerimeter != perimeter ()) {
                                break;
                        }
                } catch (string e) {
                }
        }
}

Shape * getShapeById (string id)
{
        vector<Shape *>::iterator ptr;

        for (ptr = _shapes->begin (); ptr < _shapes->end (); ptr++) {
                if (id.compare ((*ptr)->id ()) == 0) {
                        return *ptr;
                }
                try {
                        return (*ptr)->getShapeById (id);
                } catch (string e) {
                }
        }
        throw string ("Expected get shape but shape not found");
}

private:
vector<Shape *> *_shapes;
};

#endif
