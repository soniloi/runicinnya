#ifndef CONCAVE_H
#define CONCAVE_H

#include <map>
#include "Point.h"

enum Direction{NORTH, EAST, SOUTH, WEST, NUM_DIRECTIONS};

class Concave{
private:
	std::map<Axis, unsigned int> coords;
	Direction rightEdge;

public:
	Concave(Axis primaryAxis, unsigned int val1, unsigned int val2, Direction dir);
	unsigned int getCoord(Axis a);
	Direction getRightEdge();
};

#endif
