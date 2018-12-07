#include "Shape.h"

void Shape::getPositions(Position *positionPtr) const
{
    for (int i = 0; i < nrOfPositions; i++)
    {
        positionPtr[i] = posPtr[i];
    }
}

//Returns mid position by adding x-coords and y-coord seperatley
//then devide the total by the number of positions.
Position Shape::position()
{
    Position midPosition;
    midPosition.xCoord = 0.0;
    midPosition.yCoord = 0.0;
    for(int i = 0; i < nrOfPositions ; i++)
    {
        midPosition.xCoord += posPtr[i].xCoord;
        midPosition.yCoord += posPtr[i].yCoord;
    }
    midPosition.xCoord /= nrOfPositions;
    midPosition.yCoord /= nrOfPositions;

    return midPosition;
}

//Shape is convex if all dot products are either positive or negative.
bool Shape::isConvex()
{
    bool isConvex = true;
    bool sign = true;     
    bool first = true;

    for(int i = 0; i < nrOfPositions; i++)
    {
        double v1x = posPtr[i].xCoord - posPtr[(i + 1) % nrOfPositions].xCoord;
        double v1y = posPtr[i].yCoord - posPtr[(i + 1) % nrOfPositions].yCoord;
        double v2x = posPtr[(i + 2) % nrOfPositions].xCoord - posPtr[(i + 1) % nrOfPositions].xCoord;
        double v2y = posPtr[(i + 2) % nrOfPositions].yCoord - posPtr[(i + 1) % nrOfPositions].yCoord;
        double dotProduct = ((v2x * v1y) - v2y * v1x);

        if(dotProduct != 0)
        {
            if(first)
            {
                if(dotProduct > 0)
                {
                    sign = false;
                    first = false;
                }
            }
            else
            {
                if(std::signbit(dotProduct) != sign)
                {
                    isConvex = false;
                }
            }
        }
    }
    return isConvex;
}

//Calculated by finding x- and y-values of both midpositions.
//Then using pythagoras to calculate the distance between them.
double Shape::distance(Shape *s)
{
    double xFirst = this->position().xCoord;
    double yFirst = this->position().yCoord;
    double xSecond = s->position().xCoord;
    double ySecond = s->position().yCoord;

    double distance = sqrt(pow((xFirst - xSecond), 2) + pow((yFirst - ySecond), 2));

    return distance;
}