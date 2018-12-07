#include "Line.h"

Line::Line(Position *pPos, int numPositions)
{
    type = "Line";
    nrOfPositions = numPositions;
    posPtr = new Position[numPositions];
    for(int i = 0; i < numPositions; i++)
    {
        posPtr[i] = pPos[i];
    }
}

Line::~Line()
{
    if(posPtr)
    {
        delete[] posPtr;
        posPtr = nullptr;
    }
}

double Line::area()
{
    double area = -1;
    return area;
}

//Circumference of a line is interpreted as the length of the line.
double Line::circumreference()
{
    double circumference = sqrt(pow((posPtr[0].xCoord - posPtr[1].xCoord), 2) + pow((posPtr[0].yCoord - posPtr[1].yCoord), 2));
    return circumference;
}