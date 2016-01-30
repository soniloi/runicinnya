#ifndef COURT_H
#define COURT_H

#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <sys/time.h>

#include "Concave.h"
#include "Point.h"

#define COURT_STYLE "fill:rgb(224,192,255);stroke-width:1;stroke:rgb(0,0,0)"
#define COURT_COLUMN_STYLE "fill:rgb(0,0,0);stroke-width:0.125;stroke:rgb(0,0,0)"
#define GRID_STYLE "stroke:rgb(96,96,96);stroke-width:0.125"
#define COURT_DIM_MAX 5
#define COURT_DIM_MIN 1
#define MAX_RATIO 3
#define RSEED 717
#define SCALE_FACTOR 20
#define BUILDING_DEPTH_MIN 1
#define BUILDING_DEPTH_MAX 2
#define WALKWAY_LENGTH_MIN BUILDING_DEPTH_MIN
#define WALKWAY_LENGTH_MAX BUILDING_DEPTH_MIN
#define MAX_X 180
#define MAX_Y 80

#define COURT_GRID_INTERVAL 0.25
#define COURT_COLUMN_INTERVAL 0.5
#define COURT_COLUMN_OFFSET COURT_GRID_INTERVAL

#define COURT_COLUMN_SIZE 0.125

class Court {
private:
	std::map<Axis, std::vector<unsigned int> > edges;
	std::set<Court *> adjacent;
	unsigned int index; // FIXME: probably remove once debugged

	static void swap(unsigned int &num1, unsigned int &num2);

	static std::map<Direction, unsigned int> positionIndexOf;
	static std::map<Direction, unsigned int> createPositionIndexOf(){
		std::map<Direction, unsigned int> m;
		m[EAST] = 1;
		m[SOUTH] = 1;
		m[WEST] = 0;
		m[NORTH] = 0;
		return m;
	}

public:
	Court(Axis primaryAxis, unsigned int primary1, unsigned int primary2, unsigned int cross1, unsigned int cross2, unsigned int ind); // FIXME: rename consistently
	~Court();
	unsigned int getEdge(Direction dir);
	unsigned int getIndex(); // FIXME:
	void addAdjacent(Court * c);
	unsigned int countAdjacent();

	bool hasOnPerimeter(Axis primaryAxis, unsigned int primaryCoord, unsigned int crossCoord);
	bool resolveCollision(Axis primaryAxis, unsigned int &primaryLowerProposed, unsigned int &primaryHigherProposed, unsigned int &crossLowerProposed, unsigned int &crossHigherProposed);
	bool adjacentTo(Court * that, Direction &side, unsigned int &lowerBound, unsigned int &upperBound);

	static unsigned int getMinSecondDimension(unsigned int first);
	static unsigned int getMaxSecondDimension(unsigned int first);

	void toFile(std::ostream &file);
};

#endif
