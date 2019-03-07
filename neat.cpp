#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
using namespace std;

struct CostIndex {
	int cost;
	int index;
};

struct CostIndex *getTotalCost( int );

int main(int argc, char** argv) {

	ifstream       				fin;
	string         				thisWord;
	vector<struct CostIndex *>	CI;
	vector<string> 				words;	

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
		/* Add word to words vector */
		words.push_back(thisWord);

		/* Calculate T(0,i) and k, store in totalCost and lineStart */
		CostIndex *ci = getTotalCost( words.size() );
		CI.push_back(ci);
		CI.push_back(ci);
	}

	/* Print all costs and indices stored in CI */
	for(int i=0; i<CI.size(); i++) {
		cout << CI[i]->cost << CI[i]->index << endl;
	}

	fin.close();
	
	return 0;
}

/* Returns the minimized cost for arranging words 0 through i in lines of max width M */
/* Assumes that the costs have already been determined up to words 0 through i-1 */
struct CostIndex *getTotalCost(int i) {
	struct CostIndex *p = (struct CostIndex *) malloc(sizeof(struct CostIndex));
	p->cost = 0;
	p->index = 0;
	return p;
}
