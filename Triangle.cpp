#include "Triangle.h"

Triangle::Triangle(Position *pPos, int numPositions)
{
    type = "Triangle";
    nrOfPositions = numPositions;
    posPtr = new Position[numPositions];
    for(int i = 0; i < numPositions; i++)
    {
        posPtr[i] = pPos[i];
    }
}

Triangle::~Triangle()
{
    if(posPtr)
    {
        delete[] posPtr;
        posPtr = nullptr;
    }
}

double Triangle::area()     
{
    double area = 0.0;
    int j = nrOfPositions - 1; 
    for (int i = 0; i < nrOfPositions; i++)
    { 
        area += (posPtr[j].xCoord + posPtr[i].xCoord) * (posPtr[j].yCoord - posPtr[i].yCoord); 
        j = i;
    }
    area = fabs(area / 2.0);
    
    if(area == 0)
    {
        area = -1;
    }
    
    return area;
}

//Calculates circumference by using pythagoras
double Triangle::circumreference()
{
    double circumference = 0.0;
    int j = nrOfPositions - 1;                  //Make j last position
    for(int i = 0; i < nrOfPositions; i++)      //Loop the triangle. First loop i = first position, and j = last position. Second loop i = secondpostion, and j = first position. And so on.
    {
        circumference += sqrt(pow((posPtr[i].xCoord - posPtr[j].xCoord), 2) + pow((posPtr[i].yCoord - posPtr[j].yCoord), 2));   //add the length of the line between the two current positions (length calculated by using pythagoras)
        j = i;      //move j forward to position of i (that is one ahead)
    }
    return circumference;
}