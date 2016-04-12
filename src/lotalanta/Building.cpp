#include "../../include/lotalanta/Building.h"

Building::Building(Axis primaryAxis, unsigned int primaryCoord, unsigned int crossCoord, unsigned int primaryDim, unsigned int crossDim){
	Axis crossAxis = (primaryAxis == XAXIS) ? YAXIS : XAXIS;

	this->coords[primaryAxis] = primaryCoord;
	this->coords[crossAxis] = crossCoord;
	this->dims[primaryAxis] = primaryDim;
	this->dims[crossAxis] = crossDim;
}

Building::~Building(){
}

unsigned int Building::getCoord(Axis a){
	return this->coords[a];
}

unsigned int Building::getDim(Axis a){
	return this->dims[a];
}

void Building::toFile(std::ostream &file){
	unsigned int xcoord = this->coords[XAXIS] * SCALE_FACTOR;
	unsigned int ycoord = this->coords[YAXIS] * SCALE_FACTOR;
	unsigned int width = this->dims[XAXIS] * SCALE_FACTOR;
	unsigned int height = this->dims[YAXIS] * SCALE_FACTOR;

	// Outline and fill
	file << "<rect x=\"" << xcoord << "\" y=\"" << ycoord << "\" width=\"" << width << "\" height=\"" << height << "\" style=\"" << BUILDING_STYLE << "\"/>" << std::endl;
}