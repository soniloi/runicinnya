#include "City.h"

using namespace std;

map<Direction, Direction> City::leftOf = City::createLeftOf();
map<Direction, Direction> City::rightOf = City::createRightOf();
map<Direction, int> City::polarityOf = City::createPolarityOf();
map<Direction, Axis> City::axisOf = City::createAxisOf();

City::City(){
	this->maxE = STARTX;
	this->maxS = STARTY;
	this->maxW = STARTX;
	this->maxN = STARTY;

	this->insertCourt(new Court(XAXIS, STARTX, STARTX-7, STARTY, STARTY-4));
	this->insertCourt(new Court(XAXIS, 95, 91, 37, 33));
	this->insertCourt(new Court(XAXIS, 98, 92 ,44, 38));
	this->insertCourt(new Court(XAXIS, 87, 85, 44, 42));
	this->insertCourt(new Court(XAXIS, 91, 88, 46, 41));
}

City::~City(){
	/*
	this->clearPerimeterAndConcaves(); //FIXME:
	for(auto it = this->courts.begin(); it != this->courts.end(); it++){
		delete (*it);
	}
	*/
}

/*
 * Return pseudorandom unsigned integer between two values (inclusive)
 */
unsigned int City::ran(int from, int to){
	static std::mt19937 rng;
	static bool seed_set = false;
	if(!seed_set){
		rng.seed(time(NULL));
		seed_set = true;
	}
	std::uniform_int_distribution<uint32_t> dist(from, to);
	return dist(rng);
}

unsigned int City::absolute(int num){
	if (num < 0)
		return num * (-1);
	return num;
}

void City::toFile(ofstream &file){

	// Starting boilerplate
	file << "<?xml version=\"1.0\"?>" << endl;
	file << "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width=\"" << (WIDTH * SCALE_FACTOR) << "\" height=\"" << (HEIGHT * SCALE_FACTOR) << "\" style=\"background: " << BG_COLOUR << "\">" << endl;

	// Content (courtyards)
	for (auto it = this->courts.begin(); it != this->courts.end(); it++){
		(*it)->toFile(file);
	}

	// Perimeter
	auto it = this->perimeter.begin();
	if(it != this->perimeter.end()){
		auto jt = it;
		jt++;
		while(jt != perimeter.end()){
			unsigned int x1 = (*it)->getCoord(XAXIS) * SCALE_FACTOR;
			unsigned int x2 = (*jt)->getCoord(XAXIS) * SCALE_FACTOR;
			unsigned int y1 = (*it)->getCoord(YAXIS) * SCALE_FACTOR;
			unsigned int y2 = (*jt)->getCoord(YAXIS) * SCALE_FACTOR;

			//cout << "\t\tx1: " << x1 << " y1: " << y1 << " x2: " << x2 << " y2: " << y2 << endl;

			file << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" style=\"stroke:rgb(0,255,255);stroke-width:2\" />" << endl;

			file << "<circle cx=\"" << x1 << "\" cy=\"" << y1 << "\" r=\"2\" style=\"stroke:rgb(0,0,255);stroke-width:1\" />" << endl;
			file << "<circle cx=\"" << x2 << "\" cy=\"" << y2 << "\" r=\"2\" style=\"stroke:rgb(0,0,255);stroke-width:1\" />" << endl;

			it++;
			jt++;
		}
	}

	// Concave points
	for(auto kt = this->concaves.begin(); kt != this->concaves.end(); kt++){
		unsigned int x = (*kt)->getCoord(XAXIS) * SCALE_FACTOR;
		unsigned int y = (*kt)->getCoord(YAXIS) * SCALE_FACTOR;

		file << "<circle cx=\"" << x << "\" cy=\"" << y << "\" r=\"5\" style=\"stroke:rgb(128,128,255);stroke-width:1\" />" << endl;
	}

	// Ending boilerplate
	file << "</svg>" << endl;
}

/*
 * Insert an already-created court into this city
 */
void City::insertCourt(Court * court){
	this->courts.push_back(court);
	
	unsigned int courtea = court->getEdge(EAST);
	unsigned int courtso = court->getEdge(SOUTH);
	unsigned int courtwe = court->getEdge(WEST);
	unsigned int courtno = court->getEdge(NORTH);

	if(courtea > this->maxE)
		this->maxE = courtea;
	if(courtso > this->maxS)
		this->maxS = courtso;
	if(courtwe < this->maxW)
		this->maxW = courtwe;
	if(courtno < this->maxN)
		this->maxN = courtno;
}

/*
 * Create a new court somewhere random in this city
 */
Court * City::createCourt(){
	this->updatePerimeter();
	Court * newCourt = NULL;

	unsigned int noConcaves = this->concaves.size();

	if(noConcaves > 0){
		Concave * concave = this->concaves[City::ran(0, noConcaves-1)]; // TODO:

		Direction rightEdge = concave->getRightEdge();
		Axis rightAxis = City::axisOf[rightEdge];
		int rightPolarity = City::polarityOf[rightEdge];

		Direction lowerEdge = City::leftOf[rightEdge];
		Axis lowerAxis = (rightAxis == XAXIS) ? YAXIS : XAXIS;
		int lowerPolarity = City::polarityOf[lowerEdge];

		unsigned int concaveRightDim = concave->getCoord(rightAxis);
		unsigned int concaveLowerDim = concave->getCoord(lowerAxis);

		unsigned int newRightDim, newLowerDim, newLeftDim, newUpperDim;

		// Get starting point of new court
		newRightDim = concaveRightDim - (City::ran(BUILDING_DEPTH_MIN, BUILDING_DEPTH_MAX) * rightPolarity);
		if(City::absolute(concaveRightDim - newRightDim) > BUILDING_DEPTH_MIN)
			newLowerDim = concaveLowerDim + (BUILDING_DEPTH_MIN * lowerPolarity);
		else
			newLowerDim = concaveLowerDim + (City::ran(BUILDING_DEPTH_MIN, BUILDING_DEPTH_MAX) * lowerPolarity);

		// Get other edges of new court
		newLeftDim = newRightDim - (City::ran(COURT_DIM_MIN, COURT_DIM_MAX) * rightPolarity);
		unsigned int firstDim = City::absolute(newRightDim - newLeftDim);
		newUpperDim = newLowerDim + (City::ran(Court::getMinSecondDimension(firstDim), Court::getMaxSecondDimension(firstDim)) * lowerPolarity);

		newCourt = new Court(rightAxis, newRightDim, newLeftDim, newLowerDim, newUpperDim);
		this->insertCourt(newCourt);
	}

	return newCourt;
}

