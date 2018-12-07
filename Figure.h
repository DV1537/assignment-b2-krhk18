#ifndef FIGURE_H
#define FIGURE_H
#include <string>
#include <iostream>
#include "Polygon.h"

class Figure
{
    private:
        Shape *shapePtr;
        int numberOfShapes;
        int capacity;
    public:
        Figure(Shape *shapePtr, int numberOfShapes);
        ~Figure();
        void addShape(const Shape &shape);
        Position* getBoundingBox();
        void getClosest(const Shape &location, int n);
        friend std::ostream &operator<<(std::ostream &out, const Figure &figure);
};

#endif