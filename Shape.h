#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include <cmath>
#include "Position.h"

class Shape
{
    protected:
        int nrOfPositions;
        std::string type;
        Position *posPtr;
    public:
        std::string getType() const                     //returns a string denoting type of a shape (point, line, polygon ..)
        {
            return type;
        }

        int getNrOfPositions() const
        {
            return nrOfPositions;
        }

        void getPositions(Position *positionPtr) const;

        virtual double area() = 0;                      //returns area of the object, or -1 if the shape is concave, intersecting, or does not have an area

        virtual double circumreference() = 0;           //returns circumreference of the object  (returns length of line if line, or -1 if dot)

        Position position();                            //returns center coordinates of the object

        bool isConvex();                                //returns true if shape is convex

        double distance(Shape *s);                      //returns distance to the center of another shape
};

#endif