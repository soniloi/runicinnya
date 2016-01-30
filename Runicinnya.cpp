#include <fstream>
#include <iostream>

#include "City.h"

using namespace std;

void writeFile(City c){
	ofstream file;
	file.open("output.svg", ofstream::out);
	if (!file.good()){
		cerr << "Error opening output file, exiting." << endl;
		exit(1);
	}

	// Starting boilerplate
	file << "<?xml version=\"1.0\"?>" << endl;
	file << "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width=\"" << (WIDTH * SCALE_FACTOR) << "\" height=\"" << (HEIGHT * SCALE_FACTOR) << "\" style=\"background: " << BG_COLOUR << "\">" << endl;

	// Grid
	for(int i = 0; i < (MAX_Y * SCALE_FACTOR); i+=SCALE_FACTOR){
		file << "<line x1=\"" << 0 << "\" y1=\"" << i << "\" x2=\"" << (MAX_X * SCALE_FACTOR) << "\" y2=\"" << i << "\" style=\"stroke:rgb(192,224,255);stroke-width:0.25\" />" << endl;
	}
	for(int i = 0; i < (MAX_Y * SCALE_FACTOR); i+=(SCALE_FACTOR*10)){
		file << "<line x1=\"" << 0 << "\" y1=\"" << i << "\" x2=\"" << (MAX_X * SCALE_FACTOR) << "\" y2=\"" << i << "\" style=\"stroke:rgb(192,224,255);stroke-width:1\" />" << endl;
		file << "<text x=\"" << 1180 << "\" y=\"" << (i-8) << "\" font-family=\"sans-serif\" font-size=\"12px\" fill=\"gray\">" << (i/SCALE_FACTOR) << "</text>" << std::endl;
	}

	for(int i = 0; i < (MAX_X * SCALE_FACTOR); i+=SCALE_FACTOR){
		file << "<line x1=\"" << i << "\" y1=\"" << 0 << "\" x2=\"" << i << "\" y2=\"" << (MAX_Y * SCALE_FACTOR) << "\" style=\"stroke:rgb(192,224,255);stroke-width:0.25\" />" << endl;
	}
	for(int i = 0; i < (MAX_X * SCALE_FACTOR); i+=(SCALE_FACTOR*10)){
		file << "<line x1=\"" << i << "\" y1=\"" << 0 << "\" x2=\"" << i << "\" y2=\"" << (MAX_Y * SCALE_FACTOR) << "\" style=\"stroke:rgb(192,224,255);stroke-width:1\" />" << endl;
		file << "<text x=\"" << (i+8) << "\" y=\"" << 392 << "\" font-family=\"sans-serif\" font-size=\"12px\" fill=\"gray\">" << (i/SCALE_FACTOR) << "</text>" << std::endl;
	}

	// City
	c.toFile(file);

	// Ending boilerplate
	file << "</svg>" << endl;

	file.close();
}

int main(int argc, char ** argv){
	if(argc < 2){
		cout << "Usage: " << argv[0] << " <number of courts>." << endl;
		exit(1);
	}

	int noCourts = atoi(argv[1]);
	if(noCourts < 1){
		cout << "Error: enter a positive integer value for number of courts." << endl;
		exit(1);
	}

	City c;
	c.generate(noCourts);
	writeFile(c);
	return 0;
}
