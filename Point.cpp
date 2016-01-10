#include "Point.h"

Point::Point(Axis a1, unsigned int val1, Axis a2, unsigned int val2){
	this->coords[a1] = val1;
	this->coords[a2] = val2;
	//std::cout << "a1: " << a1 << " val1: " << val1 << " a2: " << " val2: " << val2 << std::endl;
}

unsigned int Point::getCoord(Axis a){
	return this->coords[a];
}

bool Point::equals(Point * that){
	return ((this->coords[XAXIS] == that->getCoord(XAXIS)) && (this->coords[YAXIS] == that->getCoord(YAXIS)));
}
