#ifndef FIGURE_H
#define FIGURE_H
#include <string>
#include <iostream>
#include "Polygon.h"

class Figure
{
    private:
        Polygon *polygonPtr;
        int numberOfShapes;
        int capacity;
    public:
        Figure();
        ~Figure();
        void addShape(const Polygon &polygon);
        Position* getBoundingBox();
        Polygon *getClosest(Polygon &location, int n);
        friend std::ostream &operator<<(std::ostream &out, const Figure &figure);
};

#endif