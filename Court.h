#ifndef COURT_H
#define COURT_H

#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <sys/time.h>

#include "Concave.h"
#include "Point.h"

#define POLARITY_POSITIVE 1
#define POLARITY_NEGATIVE -1

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
#define MAX_X 180
#define MAX_Y 80

#define COURT_GRID_INTERVAL 0.25
#define COURT_COLUMN_INTERVAL 0.5
#define COURT_COLUMN_OFFSET COURT_GRID_INTERVAL

#define COURT_COLUMN_SIZE 0.125

class Court {
private:
	std::map<Axis, std::vector<unsigned int> > edges;
	unsigned int index; // FIXME: probably remove once debugged

	static void swap(unsigned int &num1, unsigned int &num2);

	static std::map<Direction, Axis> axisOf;
	static std::map<Direction, Axis> createAxisOf(){
		std::map<Direction, Axis> m;
		m[EAST] = XAXIS;
		m[SOUTH] = YAXIS;
		m[WEST] = XAXIS;
		m[NORTH] = YAXIS;
		return m;
	}

	static std::map<Direction, unsigned int> positionIndexOf;
	static std::map<Direction, unsigned int> createPositionIndexOf(){
		std::map<Direction, unsigned int> m;
		m[EAST] = 1;
		m[SOUTH] = 1;
		m[WEST] = 0;
		m[NORTH] = 0;
		return m;
	}

	static std::map<Direction, Direction> oppositeOf;
	static std::map<Direction, Direction> createOppositeOf(){
		std::map<Direction, Direction> m;
		m[EAST] = WEST;
		m[SOUTH] = NORTH;
		m[WEST] = EAST;
		m[NORTH] = SOUTH;
		return m;
	}

	static std::map<Direction, int> polarityOf;
	static std::map<Direction, int> createPolarityOf(){
		std::map<Direction, int> m;
		m[EAST] = POLARITY_POSITIVE;
		m[SOUTH] = POLARITY_POSITIVE;
		m[WEST] = POLARITY_NEGATIVE;
		m[NORTH] = POLARITY_NEGATIVE;
		return m;
	}

	static std::map<Direction, Direction> leftOf;
	static std::map<Direction, Direction> createLeftOf(){
		std::map<Direction, Direction> m;
		m[EAST] = NORTH;
		m[SOUTH] = EAST;
		m[WEST] = SOUTH;
		m[NORTH] = WEST;
		return m;
	}

	static std::map<Direction, Direction> rightOf;
	static std::map<Direction, Direction> createRightOf(){
		std::map<Direction, Direction> m;
		m[EAST] = SOUTH;
		m[SOUTH] = WEST;
		m[WEST] = NORTH;
		m[NORTH] = EAST;
		return m;
	}
public:
	Court(Axis primaryAxis, unsigned int primary1, unsigned int primary2, unsigned int cross1, unsigned int cross2, unsigned int ind); // FIXME: rename consistently
	~Court();
	unsigned int getEdge(Direction dir);
	unsigned int getIndex(); // FIXME:

	bool hasOnPerimeter(Axis primaryAxis, unsigned int primaryCoord, unsigned int crossCoord);
	bool containsPoint(Axis primaryAxis, unsigned int primaryCoord, unsigned int crossCoord);

	bool resolveCollision(Axis primaryAxis, unsigned int &primaryLowerProposed, unsigned int &primaryHigherProposed, unsigned int &crossLowerProposed, unsigned int &crossHigherProposed);

	bool adjacentTo(Court * that);

	static unsigned int getMinSecondDimension(unsigned int first);
	static unsigned int getMaxSecondDimension(unsigned int first);

	void toFile(std::ostream &file);
};

#endif
