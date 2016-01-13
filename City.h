#ifndef CITY_H
#define CITY_H

#include <fstream>
#include <iostream>
#include <list>
#include <vector>

#include "Concave.h"
#include "Court.h"

#define WIDTH MAX_X
#define HEIGHT MAX_Y

#define STARTX (WIDTH/2)
#define STARTY (HEIGHT/2)

#define BG_COLOUR "white"

#define POLARITY_POSITIVE 1
#define POLARITY_NEGATIVE -1


class City {
private:
	std::list<Court *> courts; // All courtyards making up this city
	// This map gets updated on every Court insert; just test whether the Court being inserted expands these boundaries
	std::map<Direction, unsigned int> maxCoords;

	std::vector<Point *> perimeter; // FIXME: use list instead?
	std::vector<Concave *> concaves;

	static unsigned int ran(int from, int to);
	static unsigned int absolute(int num);
	static void swap(unsigned int &num1, unsigned int &num2);

	void clearPerimeterAndConcaves();
	void updatePerimeter();
	Court * getStartingCourt();
	Court * travelClockwise(Court * currCourt, Point * &currPoint, Direction &currDir);
	Court * findNeighbouringCourt(Court * baseCourt, unsigned int dimToChange, unsigned int dimToStay, Axis normalAxis, int polarity, unsigned int &match);
	Court * findContainingCourt(Axis primaryAxis, unsigned int primaryCoord, unsigned int crossCoord);

	void insertCourt(Court * court);
	Court * createInitialCourt();
	Court * createCourt();
	Court * createCourtConvex();
	Court * createCourtConcave();

	static std::map<Direction, Direction> createLeftOf(){
		std::map<Direction, Direction> m;
		m[EAST] = NORTH;
		m[SOUTH] = EAST;
		m[WEST] = SOUTH;
		m[NORTH] = WEST;
		return m;
	}
	static std::map<Direction, Direction> leftOf;

	static std::map<Direction, Direction> createRightOf(){
		std::map<Direction, Direction> m;
		m[EAST] = SOUTH;
		m[SOUTH] = WEST;
		m[WEST] = NORTH;
		m[NORTH] = EAST;
		return m;
	}
	static std::map<Direction, Direction> rightOf;

	static std::map<Direction, int> createPolarityOf(){
		std::map<Direction, int> m;
		m[EAST] = POLARITY_POSITIVE;
		m[SOUTH] = POLARITY_POSITIVE;
		m[WEST] = POLARITY_NEGATIVE;
		m[NORTH] = POLARITY_NEGATIVE;
		return m;
	}
	static std::map<Direction, int> polarityOf;

	static std::map<Direction, Axis> createAxisOf(){
		std::map<Direction, Axis> m;
		m[EAST] = XAXIS;
		m[SOUTH] = YAXIS;
		m[WEST] = XAXIS;
		m[NORTH] = YAXIS;
		return m;
	}
	static std::map<Direction, Axis> axisOf;

public:
	City();
	~City();
	void toFile(std::ofstream &file);
	void generate(unsigned int noCourts);
};

#endif
