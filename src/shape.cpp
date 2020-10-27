#include "shape.h"
#include "iterator.h"
#include "null_iterator.h"

using namespace std;

Shape::Shape(string id) : _id (id)
{
        _color = "white";
}

Shape::Shape(string id, string color) : _id (id), _color (color)
{
}

Iterator* Shape::createIterator () const
{
        return new NullIterator ();
}


string Shape::id () const
{
        return Shape::_id;
};

string Shape::color () const
{
        return Shape::_color;
};

void Shape::addShape (Shape *shape)
{
        throw string ("Only compound shape can add shape!");
}

void Shape::deleteShapeById (std::string id)
{
        throw string ("Only compound shape can delete shape!");
}

Shape* Shape::getShapeById (std::string id) const
{
        throw string ("Only compound shape can get shape!");
}

Shape::~Shape()
{
}
