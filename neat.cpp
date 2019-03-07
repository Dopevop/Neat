#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
using namespace std;

void error(string str){
	cout << str << endl;;
	exit(1);
}


int main(int argc, char** argv) {
	ifstream fin;

	/* Check that a file name has been passed */
	if(argc != 2){
		error(string("Usage: ") + argv[0] + " <file>");
	} else {
		/* Open the file for reading */
		fin.open(argv[1]);
	}

	vector<int> T;
	vector<int> k;
	

	T.push_back(5);


	fin.close();
	
	return 0;
}
