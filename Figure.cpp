#include <iostream>
#include "Figure.h"

Figure::Figure(Shape *sPtr, int numberOfShapes)
{
    this->numberOfShapes = numberOfShapes;
    capacity = numberOfShapes;
    
    shapePtr = new Polygon[capacity];
    for(int i = 0; i < numberOfShapes; i++)
    {
        shapePtr[i] = sPtr[i];
    }
}

Figure::~Figure()
{
    if(shapePtr)
    {
        delete[] shapePtr;
        shapePtr = nullptr;
    }
}

void Figure::addShape(const Shape &shape)
{
    if(numberOfShapes >= capacity)
    {
        capacity += 1;
        Shape *tempPtr = new Polygon[capacity];
        for(int i = 0; i < numberOfShapes; i++)
        {
            tempPtr[i] = shapePtr[i];
        }
        delete[] shapePtr;
        shapePtr = tempPtr;
        tempPtr = nullptr;
    }
    shapePtr[numberOfShapes] = shape;
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
        int numberOfPositions = shapePtr[i].getNrOfPositions();
        Position *tempPositionPtr = new Position[numberOfPositions];
        //Get positions of current polygon
        shapePtr[i].getPositions(tempPositionPtr);
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

//This is for printing the types of the shapes (polygons) stored in "Figure".
std::ostream &operator<<(std::ostream &out, const Figure &figure)
{
    //Print type
    for(int i = 0; i < figure.numberOfShapes; i++)
    {
        out << figure.shapePtr[i].getType() << "\n";
    }
    return out;   
}