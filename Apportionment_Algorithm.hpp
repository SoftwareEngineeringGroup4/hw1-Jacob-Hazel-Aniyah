#ifndef APPORTIONMENT_ALGORITHM_H
#define APPORTIONMENT_ALGORITHM_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

namespace Apportionment_Algorithm
{

	void Apportionment_Algorithm(ifstream&, ofstream&, int, string);

	//compares strings 
	bool compare_1(pair<string, pair<int, float>>&, pair<string, pair<int, float>>&);
	bool compare_2(pair<string, int>&, pair<string, int>&);

	//reorders states in alphabetical order
	void sort_alphabetically_1(vector<pair<string, pair<int, float>>>&);
	void sort_alphabetically_2(vector<pair<string, int>>&);

	//finds the max float in the vector and adds one to the int in the pair, set float to zero
	void max_float(vector<pair<string, pair<int, float>>>&);

	/*Takes a CVS file of state namesand their populations
	and creates a new CVS file that has the state names in
	alphabetical order with a number of representatives
	calculated by Hamilton's Apportionment Algorithm */
	void hamilton_algorithm(ifstream&, ofstream&, int);


	// formula for calculating priority score of a state given pop. and reps it already has
	double priority(int, int);

	// finds the max priority of the vector, adds 1 to rep count, updates priority
	void max_prio(vector<pair<int, pair<int, double>>>&);

	/*Takes a CVS file of state namesand their populations
	and creates a new CVS file that has the state names in
	alphabetical order with a number of representatives
	calculated by Huntington-Hill's Apportionment Algorithm */
	void huntington_hill_algorithm(ifstream&, ofstream&, int);

	int Entry_Message_1();

	string Entry_Message_2();

};


#endif

