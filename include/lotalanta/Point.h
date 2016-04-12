#ifndef POINT_H
#define POINT_H

#include <map>
#include <iostream> // FIXME: debug

#include "DirectionMappings.h"

class Point{
private:
	std::map<Axis, unsigned int> coords;

public:
	Point(Axis primaryAxis, unsigned int primaryCoord, unsigned int crossCoord);
	unsigned int getCoord(Axis a);
	bool equals(Point * other);
};

#endif
