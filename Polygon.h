#ifndef POLYGON_H
#define POLYGON_H
#include <string>
#include <iostream>
#include "Shape.h"

class Polygon : public Shape
{
    private:
    public:
        Polygon();

        Polygon(Position *pPos, int numPositions);      //Polygon constructor

        ~Polygon();     //Polygon destructor

        Polygon& operator=(const Polygon &polygon);

        friend Polygon operator+(const Polygon &polygonOne, const Polygon &polygonTwo);

        friend std::ostream &operator<<(std::ostream &out, const Polygon &polygon);

        double area();

        double circumreference();
};

#endif