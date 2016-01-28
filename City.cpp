#include "City.h"

using namespace std;

map<Direction, Direction> City::leftOf = City::createLeftOf();
map<Direction, Direction> City::rightOf = City::createRightOf();
map<Direction, Direction> City::oppositeOf = City::createOppositeOf();
map<Direction, int> City::polarityOf = City::createPolarityOf();
map<Direction, Axis> City::axisOf = City::createAxisOf();

City::City(){
	this->maxCoords[EAST] = this->maxCoords[WEST] = STARTX;
	this->maxCoords[SOUTH] = this->maxCoords[NORTH] = STARTY;
	this->courtCount = 0;
}

City::~City(){
	// TODO: release perimeter points, concaves, courts, buildings, and walkways
}

/*
 * Return pseudorandom unsigned integer between two values (inclusive)
 */
unsigned int City::ran(int from, int to){
	static std::mt19937 rng;
	static bool seed_set = false;
	if(!seed_set){
		//rng.seed(time(NULL));
		rng.seed(1217);
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

void City::swap(unsigned int &num1, unsigned int &num2){
	unsigned int temp = num1;
	num1 = num2;
	num2 = temp;
}

void City::toFile(ofstream &file){

	// Starting boilerplate
	file << "<?xml version=\"1.0\"?>" << endl;
	file << "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width=\"" << (WIDTH * SCALE_FACTOR) << "\" height=\"" << (HEIGHT * SCALE_FACTOR) << "\" style=\"background: " << BG_COLOUR << "\">" << endl;

	// Grid
	for(int i = 0; i < (MAX_Y * SCALE_FACTOR); i+=SCALE_FACTOR){
		file << "<line x1=\"" << 0 << "\" y1=\"" << i << "\" x2=\"" << (MAX_X * SCALE_FACTOR) << "\" y2=\"" << i << "\" style=\"stroke:rgb(192,224,255);stroke-width:0.25\" />" << endl;
	}
	for(int i = 0; i < (MAX_Y * SCALE_FACTOR); i+=(SCALE_FACTOR*10)){
		file << "<line x1=\"" << 0 << "\" y1=\"" << i << "\" x2=\"" << (MAX_X * SCALE_FACTOR) << "\" y2=\"" << i << "\" style=\"stroke:rgb(192,224,255);stroke-width:1\" />" << endl;
		file << "<text x=\"" << 1180 << "\" y=\"" << (i-8) << "\" font-family=\"sans-serif\" font-size=\"12px\" fill=\"gray\">" << (i/SCALE_FACTOR) << "</text>" << std::endl;
	}

	for(int i = 0; i < (MAX_X * SCALE_FACTOR); i+=SCALE_FACTOR){
		file << "<line x1=\"" << i << "\" y1=\"" << 0 << "\" x2=\"" << i << "\" y2=\"" << (MAX_Y * SCALE_FACTOR) << "\" style=\"stroke:rgb(192,224,255);stroke-width:0.25\" />" << endl;
	}
	for(int i = 0; i < (MAX_X * SCALE_FACTOR); i+=(SCALE_FACTOR*10)){
		file << "<line x1=\"" << i << "\" y1=\"" << 0 << "\" x2=\"" << i << "\" y2=\"" << (MAX_Y * SCALE_FACTOR) << "\" style=\"stroke:rgb(192,224,255);stroke-width:1\" />" << endl;
		file << "<text x=\"" << (i+8) << "\" y=\"" << 392 << "\" font-family=\"sans-serif\" font-size=\"12px\" fill=\"gray\">" << (i/SCALE_FACTOR) << "</text>" << std::endl;
	}

	// Buildings
	for (auto it = this->buildings.begin(); it != this->buildings.end(); it++){
		(*it)->toFile(file);
	}

	// Courtyards
	int count = 0;
	for (auto it = this->courts.begin(); it != this->courts.end(); it++){
		(*it)->toFile(file);
		count++;
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

void City::generate(unsigned int noCourts){
	if(noCourts == 0)
		return;

	Court * nextCourt;

	nextCourt = this->createInitialCourt();
	this->insertCourt(nextCourt);
	this->updatePerimeter();

	for(int i = 1; i < noCourts; ++i){
		nextCourt = this->createCourt();
		if(nextCourt) // FIXME: make it so it's not possible to get a NULL return
			this->insertCourt(nextCourt);
		this->updatePerimeter();
	}


	for(auto it = this->courts.begin(); it != this->courts.end(); it++){
		Court * current = (*it);
		for(auto jt = this->courts.begin(); jt != it; jt++){
			Court * other = (*jt);
			Direction adjacentSide;
			unsigned int adjacentLower, adjacentUpper;

			if(current->adjacentTo(other, adjacentSide, adjacentLower, adjacentUpper)){
				this->walkways.push_back(new Walkway(City::rightOf[adjacentSide], current, other, City::ran(adjacentLower, adjacentUpper)));
			}
		}
	}

	// TODO: this should instead be detectBuildings() or computeBuildings() or something, determined based on where courts have been placed
	//this->buildings.push_back(new Building(XAXIS, 87, 45, 1, 1));
	//this->buildings.push_back(new Building(YAXIS, 44, 92, 2, 7));
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

	if(courtea > this->maxCoords[EAST])
		this->maxCoords[EAST] = courtea;
	if(courtso > this->maxCoords[SOUTH])
		this->maxCoords[SOUTH] = courtso;
	if(courtwe < this->maxCoords[WEST])
		this->maxCoords[WEST] = courtwe;
	if(courtno < this->maxCoords[NORTH])
		this->maxCoords[NORTH] = courtno;
}

/*
 * Create the first court in this city
 */
Court * City::createInitialCourt(){
	Court * newCourt = this->createCourtConvex();
	this->maxCoords[EAST] = newCourt->getEdge(EAST);
	this->maxCoords[SOUTH] = newCourt->getEdge(SOUTH);
	this->maxCoords[WEST] = newCourt->getEdge(WEST);
	this->maxCoords[NORTH] = newCourt->getEdge(NORTH);
	return newCourt;
}

/*
 * Create a new court somewhere random in this city
 */
Court * City::createCourt(){
	Court * newCourt;
	if(this->concaves.size() == 0)
		newCourt = this->createCourtConvex();
	else
		newCourt = this->createCourtConcave();
	return newCourt;
}

/*
 * Create a new court somewhere outside the current perimeter of this city
 */
Court * City::createCourtConvex(){
	Court * newCourt = NULL;

	// Choose a side at random to add the new court on, and which direction from that the new court should fan
	Direction side = (Direction) City::ran(0, NUM_DIRECTIONS-1);
	Axis primaryAxis = City::axisOf[side];
	int primaryPolarity = City::polarityOf[side];
	int crossPolarity = POLARITY_POSITIVE;
	if(City::ran(0, 1))
		crossPolarity = POLARITY_NEGATIVE;

	// Determine cross boundaries
	unsigned int crossBound1, crossBound2;
	crossBound1 = this->maxCoords[City::leftOf[side]];
	crossBound2 = this->maxCoords[City::rightOf[side]];
	if(crossBound2 < crossBound1)
		swap(crossBound1, crossBound2);

	// Determine the first coordinates of the new court
	unsigned int primaryAxisCoord1, crossAxisCoord1, primaryAxisCoord2, crossAxisCoord2;
	primaryAxisCoord1 = this->maxCoords[side] + (City::ran(BUILDING_DEPTH_MIN, BUILDING_DEPTH_MAX) * primaryPolarity);
	crossAxisCoord1 = City::ran(crossBound1, crossBound2);

	// Determine the other coordinates
	primaryAxisCoord2 = primaryAxisCoord1 + (City::ran(COURT_DIM_MIN, COURT_DIM_MAX) * primaryPolarity);
	unsigned int firstDim = City::absolute(primaryAxisCoord2 - primaryAxisCoord1);
	crossAxisCoord2 = crossAxisCoord1 + (City::ran(Court::getMinSecondDimension(firstDim), Court::getMaxSecondDimension(firstDim)) * crossPolarity);

	newCourt = new Court(primaryAxis, primaryAxisCoord1, primaryAxisCoord2, crossAxisCoord1, crossAxisCoord2, this->courtCount++);

	return newCourt;
}

/*
 * Create a new court at a random concave point in this city
 */
Court * City::createCourtConcave(){

	// Choose a concave point at random to add the new court at
	Concave * concave = this->concaves[City::ran(0, this->concaves.size()-1)];
	cout << "### Inserting court #" << this->courtCount << " at concave: " << concave->toString() << endl;

	Direction rightEdge = concave->getRightEdge();
	Axis rightAxis = City::axisOf[rightEdge];
	int rightPolarity = City::polarityOf[rightEdge];

	Direction lowerEdge = City::leftOf[rightEdge];
	Axis lowerAxis = (rightAxis == XAXIS) ? YAXIS : XAXIS;
	int lowerPolarity = City::polarityOf[lowerEdge];

	unsigned int concaveRightDim = concave->getCoord(rightAxis);
	unsigned int concaveLowerDim = concave->getCoord(lowerAxis);


	unsigned int newRightCoord, newLowerCoord, newLeftCoord, newUpperCoord;

	// Get starting point of new court
	newRightCoord = concaveRightDim - (City::ran(BUILDING_DEPTH_MIN, BUILDING_DEPTH_MAX) * rightPolarity);
	if(City::absolute(concaveRightDim - newRightCoord) > BUILDING_DEPTH_MIN)
		newLowerCoord = concaveLowerDim + (BUILDING_DEPTH_MIN * lowerPolarity);
	else
		newLowerCoord = concaveLowerDim + (City::ran(BUILDING_DEPTH_MIN, BUILDING_DEPTH_MAX) * lowerPolarity);

	// Get other edges of new court
	newLeftCoord = newRightCoord - (City::ran(COURT_DIM_MIN, COURT_DIM_MAX) * rightPolarity);
	unsigned int firstDim = City::absolute(newRightCoord - newLeftCoord);

	newUpperCoord = newLowerCoord + (City::ran(Court::getMinSecondDimension(firstDim), Court::getMaxSecondDimension(firstDim)) * lowerPolarity);
	//cout << "\tProposing: newRightCoord: " << newRightCoord << " newLeftCoord: " << newLeftCoord << " newLowerCoord: " << newLowerCoord << " newUpperCoord: " << newUpperCoord << endl;

	for(auto it = this->courts.begin(); it != this->courts.end(); it++){
		if(newLeftCoord > newRightCoord)
			swap(newLeftCoord, newRightCoord);
		if(newUpperCoord > newLowerCoord)
			swap(newUpperCoord, newLowerCoord);
		if((*it)->resolveCollision(rightAxis, newLeftCoord, newRightCoord, newUpperCoord, newLowerCoord)){
			cout << "\tCollision detected and resolved" << endl;
			// TODO: check for zero-length resolutions
		}
	}

	return new Court(rightAxis, newRightCoord, newLeftCoord, newLowerCoord, newUpperCoord, this->courtCount++);
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
	if(!currCourt){
		cout << "No starting point; error" << endl;
		return;
	}

	int startX = currCourt->getEdge(WEST);
	int startY = currCourt->getEdge(NORTH);
	Direction currDir = EAST;

	Point * startingPoint = new Point(XAXIS, startX, startY);
	Point * currPoint = startingPoint;

	this->perimeter.push_back(startingPoint);

	int iterations = 0; // FIXME: this to come out when overlap issues fixed
	do {
		/*
		cout << "Travelling: ";
		switch(currDir){
			case EAST: cout << "EAST"; break;
			case SOUTH: cout << "SOUTH"; break;
			case WEST: cout << "WEST"; break;
			case NORTH: cout << "NORTH"; break;
			default: break;
		}
		cout << endl;
*/
		//cout << "traversing perimeter" << endl;
		currCourt = this->travelClockwise(currCourt, currPoint, currDir);
		iterations++;
	} while ((currPoint == startingPoint || !currPoint->equals(startingPoint)) && iterations < 1000);

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

	// Check just a little bit beyond the end in this direction, in case there are any on the left there
	unsigned int pastLastPoint = lastPoint + (BUILDING_DEPTH_MAX * polarity);
	while(dimToChange != pastLastPoint){
		dimToChange += 1 * (polarity);
		provCourt = this->findNeighbouringCourt(currCourt, dimToStay, dimToChange, perpendicularAxis, leftPolarity, match);
		if(provCourt){
			currPoint = new Point(currAxis, dimToChange, dimToStay);
			this->perimeter.push_back(currPoint);
			this->concaves.push_back(new Concave(currAxis, dimToChange, dimToStay, currDir));
			currDir = leftDir;
			return provCourt;
		}
	}

	// There are none beyond, so go around the corner instead
	dimToChange = lastPoint;

	provCourt = this->findNeighbouringCourt(currCourt, dimToChange, dimToStay, currAxis, polarity, match);
	if(provCourt){
		dimToChange = match;
		if(dimToStay == provCourt->getEdge(leftDir)){ // Continuing along the edge; do not add point or change direction
			//this->perimeter.push_back(new Point(currAxis, dimToChange, dimToStay));
			return provCourt;
		}
		else{
			currPoint = new Point(currAxis, dimToChange, dimToStay);
			this->perimeter.push_back(currPoint);
			this->concaves.push_back(new Concave(currAxis, dimToChange, dimToStay, currDir));
			currDir = leftDir;
			return provCourt;
		}
	}
	else{
		currPoint = new Point(currAxis, dimToChange, dimToStay);
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
		unsigned int bound = (BUILDING_DEPTH_MAX < 2) ? 2 : BUILDING_DEPTH_MAX; // Even if BUILDING_DEPTH_MAX is 1, the minimum distance between courts will be 3 when we want to allow for another one
		for(int i = BUILDING_DEPTH_MIN; i <= bound; ++i){
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
	unsigned int vert = MAX_X;
	Court * result = NULL;
	for(auto it = this->courts.begin(); it != this->courts.end(); it++){
		Court * court = (*it);
		if(court->getEdge(NORTH) == this->maxCoords[NORTH]){
			unsigned int west = court->getEdge(WEST);
			if(west < vert){ // we want the westmost one of these, in case several border the northernmost line
				vert = west;
				result = court;
			}
		}
	}

	return result;
}
