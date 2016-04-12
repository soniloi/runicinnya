#ifndef WALKWAY_H
#define WALKWAY_H

#include "Court.h"

#define WALKWAY_STYLE "fill:rgb(224,192,255);stroke-width:2;stroke:rgb(224,192,255)"
//#define WALKWAY_STYLE "fill:rgb(240,224,255);stroke-width:1;stroke:rgb(0,0,0)"
#define WALKWAY_EDGE_STYLE "stroke:rgb(31,31,31);stroke-width:0.5;stroke-linecap=\'round\'"
#define WALKWAY_WIDTH COURT_COLUMN_OFFSET

class Walkway{
private:
	Direction direction;
	Court * court1;
	Court * court2;
	unsigned int leftEdge;
	bool up;

public:
	Walkway(Direction dir, Court * c1, Court * c2, unsigned int le, bool isUp);
	void toFile(std::ostream &file);
};

#endif
