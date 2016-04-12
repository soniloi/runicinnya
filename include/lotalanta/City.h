#ifndef CITY_H
#define CITY_H

#include <fstream>
#include <iostream>
#include <list>
#include <vector>

#include "Concave.h"
#include "Court.h"
#include "Building.h"
#include "Walkway.h"

#define WIDTH MAX_X
#define HEIGHT MAX_Y

#define STARTX (WIDTH/2)
#define STARTY (HEIGHT/2)

#define BG_COLOUR "white"

typedef std::list<Court *> CourtCollection; // FIXME: consider making this a vector
typedef std::vector<Point *> PerimeterCollection; // FIXME: use list instead?
typedef std::vector<Concave *> ConcaveCollection;
typedef std::list<Building *> BuildingCollection;
typedef std::list<Walkway *> WalkwayCollection;
typedef std::map<Direction, unsigned int> MaxCoordsCollection;

class City {
private:
	CourtCollection courts; // All courtyards making up this city
	// This map gets updated on every Court insert; just test whether the Court being inserted expands these boundaries
	MaxCoordsCollection maxCoords;
	unsigned int courtCount; // FIXME: probably remove once debugged

	PerimeterCollection perimeter;
	ConcaveCollection concaves;
	BuildingCollection buildings;
	WalkwayCollection walkways;

	static unsigned int ran(int from, int to);
	static unsigned int absolute(int num);
	static void swap(unsigned int &num1, unsigned int &num2);

	void clearPerimeterAndConcaves();
	void updatePerimeter();
	Court * getStartingCourt();
	Court * travelClockwise(Court * currCourt, Point * &currPoint, Direction &currDir);
	Court * findNeighbouringCourt(Court * baseCourt, unsigned int dimToChange, unsigned int dimToStay, Axis normalAxis, int polarity, unsigned int &match);

	void insertCourt(Court * court);
	Court * createInitialCourt();
	Court * createCourt();
	Court * createCourtConvex();
	Court * createCourtConcave();

	void addWalkwaysToCourt(Court * primary, CourtCollection::iterator start, CourtCollection::iterator stop);

public:
	City();
	~City();
	void toFile(std::ofstream &file);
	void generate(unsigned int noCourts);
};

#endif
