#include "Court.h"

/*
 * Constructor
 * FIXME: refactor
 */
Court::Court(Axis primaryAxis, unsigned int primary1, unsigned int primary2, unsigned int cross1, unsigned int cross2, unsigned int ind){
	if(primaryAxis == YAXIS){
		if(primary1 > primary2){
			this->edges[SOUTH] = primary1;
			this->edges[NORTH] = primary2;
		}
		else{
			this->edges[SOUTH] = primary2;
			this->edges[NORTH] = primary1;
		}
		if(cross1 > cross2){
			this->edges[EAST] = cross1;
			this->edges[WEST] = cross2;
		}
		else{
			this->edges[EAST] = cross2;
			this->edges[WEST] = cross1;
		}
	}
	else{
		if(primary1 > primary2){
			this->edges[EAST] = primary1;
			this->edges[WEST] = primary2;
		}
		else{
			this->edges[EAST] = primary2;
			this->edges[WEST] = primary1;
		}
		if(cross1 > cross2){
			this->edges[SOUTH] = cross1;
			this->edges[NORTH] = cross2;
		}
		else{
			this->edges[SOUTH] = cross2;
			this->edges[NORTH] = cross1;
		}
	}
	this->index = ind;
	//std::cout << "\teast: " << this->edges[EAST] << "\tsouth: " << this->edges[SOUTH] << "\twest: " << this->edges[WEST] << "\tnorth: " << this->edges[NORTH] << "\t" << std::endl;
}

Court::~Court(){
}

unsigned int Court::getEdge(Direction dir){
	return this->edges[dir];
}

unsigned int Court::getIndex(){
	return this->index;
}

/*
 * Return whether a given point lies on the perimeter of this court
 * FIXME: refactor
 */
bool Court::hasOnPerimeter(Axis primaryAxis, unsigned int primaryCoord, unsigned int crossCoord){
	unsigned int east = this->edges[EAST];
	unsigned int south = this->edges[SOUTH];
	unsigned int west = this->edges[WEST];
	unsigned int north = this->edges[NORTH];
	if(primaryAxis == XAXIS){
		if (primaryCoord == east || primaryCoord == west){
			return (crossCoord <= south && crossCoord >= north);
		}
		else if (crossCoord == south || crossCoord == north){
			return (primaryCoord <= east && primaryCoord >= west);
		}
		return false;
	}
	else{
		if (primaryCoord == south || primaryCoord == north){
			return (crossCoord <= east && crossCoord >= west);
		}
		else if (crossCoord == east || crossCoord == west){
			return (primaryCoord <= south && primaryCoord >= north);
		}
		return false;
	}
}

/*
 * Return whether a given point lies within or on the perimeter of this court
 */
bool Court::containsPoint(Axis primaryAxis, unsigned int primaryCoord, unsigned int crossCoord){
	if(primaryAxis == XAXIS){
		return ((primaryCoord >= this->edges[WEST] && primaryCoord <= this->edges[EAST]) &&
				(crossCoord >= this->edges[NORTH] && crossCoord <= this->edges[SOUTH]));
	}
	return ((primaryCoord >= this->edges[NORTH] && primaryCoord <= this->edges[SOUTH]) &&
			(crossCoord >= this->edges[WEST] && crossCoord <= this->edges[EAST]));
}

/*
 * Return the minimum a court dimension can be, based on the other one
 */
unsigned int Court::getMinSecondDimension(unsigned int first){
	int second = first / MAX_RATIO + 1;
	if(second < COURT_DIM_MIN)
		second = COURT_DIM_MIN;
	return second;
}

/*
 * Return the maximum a court dimension can be, based on the other one
 */
unsigned int Court::getMaxSecondDimension(unsigned int first){
	int second = first * MAX_RATIO;
	if(second > COURT_DIM_MAX)
		second = COURT_DIM_MAX;
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
	file << "<text x=\"" << xcoord << "\" y=\"" << ycoord << "\" font-family=\"sans-serif\" font-size=\"12px\" fill=\"red\">" << this->index << "</text>" << std::endl;
}
