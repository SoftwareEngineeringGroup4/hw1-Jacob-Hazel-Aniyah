#include "Apportionment_Algorithm.hpp"


int main()
{
	
	string file_name, file_type;
	cout << "> Please type in the name of the csv file you wish to use exactly: ";
	cin >> file_name;
	cout << "> Please specify the file type (csv or xlsx): ";
	cin >> file_type;
	cout << endl;

	while (file_type != "csv" && file_type != "xlsx")
	{
		cout << "> Incorrect Syntax \n> Please type csv or xlsx: ";
		cin >> file_type;
	}

	string hold = file_name;

	// creates a copy of the xlsx file as a csv file to work with
	if (file_type == "xlsx")
	{
		string str = file_name + ".xlsx";
		const char* name = str.c_str();

		intrusive_ptr<Aspose::Cells::IWorkbook> wkb = Factory::CreateIWorkbook(new String(name));
		wkb->Save(new String("temp.csv"));

		file_name = "temp";

	}

	//opens the csv file to start reading
	ifstream infile(file_name + ".csv");
	if (!infile)
	{
		cout << "> Error opening file...\n";
		ifstream check(file_name + ".xlsx");
		cout << "> Exiting Program...\n";
		exit(1);
	}

	//creates a new csv file that will be written on
	string new_file_name = file_name + " reps.csv";
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
		//turns the file into a vector
		vector<pair<string, int>> input_file;
		Apportionment_Algorithm::make_vector(infile, input_file);

		Apportionment_Algorithm::Apportionment_Algorithm(input_file, outfile, number_of_representatives, type_of_algorithm);



		// changes file back to xlsx if it originally was an xlsx file
		if (file_name == "temp")
		{

			string t = hold + " reps.xlsx";
			const char* n = t.c_str();

			intrusive_ptr<Aspose::Cells::IWorkbook> wkb2 = Factory::CreateIWorkbook(new String("temp reps.csv"));
			wkb2->Save(new String(n));

		}


		cout << endl << "> Finished :)\n\n\n";
	}
	catch (runtime_error& error)
	{
		cout << error.what() << endl << endl;
	}

	infile.close();
	outfile.close();

	remove("temp.csv");
	remove("temp reps.csv");
	

	return 0;
}