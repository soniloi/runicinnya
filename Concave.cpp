#include "Concave.h"

Concave::Concave(Axis primaryAxis, unsigned int val1, unsigned int val2, Direction dir){
	Axis crossAxis = (primaryAxis == XAXIS) ? YAXIS : XAXIS;
	this->coords[primaryAxis] = val1;
	this->coords[crossAxis] = val2;
	this->rightEdge = dir;
}

unsigned int Concave::getCoord(Axis a){
	return this->coords[a];
}

Direction Concave::getRightEdge(){
	return this->rightEdge;
}
