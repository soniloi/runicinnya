#include "../../include/lotalanta/Walkway.h"

Walkway::Walkway(Direction dir, Court * c1, Court * c2, unsigned int le, bool isUp){
	this->direction = dir;
	this->court1 = c1;
	this->court2 = c2;
	this->leftEdge = le;
	this->up = isUp;
	//std::cout << "Creating connecting walkway between courts " << c1->getIndex() << " and " << c2->getIndex() << " in direction: " << this->direction << " at coord " << this->leftEdge << std::endl;
}

// FIXME: refactor to reduce repetition
void Walkway::toFile(std::ostream &file){
	Axis axis = DirectionMappings::getAxisOf(this->direction);

	float left = this->leftEdge;
	if(this->up)
		left -= WALKWAY_WIDTH;

	float xcoord, ycoord, width, height;
	float x1a, y1a, x2a, y2a;
	float x1b, y1b, x2b, y2b;

	if(axis == YAXIS) {
		unsigned int west = this->court1->getEdge(DirectionMappings::getLeftOf(this->direction));
		unsigned int east = this->court2->getEdge(DirectionMappings::getRightOf(this->direction));
		if(east < west){
			unsigned int temp = west;
			west = east;
			east = temp;
		}

		xcoord = west * SCALE_FACTOR;
		ycoord = left * SCALE_FACTOR;
		width = (east - west) * SCALE_FACTOR;
		height = (WALKWAY_WIDTH) * SCALE_FACTOR;

		x2a = xcoord + width;
		y2a = ycoord;
		x1b = xcoord;
		y1b = ycoord + height;
	}
	else{
		unsigned int north = this->court1->getEdge(DirectionMappings::getLeftOf(this->direction));
		unsigned int south = this->court2->getEdge(DirectionMappings::getRightOf(this->direction));
		if(south < north){
			unsigned int temp = north;
			north = south;
			south = temp;
		}

		ycoord = north * SCALE_FACTOR;
		xcoord = left * SCALE_FACTOR;
		height = (south - north) * SCALE_FACTOR;
		width = (WALKWAY_WIDTH) * SCALE_FACTOR;

		x2a = xcoord;
		y2a = ycoord + height;
		x1b = xcoord + width;
		y1b = ycoord;
	}

	x1a = xcoord;
	y1a = ycoord;
	x2b = xcoord + width;
	y2b = ycoord + height;

	file << "<rect x=\"" << xcoord << "\" y=\"" << ycoord << "\" width=\"" << width << "\" height=\"" << height << "\" style=\"" << WALKWAY_STYLE << "\"/>" << std::endl;
	file << "<line x1=\"" << x1a << "\" y1=\"" << y1a << "\" x2=\"" << x2a << "\" y2=\"" << y2a << "\" style=\"" << WALKWAY_EDGE_STYLE << "\" />" << std::endl;
	file << "<line x1=\"" << x1b << "\" y1=\"" << y1b << "\" x2=\"" << x2b << "\" y2=\"" << y2b << "\" style=\"" << WALKWAY_EDGE_STYLE << "\" />" << std::endl;
}
