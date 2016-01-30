#include "Walkway.h"

Walkway::Walkway(Direction dir, Court * c1, Court * c2, unsigned int le){
	this->direction = dir;
	this->court1 = c1;
	this->court2 = c2;
	this->leftEdge = le;
	//std::cout << "Creating connecting walkway between courts " << c1->getIndex() << " and " << c2->getIndex() << " in direction: " << this->direction << " at coord " << this->leftEdge << std::endl;
}

// FIXME: refactor to reduce repetition
void Walkway::toFile(std::ostream &file){
	Axis axis = DirectionMappings::getAxisOf(this->direction);

	unsigned int xcoord, ycoord, width, height;
	if(axis == YAXIS) {
		unsigned int west = this->court1->getEdge(DirectionMappings::getLeftOf(this->direction));
		unsigned int east = this->court2->getEdge(DirectionMappings::getRightOf(this->direction));
		if(east < west){
			unsigned int temp = west;
			west = east;
			east = temp;
		}

		xcoord = west * SCALE_FACTOR;
		ycoord = this->leftEdge * SCALE_FACTOR;
		width = (east - west) * SCALE_FACTOR;
		height = (WALKWAY_WIDTH) * SCALE_FACTOR;

		file << "<rect x=\"" << xcoord << "\" y=\"" << ycoord << "\" width=\"" << width << "\" height=\"" << height << "\" style=\"" << WALKWAY_STYLE << "\"/>" << std::endl;
		file << "<line x1=\"" << xcoord << "\" y1=\"" << ycoord << "\" x2=\"" << (xcoord + width) << "\" y2=\"" << ycoord << "\" style=\"" << WALKWAY_EDGE_STYLE << "\" />" << std::endl;
		file << "<line x1=\"" << xcoord << "\" y1=\"" << (ycoord + height) << "\" x2=\"" << (xcoord + width) << "\" y2=\"" << (ycoord + height) << "\" style=\"" << WALKWAY_EDGE_STYLE << "\" />" << std::endl;
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
		xcoord = this->leftEdge * SCALE_FACTOR;
		height = (south - north) * SCALE_FACTOR;
		width = (WALKWAY_WIDTH) * SCALE_FACTOR;

		file << "<rect x=\"" << xcoord << "\" y=\"" << ycoord << "\" width=\"" << width << "\" height=\"" << height << "\" style=\"" << WALKWAY_STYLE << "\"/>" << std::endl;
		file << "<line x1=\"" << xcoord << "\" y1=\"" << ycoord << "\" x2=\"" << xcoord << "\" y2=\"" << (ycoord+height) << "\" style=\"" << WALKWAY_EDGE_STYLE << "\" />" << std::endl;
		file << "<line x1=\"" << (xcoord + width) << "\" y1=\"" << ycoord << "\" x2=\"" << (xcoord + width) << "\" y2=\"" << (ycoord + height) << "\" style=\"" << WALKWAY_EDGE_STYLE << "\" />" << std::endl;
	}

	//file << "<rect x=\"" << xcoord << "\" y=\"" << ycoord << "\" width=\"" << width << "\" height=\"" << height << "\" style=\"" << WALKWAY_STYLE << "\"/>" << std::endl;
}
