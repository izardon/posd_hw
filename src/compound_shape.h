#ifndef COMPOUND_SHAPE_H
#define COMPOUND_SHAPE_H

#include <vector>
#include "shape.h"
// #include "null_iterator.h"
#include "shape_iterator.h"
#include "iterator.h"
#include <list>

using namespace std;

class CompoundShape : public Shape {
public:
CompoundShape(string id, std::list<Shape*> shapes) : Shape (id, "transparent"), _shapes (shapes)
{
        if (shapes.size () == 0) {
                throw string ("This is not a compound shape!");
        }
}

Iterator* createIterator () const
{
        return new ShapeIterator<std::list<Shape *>::const_iterator> (_shapes.begin (), _shapes.end ());
}


double area () const
{
        double sum = 0;
        std::list<Shape *>::const_iterator ptr;

        for (ptr = _shapes.begin (); ptr != _shapes.end (); ptr++) {
                sum += (*ptr)->area ();
        }
        return sum;
}

double perimeter () const
{
        double sum = 0;
        std::list<Shape *>::const_iterator ptr;

        for (ptr = _shapes.begin (); ptr != _shapes.end (); ptr++) {
                sum += (*ptr)->perimeter ();
        }
        return sum;
}

string info () const
{
        ostringstream stream;
        std::list<Shape *>::const_iterator ptr;

        stream << "Compound Shape {";

        for (ptr = _shapes.begin (); ptr != _shapes.end (); ptr++) {
                stream << (*ptr)->info ();

                if (std::distance (ptr, _shapes.end ()) > 1) {
                        stream << ", ";
                }
        }

        stream << "}";

        return stream.str ();
}

void addShape (Shape* shape)
{
        _shapes.push_back (shape);
}

void deleteShapeById (string id)
{
        double oriPerimeter = perimeter ();
        list<Shape *>::iterator ptr;

        for (ptr = _shapes.begin (); ptr != _shapes.end (); ptr++) {
                if (id.compare ((*ptr)->id ()) == 0) {
                        _shapes.erase (ptr);
                        return;
                }
                try {
                        (*ptr)->deleteShapeById (id);
                        if (oriPerimeter != perimeter ()) {
                                return;
                        }
                } catch (string e) {
                }
        }
        throw string ("Expected delete shape but shape not found");
}

Shape * getShapeById (string id) const
{
        list<Shape *>::const_iterator ptr;

        for (ptr = _shapes.begin (); ptr != _shapes.end (); ptr++) {
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

string type () const
{
        return "Compound Shape";
}

private:
std::list<Shape *> _shapes;
};

#endif
