#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
using namespace std;

int main(int argc, char** argv) {
	ifstream fin;

	/* Check that a file name has been passed */
	if(argc != 2){
		cerr << "Usage: " << argv[0] << " <file>" << endl;;
		exit(1);
	} else {
		/* Open the file for reading */
		fin.open(argv[1]);
		if( fin.fail() ){
			cerr << "Could not open " << argv[1] << endl;
			exit(1);
		}
	}

	vector<int> T;
	vector<int> k;
	

	T.push_back(5);


	fin.close();
	
	return 0;
}
