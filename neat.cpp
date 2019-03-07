#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

#define INF 999999999

using namespace std;

const int M = 10;

int main(int argc, char** argv) {
	ifstream		fin;
	string			str;
	vector<string>	words;	
	vector<int>		costs;
	vector<int>		index;

	/* Open File if it has been passed correctly */
	if(argc != 2){
		cerr << "Usage: " << argv[0] << " <file>" << endl;;
		exit(1);
	} else {
		fin.open(argv[1]);
		if( fin.fail() ){
			cerr << "Could not open " << argv[1] << endl;
			exit(1);
		}
	}

	/* Read all words from input file */
	while( fin >> str ) {
		/* Add word to words vector */
		words.push_back(str);

		/* Calculate T(0,i) and k, store in totalCost and lineStart */
		CostIndex *ci = getTotalCost( words.size(), &CIVector );
		CIVector.push_back(ci);
	}

	/* Print cost of putting words 0->k 0<=k<=n on a line */
	for(int k=0; k<words.size(); k++) {
		cout << "C(0, " << k << "): " << getLineCost(0, k, &words) << endl;
	}

	fin.close();
	
	return 0;
}

/* 			{ 0											if i > j                      */
/* T(i,j) = { C(i,j)									if i = j                      */
/* 			{ min( 0<=k<=j ){ T(i, k-1) + C(k, j) }		otherwise                     */
/* Returns the minimized cost for arranging words 0 through i in lines of max width M */
/* Assumes that the costs have already been determined up to words 0 through i-1      */
/* And these costs are stored along with the corresponding indices in currCI 		  */
struct CostIndex *getTotalCost(int i, vector<struct CostIndex *> *CIVector) {
	struct CostIndex *p = (struct CostIndex *) malloc(sizeof(struct CostIndex));
	p->cost = 0;
	p->index = 0;
	return p;
}

/* 			{ inf       if E(i,j) < 0                                 */
/* C(i,j) = { 0         if j = n & E(i,n) >= 0                        */
/* 			{ E(i,j)^3  otherwise                                     */
/*																	  */
/* E(i,j) = M - (j - i) - Σ(length(words[k])) 						  */
/*																	  */
/* Returns cost of words [i,j] from words on a line together	      */
/* words must contain at least j+1 entries and i<=j					  */
int getLineCost(int i, int j, vector<string> *words){	
	int extra;
	if(words->size() < j+1 || i > j){
		return -1;
	} else {
		extra = M - (j - i);
		for(int k=i; k<=j; k++) {
			extra -= (*words)[k].length();
		}
	}
	if(extra < 0) {
		return INF;
	} else {
		return extra * extra * extra;
	}
}

