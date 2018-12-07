#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <string>
#include "Shape.h"

class Triangle : public Shape
{
    private:
    public:
        Triangle(Position *pPos, int numPositions);     //Triangle constructor
     
        ~Triangle();                                                      //Triangle destructor

        double area();

        double circumreference();
};

#endif