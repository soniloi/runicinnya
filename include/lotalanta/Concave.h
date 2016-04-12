#ifndef CONCAVE_H
#define CONCAVE_H

#include <map>
#include <sstream> // FIXME: debug

#include "DirectionMappings.h"
#include "Point.h"

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
