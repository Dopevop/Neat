#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <list>

#define INF 999999999

using namespace std;

int M = 60;

void updateWCI(string, vector<string>&, vector<int>&, vector<int>&, bool);
int  lineCost(int, int, vector<string> &);
int  getCost(int, vector<int> &);
void printWTI(vector<string>& W, vector<int>& T, vector<int>& I);

int main(int argc, char** argv) {
	ifstream		fin;
	ofstream		fout;
	string			str;
	vector<string>	W;	
	vector<int>		T;    // Total up to T[i], i != n
	vector<int>		I;
	vector<int>		altT; // Total up to T[i], i == n
	vector<int>		altI;
	list<string> 	solution;
	int 			cost;

	/* Open File if it has been passed correctly */
	if(argc < 2 || argc > 3){
		cerr << "Usage: " << argv[0] << " <file> [max width]" << endl;;
		exit(1);
	} else {
		fin.open(argv[1]);
		if( fin.fail() ){
			cerr << "Could not open " << argv[1] << endl;
			exit(1);
		}
		fout.open("output.txt");
		if( fin.fail() ){
			cerr << "Could not open output" << endl;
			exit(1);
		}
		if(argc == 3)
			M = stoi( string(argv[2]) );
	}

	/* Read words and build up T, I */
	while( fin >> str ) {
		updateWCI(str, W, T, I, false);
	}

	/* Redo the last word, knowing it will be on last line */
	W.pop_back();
	T.pop_back();
	I.pop_back();
	updateWCI(str, W, T, I, true);
	
	/* Construct list of numbers in reverse, each number is how many words to print before a \n */
	cost = T.back();
	int nextBreak = I.back();
	list<string>::iterator lit = solution.begin();
	for(int i = W.size()-1; i>=0; i--){
		lit = solution.insert(lit, W[i]);
		if(i == nextBreak && i != 0){
			lit = solution.insert(lit, "\n");
			nextBreak = I[i-1];
		}
	}
	
	/* print out the list of words with newlines in place */
	fout << cost << "\n";
	for(; lit != solution.end(); ++lit) {
		fout<<( *lit );
		if(*lit != "\n") 
			fout<<" ";
	}
	fout << endl;

	fin.close();
	
	return 0;
}

void printWTI(vector<string>& W, vector<int>& T, vector<int>& I) {
	for(int i=0; i<W.size(); i++) {
		cout<<setw(2)<<i<<":"<<setw(9)<<W[i]<<" T:"<<setw(3)<<T[i];
		cout<<" I:"<<setw(1)<<I[i]<<endl;
	}
}

/* Calculates T(0,i) where i is index of word added to words[] */
void updateWCI(string word, vector<string>& W, vector<int>& T, vector<int>& I, bool last) { 
	int i, j, nlc, minK, minT, thisT;
	W.push_back(word);
	if(W.size() == 1) {
		if(last){
			T.push_back(0);
			T.push_back(0);
		} else {
			T.push_back(lineCost(0, 0, W));
			I.push_back(0);
		}
	} else {
		i = j = W.size() - 1;
		minT = INF;
		while( (nlc = lineCost(i, j, W)) != INF ) {
			if(last){
				thisT = getCost(i-1, T);
			} else {
				thisT = getCost(i-1, T) + nlc; 
			}
			if( thisT < minT ){
				minT = thisT;
				minK = i;
			}
			i--;
		}
		T.push_back(minT);
		I.push_back(minK);
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
int lineCost(int i, int j, vector<string> &W){	
	int extra;
	if(W.size() < j+1 || i > j || i < 0){    // Invalid indices
		return INF;
	} else {                            // Calculate E(i,j)
		extra = M - (j - i);
		for(int k=i; k<=j; k++) {
			extra -= W[k].length();
		}
	}
	if(extra < 0) {                     // Words don't fit on line
		return INF;
	} else {                            // Otherwise
		return extra * extra * extra;
	}
}

