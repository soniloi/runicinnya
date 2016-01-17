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

	c.toFile(file);

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
