#include "Functions.h"

//Sorts through recursive quick sort
void sort(Polygon *toSort, int start, int end, Polygon &location)
{
	if (start < end)
	{
		//Partitioning the vector and gets the pivot point (p)
		int p = partition(toSort, start, end, location);

		//Separately sort elements before pivot point and after pivot point 
		sort(toSort, start, p - 1, location);
		sort(toSort, p + 1, end, location);
	}
}

int partition(Polygon *polygons, int start, int end, Polygon &location)
{
	//Take start element to pivot
	int pivotValue = polygons[start].distance(&location);
	//Index of pivot element
	int pivotPosition = start;

	//Rearrange the rest of the vectors elements.
	for (int i = start + 1; i <= end; i++)
	{
		if(polygons[i].distance(&location) < pivotValue)
		{
			//Swap current object in polygons with object to the right of pivot
			Polygon tempPoly;
            tempPoly = polygons[pivotPosition + 1];
			polygons[pivotPosition + 1] = polygons[i];
			polygons[i] = tempPoly;

			//Swap the current (at position "pivotPosition + 1") item with the pivot element
			tempPoly = polygons[pivotPosition];
			polygons[pivotPosition] = polygons[pivotPosition + 1];
			polygons[pivotPosition + 1] = tempPoly;
			//Adjust pivotPosition
			pivotPosition++;
		}
	}
	return pivotPosition;
} 