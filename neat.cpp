#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <list>

#define INF 999999999

using namespace std;

typedef  unsigned long long int ulli;

int M = 60;

void updateWTI(string, vector<string>&, vector<ulli>&, vector<int>&, bool); // Time Complexity → O(M)
int  lineCost(int, int, vector<string> &); // Time Complexity → O(M)
int  getCost(int, vector<ulli> &); // Time Complexity → O(1)
void printWTI(vector<string>& W, vector<ulli>& T, vector<int>& I); // Time Complexity → O(N)

int main(int argc, char** argv) {
	ifstream		fin;
	ofstream		fout;
	string			str;
	vector<string>	W;	
	vector<ulli>	T;  
	vector<int>		I;
	list<string> 	solution;
	int 			cost;

	/* Open File if it has been passed correctly */
	if(argc < 2 || argc > 3){                                          // O(1)
		cerr << "Usage: " << argv[0] << " <file> [max width]" << endl;
		exit(1);
	} else {
		fin.open(argv[1]);                                             // O(1)
		if( fin.fail() ){                                              // O(1)
			cerr << "Could not open " << argv[1] << endl;
			exit(1);
		}
		fout.open("output.txt");                                       // O(1)
		if( fin.fail() ){                                              // O(1)
			cerr << "Could not open output" << endl;
			exit(1);
		}
		if(argc == 3)                                                  // O(1)
			sscanf(argv[2], "%d", &M);
	}

	/* Read words and build up T, I */
	while( fin >> str ) {               // O(N)
		updateWTI(str, W, T, I, false); // └ O(M)
	}

	/* Redo the last word, knowing it will be on last line */
	W.pop_back();                  // O(1)
	T.pop_back();                  // O(1)
	I.pop_back();                  // O(1)
	updateWTI(str, W, T, I, true); // O(M)
	
	/* Construct list of numbers in reverse, each number is how many words to print before a \n */
	cost = T.back();                               // O(1)
	int nextBreak = I.back();                      // O(1)
	list<string>::iterator lit = solution.begin(); // O(1)
	for(int i = W.size()-1; i>=0; i--){            // O(N)
		lit = solution.insert(lit, W[i]);          // ├ O(1) 
		if(i == nextBreak && i != 0){              // ├ O(1)
			lit = solution.insert(lit, "\n");      // ├ O(1)
			nextBreak = I[i-1];                    // └ O(1)
		}
	}
	
	/* print out the list of words with newlines in place */
	fout << cost << "\n";                 // O(1)
	for(; lit != solution.end(); ++lit) { // O(N)
		fout<<( *lit );                   // ├ O(1)
		if( *lit != "\n" )                // ├ O(1)
			fout<<" ";                    // └ O(1)
	}
	fout << endl;                         // O(1)

	fin.close(); // O(1)  
	fout.close(); // O(1)  
	
	return 0; // O(1)  
}

/* Prints out all WCI values for each word processed */
/* Doesn't consider the last line pentaly-free       */
void printWTI(vector<string>& W, vector<ulli>& T, vector<int>& I) { // Time Complexity → O(N)
	for(int i=0; i<W.size(); i++) {                                 // O(N)
		cout<<setw(2)<<i<<":"<<setw(9)<<W[i]<<" T:"<<setw(3)<<T[i]; // ├ O(1)
		cout<<" I:"<<setw(1)<<I[i]<<endl;                           // └ O(1)
	}
}

/* Calculates T(0,i) where i is index of word added to words[] */
void updateWTI(string word, vector<string>& W, vector<ulli>& T, vector<int>& I, bool last) { // Time Complexity → O(M)
	int i, j, nlc, minK, minT, thisT;       // O(1)
	W.push_back(word);                      // O(1)
	if(W.size() == 1) {                     // O(1)
		if(last){                           // O(1)
			T.push_back(0);                 // O(1)
			T.push_back(0);                 // O(1)
		} else {                            //
			T.push_back(lineCost(0, 0, W)); // O(1)
			I.push_back(0);                 // O(1)
		}
	} else {
		i = j = W.size() - 1;                       // O(1)
		minT = INF;                                 // O(1)
		while( (nlc = lineCost(i, j, W)) != INF ) { // O(M)
			if(last){                               // ├ O(1)
				thisT = getCost(i-1, T);            // ├ O(1)
			} else {                                // │
				thisT = getCost(i-1, T) + nlc;      // ├ O(1)
			}                                       // │
			if( thisT < minT ){                     // ├ O(1)
				minT = thisT;                       // ├ O(1)
				minK = i;                           // ├ O(1)
			}                                       // │
			i--;                                    // └ O(1)
		}
		T.push_back(minT);                          // O(1)
		I.push_back(minK);                          // O(1)
	}
}

// A wrapper function to handle costs[i] when i < 0
int getCost(int index, vector<ulli> &costs){ // Time complexity →  Constant
	if(index < 0) {          // O(1)
		return 0;            // O(1)
	} else {
		return costs[index]; // O(1)
	}
}

/* Returns cost of words [i,j] from words on a line together */
/* Words must contain at least j+1 entries and i<=j          */
int lineCost(int i, int j, vector<string> &W){ // Time Complexity →  O(M)
	int extra;
	if(W.size() < j+1 || i > j || i < 0){ // O(1)
		return INF;
	} else {
		extra = M - (j - i);              // O(1)
		for(int k=i; k<=j; k++) {         // O(M÷2) →  O(M)
			extra -= W[k].length();       // └ O(1)
		}
	}
	if(extra < 0) {
		return INF;                       // O(1)
	} else {
		return extra * extra * extra;     // O(1)
	}
}

