#include <iostream>
#include "Figure.h"

Figure::Figure() : polygonPtr(nullptr), numberOfShapes(0), capacity(0)
{
}

Figure::~Figure()
{
    if(polygonPtr)
    {
        delete[] polygonPtr;
        polygonPtr = nullptr;
    }
}

void Figure::addShape(const Polygon &polygon)
{
    if(numberOfShapes >= capacity)
    {
        capacity += 1;
        Polygon *tempPtr = new Polygon[capacity];
        for(int i = 0; i < numberOfShapes; i++)
        {
            tempPtr[i] = polygonPtr[i];
        }
        delete[] polygonPtr;
        polygonPtr = tempPtr;
        tempPtr = nullptr;
    }
    polygonPtr[numberOfShapes] = polygon;
    numberOfShapes++;
}

/* Gets boundingbox top left and bottom right positions by
looping trough the polygons in the figure and comparing
the x- and y-coords to find the highest and lowest of each.
top left = (lowest x-coord, highest y-coord)
bottom right = (highest x-coord, lowest y-coord) */
Position* Figure::getBoundingBox()
{
    double xMin = 0.0;
    double yMin = 0.0;
    double xMax = 0.0;
    double yMax = 0.0;

    //Loop through Polygons in the Figure.
    for(int i = 0; i < numberOfShapes; i++)
    {
        //Create new pointer for positions in current polygon
        int numberOfPositions = polygonPtr[i].getNrOfPositions();
        Position *tempPositionPtr = new Position[numberOfPositions];
        //Get positions of current polygon
        polygonPtr[i].getPositions(tempPositionPtr);
        
        //Find min- and max- values of x and y
        if(i == 0)
        {
            xMin = xMax = tempPositionPtr[0].xCoord;
            yMin = yMax = tempPositionPtr[0].yCoord;
        }
        for(int j = 0; j < numberOfPositions; j++)
        {
            if(xMin > tempPositionPtr[j].xCoord)
            {
                xMin = tempPositionPtr[j].xCoord;
            }
            if(xMax < tempPositionPtr[j].xCoord)
            {
                xMax = tempPositionPtr[j].xCoord;
            }
            if(yMin > tempPositionPtr[j].yCoord)
            {
                yMin = tempPositionPtr[j].yCoord;
            }
            if(yMax < tempPositionPtr[j].yCoord)
            {
                yMax = tempPositionPtr[j].yCoord;
            }
        }
        
        //Free memory
        delete []tempPositionPtr;
        tempPositionPtr = nullptr;
    }
    
    //Make position top left corner (xMin, yMax) and bottom right corner (xMax, yMin)
    Position topLeft(xMin, yMax);
    Position bottomRight(xMax, yMin);
    
    Position *cornerPtr = new Position[2];
    cornerPtr[0] = topLeft;
    cornerPtr[1] = bottomRight;

    return cornerPtr;
}

//Returns n closest shapes to the location.
Polygon *Figure::getClosest(Polygon &location, int n)
{
    //1. Sort polygonPtr med avseende på distance to location
    //2. Dynamically allocate array of n shapes (polygons)
    //3. Save n first polygons in the array
    //4. Return the array.

    //Sort
    bool swapped;
    Polygon tempPoly;
    do
    {
        swapped = false;
        for(int i = 0; i < numberOfShapes - 1; i++)
        {
            double distanceCurrent = polygonPtr[i].distance(&location);
            double distanceNext = polygonPtr[i + 1].distance(&location);
            if(distanceNext < distanceCurrent)
            {
                tempPoly = polygonPtr[i];
                polygonPtr[i] = polygonPtr[i + 1];
                polygonPtr[i + 1] = tempPoly;
                swapped = true;
            }
        }
    }while(swapped);

    //Save the n closest shapes (polygons) in "closestPtr" (of size n) and return.
    Polygon *closestPtr = new Polygon[n];
    for(int i = 0; i < n; i++)
    {
        closestPtr[i] = polygonPtr[i + 1];
    }

    return closestPtr;

}

//This is for being able to print the types of the shapes (polygons) stored in "Figure".
//(Used for debugging)
std::ostream &operator<<(std::ostream &out, const Figure &figure)
{
    //Print type
    for(int i = 0; i < figure.numberOfShapes; i++)
    {
        out << figure.polygonPtr[i].getType() << "\n";
    }
    return out;   
}