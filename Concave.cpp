#include "Concave.h"

Concave::Concave(Axis primaryAxis, unsigned int primaryCoord, unsigned int crossCoord, Direction dir){
	Axis crossAxis = (primaryAxis == XAXIS) ? YAXIS : XAXIS;
	this->coords[primaryAxis] = primaryCoord;
	this->coords[crossAxis] = crossCoord;
	this->rightEdge = dir;
}

unsigned int Concave::getCoord(Axis a){
	return this->coords[a];
}

Direction Concave::getRightEdge(){
	return this->rightEdge;
}
