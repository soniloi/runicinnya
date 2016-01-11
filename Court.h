#ifndef COURT_H
#define COURT_H

#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <sys/time.h>

#include "Concave.h"
#include "Point.h"

#define COURT_STYLE "fill:rgb(255,128,255);stroke-width:1;stroke:rgb(0,0,0)"
#define DIM_MAX 5
#define DIM_MIN 1
#define MAX_RATIO 3
#define RSEED 717
#define SCALE_FACTOR 10
#define BUILDING_DEPTH_MIN 1
#define BUILDING_DEPTH_MAX 2
#define MAX_X 180
#define MAX_Y 80

class Court {
private:
	std::map<Direction, unsigned int> edges;

	unsigned int getMinSecondDimension(unsigned int first);
	unsigned int getMaxSecondDimension(unsigned int first);

public:
	Court(Axis primaryAxis, unsigned int primary1, unsigned int primary2, unsigned int cross1, unsigned int cross2);
	~Court();
	unsigned int getEdge(Direction dir);

	bool hasOnPerimeter(Axis normalAxis, unsigned int val1, unsigned int val2);

	void toFile(std::ostream &file);
};

#endif
