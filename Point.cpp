#include "Point.h"

Point::Point(Axis primaryAxis, unsigned int primaryCoord, unsigned int crossCoord){
	Axis crossAxis = (primaryAxis == XAXIS) ? YAXIS : XAXIS;
	this->coords[primaryAxis] = primaryCoord;
	this->coords[crossAxis] = crossCoord;
	//std::cout << "a1: " << a1 << " val1: " << val1 << " a2: " << " val2: " << val2 << std::endl;
}

unsigned int Point::getCoord(Axis a){
	return this->coords[a];
}

bool Point::equals(Point * that){
	return ((this->coords[XAXIS] == that->getCoord(XAXIS)) && (this->coords[YAXIS] == that->getCoord(YAXIS)));
}
