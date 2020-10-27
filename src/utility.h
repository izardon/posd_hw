#ifndef UTILITY_H
#define UTILITY_H

#include <deque>
#include "shape.h"
#include "rectangle.h"

Shape* getShapeById(Shape* shape, std::string id) {
        Iterator* it = shape->createIterator();
        if(it->isDone()) {
                throw string ("Only compound shape can get shape!");
        }
        for(it; !it->isDone(); it->next()) {
                if(it->currentItem()->id().compare(id) == 0) {
                        return it->currentItem();
                }
                try {
                        Shape * findShape = getShapeById(it->currentItem(), id);
                        if(findShape) {
                                return findShape;
                        }
                } catch (string e) {

                }
        }
        throw string ("Expected get shape but shape not found");
}

template <class Filter>
std::deque<Shape*> filterShape(Shape* shape, Filter filter){
        std::deque<Shape* > shapesQue;
        Iterator* it = shape->createIterator();
        if(it->isDone()) {
                throw string ("Only compound shape can filter shape!");
        }
        for(it; !it->isDone(); it->next()) {
                if(filter(it->currentItem())) {
                        shapesQue.push_back(it->currentItem());
                }
                try {
                        filterShape<Filter> (it->currentItem(), filter);
                        std::deque<Shape* > subShapesQue = filterShape<Filter> (it->currentItem(), filter);
                        for (auto &sub : subShapesQue) {
                                shapesQue.push_back(sub);
                        }
                } catch (string e) {
                }
        }
        return shapesQue;
}

class AreaFilter {
public:
        AreaFilter(double upperBound, double lowerBound) : _upperBound(upperBound), _lowerBound(lowerBound){
        }
        bool operator() (Shape* shape) const {
                return (shape->area() <= _upperBound && shape->area() >= _lowerBound);
        }
private:
        double _upperBound, _lowerBound;
};

class PerimeterFilter {
public:
        PerimeterFilter(double upperBound, double lowerBound) : _upperBound(upperBound), _lowerBound(lowerBound){
        }
        bool operator() (Shape* shape) const {
                return (shape->perimeter() <= _upperBound && shape->perimeter() >= _lowerBound);
        }
private:
        double _upperBound, _lowerBound;
};

class ColorFilter {
public:
        ColorFilter(std::string color) : _color(color) {
        }
        bool operator() (Shape* shape) const {
                return (shape->color().compare(_color) == 0);
        }
private:
        std::string _color;
};

class TypeFilter {
public:
        TypeFilter(std::string type) : _type(type) {
        }
        bool operator() (Shape* shape) const {
                return (shape->type().compare(_type) == 0);
        }
private:
        std::string _type;
};

#endif
