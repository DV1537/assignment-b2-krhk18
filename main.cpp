#include <iostream>
#include <fstream>
#include <sstream>
#include "Position.h"
#include "Shape.h"
#include "Point.h"
#include "Line.h"
#include "Triangle.h"
#include "Polygon.h"
#include "Figure.h"

/*
See comment in B1. I have read in the shapes and stored them,
not using "addShape" when I created a Figure.

Here in B2 (different from B1) I am only using the shapes presented in the file,
to find out the closest shapes.
*/

int main(int argc, const char * argv[])
{
    int capacityNumbers = 1;
    double *numbersPtr = new double[capacityNumbers];
    Position *positionPtr = nullptr;
    std::string type = "";
    std::ifstream inputFile;
    std::stringstream myStringStream;
    std::string line;
    int numberOfCoordinates = 0;
    int numberOfElements;
    int capacityPolygons = 1;
    Polygon *polygonPtr = new Polygon[capacityPolygons];
    int numberOfShapes;

    inputFile.open(argv[1]);

    //Check if file reads in successfully
    if(!inputFile)
    {
        std::cout << "Error opening file\n";
        exit(EXIT_FAILURE);
    }
    else
    {
        //Read in file
        while(!inputFile.eof())
        {
            //Read one line into a string
            myStringStream.clear();
            std::getline(inputFile, line);
            myStringStream << line;

            //read each element in the string and store in numbersPtr (+ count number of elements)
            while(myStringStream >> numbersPtr[numberOfElements])           //Read in and store
            {           
                numberOfElements++;
                if(numberOfElements >= capacityNumbers)       //If full: expand
                {
                    capacityNumbers += 1;
                    double *tempPtr = new double[capacityNumbers];  //Create new, bigger
                    for(int i = 0; i < capacityNumbers - 1; i++)      //move
                    {
                        tempPtr[i] = numbersPtr[i];
                    }
                    delete []numbersPtr;                //delete old content
                    numbersPtr = tempPtr;               //make pointer point to new array
                    tempPtr = nullptr;
                }
            }

            //Check if line is empty, contains non-numberical values or has an odd number of values
            if(numberOfElements == 0 || !myStringStream.eof())
            {
                std::cout << "Line number " << numberOfShapes + 1 << " is empty or contains non-numerical values\n";
                exit(EXIT_FAILURE);
            }
            else if(numberOfElements % 2 == 1)
            {
                std::cout << "Line number " << numberOfShapes + 1 << " contains an odd number of values\n";
                exit(EXIT_FAILURE);
            }
            else
            {
                //Store numbers as positions (x, y) in positionPtr
                numberOfCoordinates = numberOfElements / 2;
                positionPtr = new Position[numberOfCoordinates];
                for(int i = 0; i < numberOfCoordinates; i++)
                {
                    positionPtr[i].xCoord = numbersPtr[2 * i];
                    positionPtr[i].yCoord = numbersPtr[2 * i + 1];
                }

                //Create polygon object
                Polygon myPolygonObject(positionPtr, numberOfCoordinates);

                //Store polygon object in polygonPtr (by first increasing the size if needed)
                if(numberOfShapes >= capacityPolygons)
                {
                    capacityPolygons += 1;
                    Polygon *tempPtr = new Polygon[capacityPolygons];  //Create new, bigger
                    for(int i = 0; i < capacityPolygons - 1; i++)      //move
                    {
                        tempPtr[i] = polygonPtr[i];
                    }
                    delete []polygonPtr;                //delete old content
                    polygonPtr = tempPtr;               //make pointer point to new array
                    tempPtr = nullptr;
                }
                polygonPtr[numberOfShapes] = myPolygonObject;
                numberOfShapes++;

                numberOfElements = 0;
            }
            //Start over with next line in file
        }
    }

    inputFile.close();

    //Create Figure
    Figure myFigure(polygonPtr, numberOfShapes);

    //Call getClosest and store returned pointer to polygons
    Polygon *closestPtr;
    closestPtr = myFigure.getClosest(polygonPtr[0], 3);

    //Round to 3 decimal digits and print 3 closest shapes
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < closestPtr[i].getNrOfPositions(); j++)
        {
            int sizeOfPolygon = closestPtr[i].getNrOfPositions();
            Position *tempPositions = new Position[sizeOfPolygon];
            closestPtr[i].getPositions(tempPositions);
            double xCoord = roundf(tempPositions[j].xCoord * 1000) / 1000;
            double yCoord = roundf(tempPositions[j].yCoord * 1000) / 1000;
            std::cout << xCoord << " " << yCoord << " ";

            delete []tempPositions;
            tempPositions = nullptr;
        }
        std::cout << "\n";
    }

    //Free memory
    delete []numbersPtr;
    numbersPtr = nullptr;
    
    delete []positionPtr;
    positionPtr = nullptr;
    
    delete []polygonPtr;
    polygonPtr = nullptr;

    //Pause program
    std::getchar();

    return 0;
}