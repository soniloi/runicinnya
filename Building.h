#ifndef BUILDING_H
#define BUILDING_H

#include <fstream>
#include <iostream>
#include <map>
#include <random>
//#include <sys/time.h>

#include "Court.h" // FIXME: sort this out


#define BUILDING_STYLE "fill:rgb(192,255,255);stroke-width:1;stroke:rgb(0,0,0)"

class Building {
private:
	std::map<Axis, unsigned int> coords;
	std::map<Axis, unsigned int> dims;

public:
	Building(Axis primaryAxis, unsigned int primaryCoord, unsigned int crossCoord, unsigned int primaryDim, unsigned int crossDim);
	~Building();
	unsigned int getCoord(Axis a);
	unsigned int getDim(Axis a);

	void toFile(std::ostream &file);
};

#endif
