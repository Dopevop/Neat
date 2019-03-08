#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iomanip>


#define INF 999999999

using namespace std;

const int M = 10;

void updateWCI(string, vector<string>&, vector<int>&, vector<int>&);
int  getLineCost(int, int, vector<string> &);
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

/* Calculates T(0,i) where i is index of newWord added to words[] */
void updateWCI(string newWord, vector<string>& words, vector<int>& costs, vector<int>& indices) {
	int i, j, newLineCost, minK, minT, thisT;
	words.push_back(newWord);
	if(words.size() == 1) {
		i = j = 0; 
		costs.push_back(getLineCost(i, j, words));
		indices.push_back(i);
	} else {
		j = words.size() - 1;
		i = j;
		minT = INF;
		while( (newLineCost = getLineCost(i, j, words)) != INF ) {
			thisT = getCost(i-1, costs); // Don't add last line to cost
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

// A wrapper function to handle costs[i] when i < 0
int getCost(int index, vector<int> &costs){
	if(index < 0) {
		return 0;
	} else {
		return costs[index];
	}
}

/* Returns cost of words [i,j] from words on a line together */
/* Words must contain at least j+1 entries and i<=j          */
int getLineCost(int i, int j, vector<string> &words){	
	int extra;
	if(words.size() < j+1 || i > j){    // Invalid indices
		return -1;
	} else {                            // Calculate E(i,j)
		extra = M - (j - i);
		for(int k=i; k<=j; k++) {
			extra -= words[k].length();
		}
	}
	if(extra < 0) {                     // Words don't fit on line
		return INF;
	} else {                            // Otherwise
		return extra * extra * extra;
	}
}

