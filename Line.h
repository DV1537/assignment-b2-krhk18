#ifndef LINE_H
#define LINE_H
#include <string>
#include "Shape.h"

class Line : public Shape
{
    private:
    public:
        Line(Position *pPos, int numPositions);      //Line constructor

        ~Line();        //Line destructor
    
        double area();      //returns area of the object     

        double circumreference();       //returns circumreference of the object (interpreted as the length of the line)
};

#endif