#include <iostream>
#include "Figure.h"
#include "Functions.h"

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

void Figure::addShape(Polygon *polygon)
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
    polygonPtr[numberOfShapes] = *polygon;
    numberOfShapes++;
}

Polygon Figure::getFirstPolygon()
{
    return polygonPtr[0];
}

// Gets boundingbox top left and bottom right positions
BoundingBox Figure::getTotalBoundingBox()
{
	double xMin = 0.0;
	double yMin = 0.0;
	double xMax = 0.0;
	double yMax = 0.0;

	//Loop through Polygons in the Figure.
	for (int i = 0; i < numberOfShapes; i++)
	{
		BoundingBox boundingBox;
		boundingBox = polygonPtr[i].getBoundingBox();

		if (boundingBox.topLeft.xCoord < xMin)
		{
			xMin = boundingBox.topLeft.xCoord;    //xMin
		}
		if (boundingBox.topLeft.yCoord > yMax)
		{
			yMax = boundingBox.topLeft.yCoord;    //yMax
		}
		if (boundingBox.bottomRight.xCoord > xMax)
		{
			xMax = boundingBox.bottomRight.xCoord;     //xMax 
		}
		if (boundingBox.bottomRight.yCoord < yMin)
		{
			boundingBox.bottomRight.yCoord;           //yMin
		}
	}

	//Make position top left corner (xMin, yMax) and bottom right corner (xMax, yMin)
	Position topLeft(xMin, yMax);
	Position bottomRight(xMax, yMin);

	BoundingBox boundingBox;
	boundingBox.topLeft = topLeft;
	boundingBox.bottomRight = bottomRight;

	return boundingBox;
}

//Returns n closest shapes to the location.
void Figure::getClosest(Polygon *closestPolygons, Polygon &location, int n)
{
	//Sort med avseende på distance to location
    sort(polygonPtr, 0, numberOfShapes - 1, location);

    //Save the n closest shapes (polygons) in "closestPolygons".
    //Polygon *closestPtr = new Polygon[n];
    for(int i = 0; i < n; i++)
    {
        closestPolygons[i] = polygonPtr[i + 1];
    }
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