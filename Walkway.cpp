#include "Walkway.h"

Walkway::Walkway(Direction dir, Court * c1, Court * c2, unsigned int le){
	this->direction = dir;
	this->court1 = c1;
	this->court2 = c2;
	this->leftEdge = le;
	std::cout << "Creating connecting walkway between courts " << c1->getIndex() << " and " << c2->getIndex() << " in direction: " << this->direction << " at coord " << this->leftEdge << std::endl;
}

void toFile(std::ostream &file){
	/*
	 TODO: after static maps have been refactored
	 get the directions to the left and right of this->direction
	 get the edges of the courts in the appropriate directions
	*/
}
