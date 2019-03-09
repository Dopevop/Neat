/* Devon O'Connor */
/* March 8th, 2019 */
/* The algorithm runs in O(NM) time where N is the number of words and M is the max line width. */

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

void updateWTI(string, vector<string>&, vector<ulli>&, vector<int>&, bool); // T:O(M)
int  lineCost(int, int, vector<string> &);                                  // T:O(M)
int  getCost(int, vector<ulli> &);                                          // T:O(1)
void printWTI(vector<string>&, vector<ulli>&, vector<int>&);                // T:O(N)
int main(int argc, char** argv) {                                           // T:O(NM)
	ifstream		fin;
	ofstream		fout;
	string			str;
	vector<string>	W;	
	vector<ulli>	T;  
	vector<int>		I;
	list<string> 	solution;
	int 			cost;

	/* Open File if it has been passed correctly */
	if(argc < 2 || argc > 3){                                          // T:O(1)
		cerr << "Usage: " << argv[0] << " <file> [max width]" << endl;
		exit(1);
	} else {
		fin.open(argv[1]);                                             // T:O(1)
		if( fin.fail() ){                                              // T:O(1)
			cerr << "Could not open " << argv[1] << endl;
			exit(1);
		}
		fout.open("output.txt");                                       // T:O(1)
		if( fin.fail() ){                                              // T:O(1)
			cerr << "Could not open output" << endl;
			exit(1);
		}
		if(argc == 3)                                                  // T:O(1)
			sscanf(argv[2], "%d", &M);
	}

	/* Read words and build up T, I */
	while( fin >> str ) {               // T:O(N)
		updateWTI(str, W, T, I, false); //   └→ O(M)
	}

	/* Redo the last word, knowing it will be on last line */
	W.pop_back();                  // T:O(1)
	T.pop_back();                  // T:O(1)
	I.pop_back();                  // T:O(1)
	updateWTI(str, W, T, I, true); // T:O(M)
	
	/* Construct list of numbers in reverse, each number is how many words to print before a \n */
	cost = T.back();                               // T:O(1)
	int nextBreak = I.back();                      // T:O(1)
	list<string>::iterator lit = solution.begin(); // T:O(1)
	for(int i = W.size()-1; i>=0; i--){            // T:O(N)
		lit = solution.insert(lit, W[i]);          //   ├→ O(1) 
		if(i == nextBreak && i != 0){              //   ├→ O(1)
			lit = solution.insert(lit, "\n");      //   ├→ O(1)
			nextBreak = I[i-1];                    //   └→ O(1)
		}
	}
	
	/* print out the list of words with newlines in place */
	fout << cost << "\n";                 // T:O(1)
	for(; lit != solution.end(); ++lit) { // T:O(N)
		fout<<( *lit );                   //   ├→ O(1)
		if( *lit != "\n" )                //   ├→ O(1)
			fout<<" ";                    //   └→ O(1)
	}
	fout << endl;                         // T:O(1)

	fin.close(); // T:O(1)  
	fout.close(); // T:O(1)  
	
	return 0; // T:O(1)  
}

/* Prints out all WCI values for each word processed */
/* Doesn't consider the last line pentaly-free       */
void printWTI(vector<string>& W, vector<ulli>& T, vector<int>& I) { // Time Complexity → T:O(N)
	for(int i=0; i<W.size(); i++) {                                 // T:O(N)
		cout<<setw(2)<<i<<":"<<setw(9)<<W[i]<<" T:"<<setw(3)<<T[i]; //   ├→ T:O(1)
		cout<<" I:"<<setw(1)<<I[i]<<endl;                           //   └→ T:O(1)
	}
}

/* Calculates T(0,i) where i is index of word added to words[] */
void updateWTI(string word, vector<string>& W, vector<ulli>& T, vector<int>& I, bool last) { // Time Complexity → T:O(M)
	int i, j, nlc, minK, minT, thisT;       // T:O(1)
	W.push_back(word);                      // T:O(1)
	if(W.size() == 1) {                     // T:O(1)
		if(last){                           // T:O(1)
			T.push_back(0);                 // T:O(1)
			T.push_back(0);                 // T:O(1)
		} else {                            //
			T.push_back(lineCost(0, 0, W)); // T:O(1)
			I.push_back(0);                 // T:O(1)
		}
	} else {
		i = j = W.size() - 1;                       // T:O(1)
		minT = INF;                                 // T:O(1)
		while( (nlc = lineCost(i, j, W)) != INF ) { // T:O(M)
			if(last){                               //   ├→ O(1)
				thisT = getCost(i-1, T);            //   ├→ O(1)
			} else {                                //   │
				thisT = getCost(i-1, T) + nlc;      //   ├→ O(1)
			}                                       //   │
			if( thisT < minT ){                     //   ├→ O(1)
				minT = thisT;                       //   ├→ O(1)
				minK = i;                           //   ├→ O(1)
			}                                       //   │
			i--;                                    //   └→ O(1)
		}
		T.push_back(minT);                          // T:O(1)
		I.push_back(minK);                          // T:O(1)
	}
}

// A wrapper function to handle costs[i] when i < 0
int getCost(int index, vector<ulli> &costs){ // Time complexity →  Constant
	if(index < 0) {          // T:O(1)
		return 0;            // T:O(1)
	} else {
		return costs[index]; // T:O(1)
	}
}

/* Returns cost of words [i,j] from words on a line together */
/* Words must contain at least j+1 entries and i<=j          */
int lineCost(int i, int j, vector<string> &W){ // Time Complexity →  T:O(M)
	int extra;
	if(W.size() < j+1 || i > j || i < 0){ // T:O(1)
		return INF;
	} else {
		extra = M - (j - i);              // T:O(1)
		for(int k=i; k<=j; k++) {         // T:O(M÷2) →  T:O(M)
			extra -= W[k].length();       //   └→ O(1)
		}
	}
	if(extra < 0) {
		return INF;                       // T:O(1)
	} else {
		return extra * extra * extra;     // T:O(1)
	}
}

