#include "Apportionment_Algorithm.hpp"


int main()
{
	//opens the csv file to start reading
	string file_name = "census2020";
	ifstream infile(file_name + ".csv");
	if (!infile)
		cout << "> Error opening file\n";

	//creates a new csv file that will be written on
	string new_file_name = file_name + " + reps.csv";
	ofstream outfile(new_file_name);
	if (!outfile)
		cout << "> Error opening new file\n";


	int number_of_representatives;
	string type_of_algorithm;

	int default_reps = 435;
	string type_ham = "Hamilton";
	string type_hunt = "Huntington-Hill";

	try
	{
		Apportionment_Algorithm Reps(infile, outfile, 437, " ");
	}
	catch (runtime_error& error)
	{
		cout << error.what();
	}
}