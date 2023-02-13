#include "Apportionment_Algorithm.hpp"

const int default_reps = 435;
string type_ham = "Hamilton";
string type_hunt = "Huntington-Hill";

void Apportionment_Algorithm::Apportionment_Algorithm(ifstream& in, ofstream& out, int num_reps, string type)
{
	if (type == "Huntington-Hill")
	{
		//huntington_hill_algorithm(in, out, num_reps);
	}
	else if (type == "Hamilton")
	{
		hamilton_algorithm(in, out, num_reps);
	}
	else
	{
		throw runtime_error("> Error: Non-compatible algorithm type entered");
	}
}


bool Apportionment_Algorithm::compare(pair<string, pair<int, float>>& a, pair<string, pair<int, float>>& b)
{
	return a.first < b.first;
}


void Apportionment_Algorithm::sort_alphabetically(vector<pair<string, pair<int, float>>>& x)
{
	sort(x.begin(), x.end(), compare);
}


void Apportionment_Algorithm::max_float(vector<pair<string, pair<int, float>>>& a)
{
	float max = 0;
	int pos = 0;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i].second.second > max)
		{
			max = a[i].second.second;
			pos = i;
		}
	}
	a[pos].second.first++;
	a[pos].second.second = 0;
}


void Apportionment_Algorithm::hamilton_algorithm(ifstream& in, ofstream& out, int num_reps)
{
	if (in and out)
	{
		string state_header, pop_header;
		getline(in, state_header, ',');
		getline(in, pop_header);

		//calculates total population
		string state_name;
		int pop;
		int total_pop = 0;
		while (getline(in, state_name, ',') && in >> pop)
		{
			total_pop += pop;
		}

		//resets the read file back to the second line
		in.clear();
		in.seekg(0);
		getline(in, state_header, ',');
		getline(in, pop_header, '\n');

		//calculates average population per representative
		float avg_pop_per_rep = static_cast<float>(total_pop) / num_reps;

		//gives minimum number of each reps for each state and a remainder
		//creates a vector of the statename, min # of reps and remainder
		float divide;
		int floor;
		float remain;
		string popp;
		int pops;
		int reps_used = 0;
		vector<pair<string, pair<int, float>>> state_floor_remain;
		while (getline(in, state_name, ',') && getline(in, popp, '\n'))
		{
			pops = stoi(popp);
			divide = static_cast<float>(pops) / avg_pop_per_rep;
			floor = static_cast<int>(divide);
			remain = divide - floor;

			state_floor_remain.push_back(make_pair(state_name, make_pair(floor, remain)));

			reps_used += floor;
		}

		//calculates representatives left then distributes them based on the largest remainders
		int reps_left = num_reps - reps_used;
		while (reps_left > 0)
		{
			max_float(state_floor_remain);
			reps_left--;
		}

		//makes vector into alphabetical order
		sort_alphabetically(state_floor_remain);

		//prints the statename and reps into the output file
		out << state_header << ", # of Reps" << endl;
		for (auto i : state_floor_remain)
		{
			out << i.first << ',' << i.second.first << endl;
		}

		in.close();
		out.close();
	}
	else
	{
		throw runtime_error("> Error: File does not exist\n");
	}

}


/*void Apportionment_Algorithm::huntington_hill_algorithm(ifstream& in, ofstream& out, int num_reps)
{
	if (in and out)
	{

		in.close();
		out.close();
	}
	else
	{
		throw runtime_error("> Error: File does not exist\n");
	}
}
*/

int Apportionment_Algorithm::Entry_Message_1()
{
	string yaynay;
	int num;

	cout << "> Would you like to change the number of representatives? (currently set to 435) \n> Please type yes or no: ";
	cin >> yaynay;

	while (yaynay != "yes" && yaynay != "no")
	{
		cout << "> Incorrect Syntax \n> Please type yes or no: ";
		cin >> yaynay;
	}
	if (yaynay == "no")
	{
		num = default_reps;
	}
	else
	{

		cout << "> Please enter the number of representatives you wish to use: ";
		cin >> num;
		while (num <= 0)
		{
			cout << "> Error: negative number entered\n> Re-enter number of representatives (positive number): ";
			cin >> num;
		}
	}

	cout << endl;
	return num;
}

string Apportionment_Algorithm::Entry_Message_2()
{
	string yaynay;
	string types;

	cout << "> Would you like to change the algorithm used to the Hamilton method? (currently set to the Huntington-Hill method)\n> Please type yes or no: ";
	cin >> yaynay;
	while (yaynay != "yes" && yaynay != "no")
	{
		cout << "> Incorrect Syntax \n> Please type yes or no: ";
		cin >> yaynay;
	}
	if (yaynay == "yes")
	{
		types = type_ham;
	}
	else
	{
		types = type_hunt;
	}
	cout << endl;
	return types;
}