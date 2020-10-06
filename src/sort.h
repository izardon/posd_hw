#ifndef SORT_H
#define SORT_H

using namespace std;

template<class RandomAccessIterator, class Compare>
void quickSort(RandomAccessIterator first, RandomAccessIterator last,
                Compare comp)
{
    last = last - 1;
    RandomAccessIterator stack[last - first + 1];

    int top = -1;

    stack[++top] = first;
    stack[++top] = last;

    while (top >= 0) {
        last = stack[top--];
        first = stack[top--];

        RandomAccessIterator pivot = __partition(first, last, comp);

        if (pivot - 1 > first) {
            stack[++top] = first;
            stack[++top] = pivot - 1;
        }

        if (pivot + 1 < last) {
            stack[++top] = pivot + 1;
            stack[++top] = last;
        }
    }
}

template<class RandomAccessIterator, class Compare>
RandomAccessIterator __partition (RandomAccessIterator first, RandomAccessIterator last,
                                  Compare comp){

        RandomAccessIterator pivot = last;
        RandomAccessIterator i = first;

        for(RandomAccessIterator j = first; j < last; j++) {
                if(comp(*j, *pivot)) {
                        __swap(*i, *j);
                        i++;
                }
        }
        __swap(*i, *last);
        return i;
}

template<class RandomAccessIterator>
void __swap(RandomAccessIterator& a, RandomAccessIterator& b) {
        RandomAccessIterator t = a;
        a = b;
        b = t;
}

bool areaAscendingCompare (Shape *a, Shape *b)
{
        return a->area () < b->area ();
}

bool areaDescendingCompare (Shape *a, Shape *b)
{
        return a->area () > b->area ();
}

bool perimeterAscendingCompare (Shape *a, Shape *b)
{
        return a->perimeter () < b->perimeter ();
}

bool perimeterDescendingCompare (Shape *a, Shape *b)
{
        return a->perimeter () > b->perimeter ();
}

class AscendingCompare {
public:
        AscendingCompare(string feature) : _feature (feature)
        {
        }

        bool operator()(Shape * a, Shape * b) {
                if(_feature == "area") {
                        return a->area() < b->area();
                } else if (_feature == "perimeter") {
                        return a->perimeter() < b->perimeter();
                } else {
                        throw string ("Feature is invalid!");
                }
        }
private:
        string _feature;
};

class DescendingCompare {
public:
        DescendingCompare(string feature) : _feature (feature)
        {
        }

        bool operator()(Shape * a, Shape * b) {
                if(_feature == "area") {
                        return a->area() > b->area();
                } else if (_feature == "perimeter") {
                        return a->perimeter() > b->perimeter();
                } else {
                        throw string ("Feature is invalid!");
                }
        }
private:
        string _feature;
};

#endif
