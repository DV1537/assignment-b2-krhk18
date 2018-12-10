#include <iostream>
#include "Figure.h"

Figure::Figure(Polygon *pPtr, int numberOfShapes)
{
    this->numberOfShapes = numberOfShapes;
    capacity = numberOfShapes;
    
    polygonPtr = new Polygon[capacity];    //Since the program is only making polygons, and no other shapes will be created, I have assumed it is OK to make polygonPtr point to Polygons.
    for(int i = 0; i < numberOfShapes; i++)
    {
        polygonPtr[i] = pPtr[i];
    }
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

Position* Figure::getBoundingBox()
{
    //Find the point with the min x value.
    //Find the point with the max x value.
    //Find the point with the min y value.
    //Find the point with the max y value.

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
        for(int t = 0; t < numberOfPositions; t++)
            std::cout << "X: " << tempPositionPtr[t].xCoord << ", Y: " << tempPositionPtr[t].yCoord << std::endl;
        std::cout << "------------\n";

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
        std::cout << "Max so far: " << "X: " << xMax << ", Y: " << yMax << std::endl;
        std::cout << "Min so far: " << "X: " << xMin << ", Y: " << yMin << std::endl;
        
        //Free memory
        delete []tempPositionPtr;
        tempPositionPtr = nullptr;
    }
    std::cout << "Total max: " << "X: " << xMax << ", Y: " << yMax << std::endl;
    std::cout << "Total min: " << "X: " << xMin << ", Y: " << yMin << std::endl;

    //Make position top left corner (xMin, yMax) and bottom right corner (xMax, yMin)
    Position topLeft(xMin, yMax);
    std::cout << "Position top left: " << "X: " << topLeft.xCoord << ", Y: " << topLeft.yCoord << std::endl;
    Position bottomRight(xMax, yMin);
    std::cout << "Position bottom right: " << "X: " << bottomRight.xCoord << ", Y: " << bottomRight.yCoord << std::endl;
    
    Position *cornerPtr = new Position[2];
    cornerPtr[0] = topLeft;
    cornerPtr[1] = bottomRight;

    return cornerPtr;
}

Polygon *Figure::getClosest(Polygon &location, int n) //returns n closest shapes to the location. Make sure that a Shape can be x,y coordinates as well, i.e. a point
{
    //1. Sort polygonPtr med avseende på distance to location
    //2. Dynamically allocate array of n shapes (polygons)
    //3. Save n first polygons in the array
    //4. Return the array.

    //Sort
    bool swapped;
    do
    {
        swapped = false;
        for(int i = 0; i < numberOfShapes - 1; i++)
        {
            double distanceCurrent = polygonPtr[i].distance(&location);
            double distanceNext = polygonPtr[i + 1].distance(&location);
            if(distanceNext < distanceCurrent)
            {
                Polygon tempPoly = polygonPtr[i];
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

//This is for printing the types of the shapes (polygons) stored in "Figure".
std::ostream &operator<<(std::ostream &out, const Figure &figure)
{
    //Print type
    for(int i = 0; i < figure.numberOfShapes; i++)
    {
        out << figure.polygonPtr[i].getType() << "\n";
    }
    return out;   
}