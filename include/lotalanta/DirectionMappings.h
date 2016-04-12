#ifndef DIRECTIONMAPPINGS_H
#define DIRECTIONMAPPINGS_H

#include <map>

#define POLARITY_POSITIVE 1
#define POLARITY_NEGATIVE -1

enum Axis{XAXIS, YAXIS};
enum Direction{NORTH, EAST, SOUTH, WEST, NUM_DIRECTIONS};

class DirectionMappings {
private:
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

	static std::map<Direction, Axis> axisOf;
	static std::map<Direction, Axis> createAxisOf(){
		std::map<Direction, Axis> m;
		m[EAST] = XAXIS;
		m[SOUTH] = YAXIS;
		m[WEST] = XAXIS;
		m[NORTH] = YAXIS;
		return m;
	}

public:
	static Direction getLeftOf(Direction dir);
	static Direction getRightOf(Direction dir);
	static Direction getOppositeOf(Direction dir);
	static int getPolarityOf(Direction dir);
	static Axis getAxisOf(Direction dir);
};

#endif

