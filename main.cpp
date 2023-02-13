#include "Apportionment_Algorithm.hpp"


int main()
{
	//opens the csv file to start reading
	string file_name;
	cout << "> Please type in the name of the csv file you wish to use exactly: ";
	cin >> file_name;
	cout << endl;
	ifstream infile(file_name + ".csv");
	if (!infile)
	{
		cout << "> Error opening file...\n> Exiting Program...\n";
		exit(1);
	}

	//creates a new csv file that will be written on
	string new_file_name = file_name + " + reps.csv";
	ofstream outfile(new_file_name);
	if (!outfile)
	{
		cout << "> Error opening new file...\n> Exiting Program...\n";
		exit(1);
	}

	int number_of_representatives = Apportionment_Algorithm::Entry_Message_1();

	string type_of_algorithm = Apportionment_Algorithm::Entry_Message_2();


	cout << "> Number of representatives used in algorithm will be : " << number_of_representatives << endl;
	cout << "> Type of algorithm used will be the \'" << type_of_algorithm << "\' method" << endl;
	cout << endl << "> Calculating.....\n\n\n";

	try
	{
		Apportionment_Algorithm::Apportionment_Algorithm(infile, outfile, number_of_representatives, type_of_algorithm);
		cout << endl << "> Finished :)\n\n\n";
	}
	catch (runtime_error& error)
	{
		cout << error.what();
	}
	infile.close();
	outfile.close();
	return 0;
}