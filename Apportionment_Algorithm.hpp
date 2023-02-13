#ifndef APPORTIONMENT_ALGORITHM_H
#define APPORTIONMENT_ALGORITHM_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


namespace Apportionment_Algorithm
{
	//compares strings
	bool compare(pair<string, pair<int, float>>&, pair<string, pair<int, float>>&);

	//reorders states in alphabetical order
	void sort_alphabetically(vector<pair<string, pair<int, float>>>&);

	//finds the max float in the vector and adds one to the int in the pair, set float to zero
	void max_float(vector<pair<string, pair<int, float>>>&);

	/*Takes a CVS file of state namesand their populations
	and creates a new CVS file that has the state names in
	alphabetical order with a number of representatives
	calculated by Hamilton's Apportionment Algorithm */
	void hamilton_algorithm(ifstream&, ofstream&, int);

	/*Takes a CVS file of state namesand their populations
	and creates a new CVS file that has the state names in
	alphabetical order with a number of representatives
	calculated by Huntington-Hill's Apportionment Algorithm */
	//void huntington_hill_algorithm(ifstream&, ofstream&, int);

	void Apportionment_Algorithm(ifstream&, ofstream&, int, string);
};


#endif

