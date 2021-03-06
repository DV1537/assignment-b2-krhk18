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

int main(int argc, const char * argv[])
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);



    int capacityNumbers = 1;
    double *numbersPtr = new double[capacityNumbers];
    Position *positionPtr = nullptr;
    std::ifstream inputFile;
    std::stringstream myStringStream;
    std::string line = "";
    int numberOfCoordinates = 0;
    int numberOfElements = 0;
    int numberOfShapes = 0;
    Figure myFigure;
    double xCoord, yCoord;
	Polygon firstPolygon;

    inputFile.open(argv[1]);

    //Check if file reads in successfully
    if(!inputFile)
    {
        std::cout << "Error opening file\n";
        std::cin.get();
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
                std::cin.get();
                exit(EXIT_FAILURE);
            }
            else if(numberOfElements % 2 == 1)
            {
                std::cout << "Line number " << numberOfShapes + 1 << " contains an odd number of values\n";
                std::cin.get();
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
				//Create pointer to polygon object
                Polygon *myPolygonObject = new Polygon(positionPtr, numberOfCoordinates);
				delete[]positionPtr;
				positionPtr = nullptr;
				
				//store if first;
				if (numberOfShapes == 0)
				{
					firstPolygon = *myPolygonObject;
				}

				//add to myFigure
                myFigure.addShape(myPolygonObject);

				//free
                delete myPolygonObject;
                myPolygonObject = nullptr;
                                
                numberOfShapes++;

                numberOfElements = 0;
            }
            //Start over with next line in file
        }
    }

    inputFile.close();

    //Call getClosest and store returned pointer to polygons
	const int n = 3;
	Polygon closestPolygons[n];
    //Polygon firstPolygon;
    //firstPolygon = myFigure.getFirstPolygon();
	myFigure.getClosest(closestPolygons, firstPolygon, n);

	for (int i = 0; i < n; i++)
	{
		std::cout << closestPolygons[i] << std::endl;
	}

    //Free memory
    delete []numbersPtr;

    //Pause program
    std::cin.get();

    return 0;
}