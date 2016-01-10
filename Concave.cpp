#include "Concave.h"

Concave::Concave(Axis a1, unsigned int val1, Axis a2, unsigned int val2, Direction dir){
	this->coords[a1] = val1;
	this->coords[a2] = val2;
	this->rightEdge = dir;
}

unsigned int Concave::getCoord(Axis a){
	return this->coords[a];
}

Direction Concave::getRightEdge(){
	return this->rightEdge;
}
