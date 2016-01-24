#include "Court.h"

/*
 * Constructor
 * FIXME: refactor
 
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
*/

/*
 * Constructor
 */
Court::Court(Axis primaryAxis, unsigned int primary1, unsigned int primary2, unsigned int cross1, unsigned int cross2, unsigned int ind){
	unsigned int lowerPrimary = primary1;
	unsigned int higherPrimary = primary2;
	if(primary1 > primary2){
		swap(lowerPrimary, higherPrimary);
	}
	unsigned int lowerCross = cross1;
	unsigned int higherCross = cross2;
	if(cross1 > cross2){
		swap(lowerCross, higherCross);
	}

	Axis crossAxis = (primaryAxis == XAXIS) ? YAXIS : XAXIS;

	this->edges[primaryAxis].push_back(lowerPrimary);
	this->edges[primaryAxis].push_back(higherPrimary);
	this->edges[crossAxis].push_back(lowerCross);
	this->edges[crossAxis].push_back(higherCross);

	this->index = ind;
	//std::cout << "\teast: " << this->edges[EAST] << "\tsouth: " << this->edges[SOUTH] << "\twest: " << this->edges[WEST] << "\tnorth: " << this->edges[NORTH] << "\t" << std::endl;
}

Court::~Court(){
}

void Court::swap(unsigned int &num1, unsigned int &num2){
	unsigned int temp = num1;
	num1 = num2;
	num2 = temp;
}

/*
unsigned int Court::getEdge(Direction dir){
	return this->edges[dir];
}

unsigned int Court::getIndex(){
	return this->index;
}


//Return whether a given point lies on the perimeter of this court
//FIXME: refactor
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

// Return whether a given point lies within or on the perimeter of this court
bool Court::containsPoint(Axis primaryAxis, unsigned int primaryCoord, unsigned int crossCoord){
	if(primaryAxis == XAXIS){
		return ((primaryCoord >= this->edges[WEST] && primaryCoord <= this->edges[EAST]) &&
				(crossCoord >= this->edges[NORTH] && crossCoord <= this->edges[SOUTH]));
	}
	return ((primaryCoord >= this->edges[NORTH] && primaryCoord <= this->edges[SOUTH]) &&
			(crossCoord >= this->edges[WEST] && crossCoord <= this->edges[EAST]));
}
*/

//Return the minimum a court dimension can be, based on the other one
unsigned int Court::getMinSecondDimension(unsigned int first){
	int second = first / MAX_RATIO + 1;
	if(second < COURT_DIM_MIN)
		second = COURT_DIM_MIN;
	return second;
}


//Return the maximum a court dimension can be, based on the other one
unsigned int Court::getMaxSecondDimension(unsigned int first){
	int second = first * MAX_RATIO;
	if(second > COURT_DIM_MAX)
		second = COURT_DIM_MAX;
	return second;
}


//Output this court to svg as a rect
void Court::toFile(std::ostream &file){
	unsigned int west = this->edges[XAXIS][0];
	unsigned int east = this->edges[XAXIS][1];
	unsigned int north = this->edges[YAXIS][0];
	unsigned int south = this->edges[YAXIS][1];

	unsigned int xcoord = west * SCALE_FACTOR;
	unsigned int ycoord = north * SCALE_FACTOR;
	unsigned int width = (east - west) * SCALE_FACTOR;
	unsigned int height = (south - north) * SCALE_FACTOR;

	unsigned int halfcolumn = (COURT_COLUMN_SIZE / 2) * SCALE_FACTOR;
	unsigned int fullcolumn = COURT_COLUMN_SIZE * SCALE_FACTOR;
	unsigned int columnupper = ycoord + (COURT_COLUMN_OFFSET * SCALE_FACTOR);
	unsigned int columnlower = ycoord + height - (COURT_COLUMN_OFFSET * SCALE_FACTOR);
	unsigned int columnleft = xcoord + (COURT_COLUMN_OFFSET * SCALE_FACTOR);
	unsigned int columnright = xcoord + width - (COURT_COLUMN_OFFSET * SCALE_FACTOR);

	// Outline and fill
	file << "<rect x=\"" << xcoord << "\" y=\"" << ycoord << "\" width=\"" << width << "\" height=\"" << height << "\" style=\"" << COURT_STYLE << "\"/>" << std::endl;

	// Grid
    for(int i = (xcoord+COURT_GRID_INTERVAL*SCALE_FACTOR); i < (xcoord+width); i += (COURT_GRID_INTERVAL*SCALE_FACTOR)){ // Vertical lines
        file << "<line x1=\"" << i << "\" y1=\"" << ycoord << "\" x2=\"" << i << "\" y2=\"" << (ycoord+height) << "\" style=\"" << GRID_STYLE << "\" />" << std::endl;
    }
	for(int i = (ycoord+COURT_GRID_INTERVAL*SCALE_FACTOR); i < (ycoord+height); i += (COURT_GRID_INTERVAL*SCALE_FACTOR)){ // Horizontal lines
        file << "<line x1=\"" << xcoord << "\" y1=\"" << i << "\" x2=\"" << (xcoord+width) << "\" y2=\"" << i << "\" style=\"" << GRID_STYLE << "\" />" << std::endl;
	}

	// Columns
	for(int i = columnleft; i <= columnright; i += (COURT_COLUMN_INTERVAL*SCALE_FACTOR)){ // Horizontal lines of columns
		file << "<rect x=\"" << (i-halfcolumn) << "\" y=\"" << (columnupper-halfcolumn) << "\" width=\"" << fullcolumn << "\" height=\"" << fullcolumn << "\" style=\"" << COURT_COLUMN_STYLE << "\"/>" << std::endl;
		file << "<rect x=\"" << (i-halfcolumn) << "\" y=\"" << (columnlower-halfcolumn) << "\" width=\"" << fullcolumn << "\" height=\"" << fullcolumn << "\" style=\"" << COURT_COLUMN_STYLE << "\"/>" << std::endl;
	}
	for(int i = columnupper + COURT_COLUMN_INTERVAL * SCALE_FACTOR; i < columnlower; i += (COURT_COLUMN_INTERVAL*SCALE_FACTOR)){
		file << "<rect x=\"" << (columnleft-halfcolumn) << "\" y=\"" << (i-halfcolumn) << "\" width=\"" << fullcolumn << "\" height=\"" << fullcolumn << "\" style=\"" << COURT_COLUMN_STYLE << "\"/>" << std::endl;
		file << "<rect x=\"" << (columnright-halfcolumn) << "\" y=\"" << (i-halfcolumn) << "\" width=\"" << fullcolumn << "\" height=\"" << fullcolumn << "\" style=\"" << COURT_COLUMN_STYLE << "\"/>" << std::endl;
	}

	// Label
	file << "<text x=\"" << xcoord << "\" y=\"" << (ycoord-2) << "\" font-family=\"sans-serif\" font-size=\"12px\" fill=\"red\">" << this->index << "</text>" << std::endl;
}
