//-----------------------------------------------------------------------------
// Name: Lia Cui
// CRUZID: ljcui
// Assignment Name: PA8
//
//-----------------------------------------------------------------------------

#include <fstream>
#include <string>
#include <iostream>
#include"Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s input output\n", argv[0]);
		exit(1);
	}

	ifstream infile;
	ofstream outfile;
	infile.open(argv[1]);
	outfile.open(argv[2]);

	string sbuff;
	Dictionary D;
	for(int i = 1; getline(infile, sbuff); i++){
		D.setValue(sbuff, i);
	}

	
	outfile << D.to_string() << endl;
	outfile.flush();
	outfile << D.pre_string() << endl;
	outfile.flush();

	infile.close();
	outfile.close();
	return(0);
}

