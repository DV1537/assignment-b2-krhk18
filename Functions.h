#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "Figure.h"

void sort(Polygon *toSort, int start, int end, Polygon &location);

int partition(Polygon *polygons, int start, int end, Polygon &location);

#endif