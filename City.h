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


class City {
private:
	std::list<Court *> courts; // All courtyards making up this city; FIXME: consider making this a vector
	// This map gets updated on every Court insert; just test whether the Court being inserted expands these boundaries
	std::map<Direction, unsigned int> maxCoords;
	unsigned int courtCount; // FIXME: probably remove once debugged

	std::vector<Point *> perimeter; // FIXME: use list instead?
	std::vector<Concave *> concaves;
	std::list<Building *> buildings;
	std::list<Walkway *> walkways;

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

	void addWalkwaysToCourt(Court * primary, std::list<Court *>::iterator start, std::list<Court *>::iterator stop);

public:
	City();
	~City();
	void toFile(std::ofstream &file);
	void generate(unsigned int noCourts);
};

#endif
