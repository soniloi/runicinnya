#include "Court.h"

/*
 * Constructor
 */
Court::Court(unsigned int e, unsigned int s, unsigned int w, unsigned int n){
	this->edges[EAST] = e;
	this->edges[SOUTH] = s;
	this->edges[WEST] = w;
	this->edges[NORTH] = n;

	//std::cout << "\teast: " << this->edges[EAST] << "\tsouth: " << this->edges[SOUTH] << "\twest: " << this->edges[WEST] << "\tnorth: " << this->edges[NORTH] << "\t" << std::endl;
}

Court::~Court(){
}

unsigned int Court::getEdge(Direction dir){
	return this->edges[dir];
}

/*
 * Return whether a given point lies on the perimeter of this court
 * FIXME: refactor
 */
bool Court::hasOnPerimeter(Axis normalAxis, unsigned int val1, unsigned int val2){
	unsigned int east = this->edges[EAST];
	unsigned int south = this->edges[SOUTH];
	unsigned int west = this->edges[WEST];
	unsigned int north = this->edges[NORTH];
	if(normalAxis == XAXIS){
		if (val1 == east || val1 == west){
			return (val2 <= south && val2 >= north);
		}
		else if (val2 == south || val2 == north){
			return (val1 <= east && val1 >= west);
		}
		return false;
	}
	else{
		if (val1 == south || val1 == north){
			return (val2 <= east && val2 >= west);
		}
		else if (val2 == east || val2 == west){
			return (val1 <= south && val1 >= north);
		}
		return false;
	}
}

/*
 * Return the minimum a court dimension can be, based on the other one
 */
unsigned int Court::getMinSecondDimension(unsigned int first){
	int second = first / MAX_RATIO + 1;
	if(second < DIM_MIN)
		second = DIM_MIN;
	return second;
}

/*
 * Return the maximum a court dimension can be, based on the other one
 */
unsigned int Court::getMaxSecondDimension(unsigned int first){
	int second = first * MAX_RATIO;
	if(second > DIM_MAX)
		second = DIM_MAX;
	return second;
}

/*
 * Output this court to svg as a rect
 */
void Court::toFile(std::ostream &file){
	int xcoord = this->edges[WEST] * SCALE_FACTOR;
	int ycoord = this->edges[NORTH] * SCALE_FACTOR;
	int width = (this->edges[EAST] - this->edges[WEST]) * SCALE_FACTOR;
	int height = (this->edges[SOUTH] - this->edges[NORTH]) * SCALE_FACTOR;

	file << "<rect x=\"" << xcoord << "\" y=\"" << ycoord << "\" width=\"" << width << "\" height=\"" << height << "\" style=\"" << COURT_STYLE << "\"/>" << std::endl;
}
