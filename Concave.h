#ifndef CONCAVE_H
#define CONCAVE_H

#include <map>
#include <sstream> // FIXME: debug

#include "Point.h"

enum Direction{NORTH, EAST, SOUTH, WEST, NUM_DIRECTIONS};

class Concave{
private:
	std::map<Axis, unsigned int> coords;
	Direction rightEdge;

public:
	Concave(Axis primaryAxis, unsigned int primaryCoord, unsigned int crossCoord, Direction dir);
	unsigned int getCoord(Axis a);
	Direction getRightEdge();
	std::string toString();
};

#endif
