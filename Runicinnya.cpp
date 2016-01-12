#include <fstream>
#include <iostream>

#include "City.h"

using namespace std;

void writeFile(City c){
	ofstream file;
	file.open("output.svg", ofstream::out);
	if (!file.good()){
		cerr << "Error opening output file, exiting." << endl;
	}

	c.toFile(file);

	file.close();
}

int main(){
	City c;
	c.generate(6);
	writeFile(c);
	return 0;
}