/*
 * Clear the previous perimeter and concave points
 */
void City::clearPerimeterAndConcaves(){
	for(auto it = this->perimeter.begin(); it != this->perimeter.end(); it++){
		delete (*it);
	}
	this->perimeter.clear();
	for(auto it = this->concaves.begin(); it != this->concaves.end(); it++){
		delete (*it);
	}
	this->concaves.clear();	
}

/*
 * Update the perimeter and concave points of this city
 */
void City::updatePerimeter(){
	this->clearPerimeterAndConcaves();

	Court * currCourt = this->getStartingCourt();
	int startX = currCourt->getEdge(WEST);
	int startY = currCourt->getEdge(NORTH);
	Direction currDir = EAST;

	Point * startingPoint = new Point(XAXIS, startX, YAXIS, startY);
	Point * currPoint = startingPoint;

	this->perimeter.push_back(startingPoint); // FIXME: possibly should not add, only use to compare against

	do {
		cout << "Travelling: ";
		switch(currDir){
			case EAST: cout << "EAST"; break;
			case SOUTH: cout << "SOUTH"; break;
			case WEST: cout << "WEST"; break;
			case NORTH: cout << "NORTH"; break;
		}
		cout << endl;

		currCourt = this->travelClockwise(currCourt, currPoint, currDir);
	} while (!currPoint->equals(startingPoint));

}

/*
 * Travel the city's perimeter clockwise, adding a perimeter point and a concave point if appropriate
 */
Court * City::travelClockwise(Court * currCourt, Point * &currPoint, Direction &currDir){
	Direction leftDir = City::leftOf[currDir];
	Direction rightDir = City::rightOf[currDir];
	int polarity = City::polarityOf[currDir];
	int leftPolarity = City::polarityOf[leftDir];
	Axis currAxis = City::axisOf[currDir];
	Axis perpendicularAxis = (currAxis == XAXIS) ? YAXIS : XAXIS;

	unsigned int dimToStay = currCourt->getEdge(leftDir);
	unsigned int firstPoint = currPoint->getCoord(currAxis);
	unsigned int lastPoint = currCourt->getEdge(currDir);

	unsigned int dimToChange = firstPoint;
	unsigned int match;
	Court * provCourt;

	while(dimToChange != lastPoint){
		dimToChange += 1 * (polarity);
		provCourt = this->findNeighbouringCourt(currCourt, dimToStay, dimToChange, perpendicularAxis, leftPolarity, match);
		if(provCourt){
			currPoint = new Point(currAxis, dimToChange, perpendicularAxis, dimToStay);
			this->perimeter.push_back(currPoint);
			this->concaves.push_back(new Concave(currAxis, dimToChange, perpendicularAxis, dimToStay, currDir));
			currDir = leftDir;
			return provCourt;
		}
	}

	provCourt = this->findNeighbouringCourt(currCourt, dimToChange, dimToStay, currAxis, polarity, match);
	if(provCourt){
		dimToChange = match;
		if(dimToStay == provCourt->getEdge(leftDir)){ // Continuing along the edge; do not add point or change direction
			//this->perimeter.push_back(new Point(currAxis, dimToChange, perpendicularAxis, dimToStay));
			return provCourt;
		}
		else{
			currPoint = new Point(currAxis, dimToChange, perpendicularAxis, dimToStay);
			this->perimeter.push_back(currPoint);
			this->concaves.push_back(new Concave(currAxis, dimToChange, perpendicularAxis, dimToStay, currDir));
			currDir = leftDir;
			return provCourt;
		}
	}
	else{
		currPoint = new Point(currAxis, dimToChange, perpendicularAxis, dimToStay);
		this->perimeter.push_back(currPoint);
		currDir = rightDir;
		return currCourt;
	}
}

/*
 * Find a court adjacent to a given court, relevant to perimeter calculation
 */
Court * City::findNeighbouringCourt(Court * baseCourt, unsigned int dimToChange, unsigned int dimToStay, Axis normalAxis, int polarity, unsigned int &match){
	for(auto it = this->courts.begin(); it != this->courts.end(); it++){
		Court * court = (*it);
		for(int i = BUILDING_DEPTH_MIN; i <= BUILDING_DEPTH_MAX; ++i){
			unsigned int proposed = dimToChange + (i * (polarity));
			if(court != baseCourt && court->hasOnPerimeter(normalAxis, proposed, dimToStay)){
				match = proposed;
				return court;
			}
		}
	}

	return NULL;
}

/*
 * Return the court that the perimeter calculation should be started at
 */
Court * City::getStartingCourt(){
	unsigned int ver = MAX_X;
	Court * result = NULL;
	for(auto it = this->courts.begin(); it != this->courts.end(); it++){
		Court * court = (*it);
		if(court->getEdge(NORTH) == this->maxN){
			unsigned int left = court->getEdge(WEST);
			if(left < ver){
				ver = left;
				result = court;
			}
		}
	}

	return result;
}
