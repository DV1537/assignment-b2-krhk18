#include "Point.h"

Point::Point(Position *pPos, int numPositions)
{
    type = "Point";
    nrOfPositions = numPositions;
    posPtr = new Position[numPositions];
    for(int i = 0; i < numPositions; i++)
    {
        posPtr[i] = pPos[i];
    }
}

Point::~Point()
{
    if(posPtr)
    {
        delete[] posPtr;
        posPtr = nullptr;
    }
}

double Point::area()
{
    double area = -1;
    return area;
}

double Point::circumreference()
{
    double area = -1;
    return area;
}