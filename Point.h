#ifndef POINT_H
#define POINT_H

#include <map>
#include <iostream> // FIXME: debug

enum Axis{XAXIS, YAXIS};

class Point{
private:
	std::map<Axis, unsigned int> coords;

public:
	Point(Axis a1, unsigned int val1, Axis a2, unsigned int val2);
	unsigned int getCoord(Axis a);
	bool equals(Point * other);
};

#endif
