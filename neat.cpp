#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
using namespace std;

int main(int argc, char** argv) {

	ifstream       fin;
	int            wordsRead = 0;
	string         thisWord;
	vector<int>    totalCost; /* Holds the total cost of arranging words [0,i] */
	vector<int>    lineStart; /* Holds the index of the word starting the i-th word's line */
	vector<string> words;	  /* Holds the words read from the file */

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

	/* Read all words from input file */
	while( fin >> thisWord ) {
		words.push_back(thisWord);
	}

	for(int i=0; i<5; i++) {
		cout << words[i] << endl;
	}



	fin.close();
	
	return 0;
}
