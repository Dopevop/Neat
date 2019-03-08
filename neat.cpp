#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iomanip>


#define INF 999999999

using namespace std;

const int M = 10;

void updateWCI(string, vector<string>&, vector<int>&, vector<int>&);
int  getLineCost(int, int, vector<string> *);
int  getCost(int, vector<int> &);

int main(int argc, char** argv) {
	ifstream		fin;
	string			str;
	vector<string>	words;	
	vector<int>		costs;
	vector<int>		indices;

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
		updateWCI(str, words, costs, indices);
	}

	for(int i=0; i<words.size(); i++) {
		cout << setw(2) << i << setw(10) << words[i];
		cout << " Cost:" << setw(4) << getCost(i, costs);
		cout << " Index: " << indices[i] << endl;
	}

	fin.close();
	
	return 0;
}

/* 			{ 0											if j < i                      */
/* T(i,j) = { C(i,j)									if i = j                      */
/* 			{ min( 0<=k<=j ){ T(i, k-1) + C(k, j) }		otherwise                     */
/* Returns the minimized cost for arranging words 0 through i in lines of max width M */
/* Assumes that the costs have already been determined up to words 0 through i-1      */
void updateWCI(string newWord, vector<string>& words, vector<int>& costs, vector<int>& indices) {
	int i, j, prevTotal, thisTotal, newLineCost;

	words.push_back(newWord);
	if(words.size() == 1) {
		// adding first word to words[]
		i = j = 0; 
		costs.push_back(getLineCost(i, j, &words));
		indices.push_back(i);
	} else {
		// Check if newWord fits on last line
		i = indices.back();
		j = words.size() - 1;
		newLineCost = getLineCost(i, j, &words);
		if(newLineCost != INF) { 
			// newWord fits 
			prevTotal = getCost(i-1, costs);
			thisTotal = prevTotal + newLineCost;
			costs.push_back(thisTotal);
			indices.push_back(i);
		} else {
			i = j;
			int minK, thisT;
			int minT = INF;
			while( (newLineCost = getLineCost(i, j, &words)) != INF ) {
				thisT = getCost(i-1, costs) + newLineCost;
				if( thisT < minT ){
					minT = thisT;
					minK = i;
				}
				i--;
			}
			costs.push_back(minT);
			indices.push_back(minK);
		}
	}
}

// A wrapper function to handle costs[i] when i < 0
int getCost(int index, vector<int> &costs){
	if(index < 0) {
		return 0;
	} else {
		return (costs)[index];
	}
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

