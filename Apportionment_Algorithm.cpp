#include "Apportionment_Algorithm.hpp"

const int default_reps = 435;
string type_ham = "Hamilton";
string type_hunt = "Huntington-Hill";

void Apportionment_Algorithm::Apportionment_Algorithm(vector<pair<string, int>>& in, ofstream& out, int num_reps, string type)
{
	if (type == "Huntington-Hill")
	{
		huntington_hill_algorithm(in, out, num_reps);
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


bool Apportionment_Algorithm::is_number(const string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

void Apportionment_Algorithm::make_vector(ifstream& in, vector<pair<string, int>>& file)
{
	string line;
	string name;
	string pop_s;

	getline(in, line); // skip the first line

	while (getline(in, line)) // read whole line into line
	{
		istringstream iss(line); // string stream
		getline(iss, name, ','); // read first part up to comma, ignore the comma
		getline(iss, pop_s, ','); // read the second part, ignore the comma

		//checks to see if the population is valid and skips if it is not
		if (!Apportionment_Algorithm::is_number(pop_s))
		{
			cout << "> Warning: " << name << " was skipped due to bad formatting" << endl;
			continue;
		}

		int pop_i = stoi(pop_s);
		file.push_back(make_pair(name, pop_i));
	}
	if (file.size() == 0)
	{
		throw runtime_error("> Error: File has no valid information");
	}
}

bool Apportionment_Algorithm::compare_1(pair<string, pair<int, float>>& a, pair<string, pair<int, float>>& b)
{
	return a.first < b.first;
}


void Apportionment_Algorithm::sort_alphabetically_1(vector<pair<string, pair<int, float>>>& x)
{
	sort(x.begin(), x.end(), compare_1);
}

bool Apportionment_Algorithm::compare_2(pair<string, int>& a, pair<string, int> & b)
{
	return a.first < b.first;
}

void Apportionment_Algorithm::sort_alphabetically_2(vector<pair<string, int>>& x)
{
	sort(x.begin(), x.end(), compare_2);
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


void Apportionment_Algorithm::hamilton_algorithm(vector<pair<string, int>>& in, ofstream& out, int num_reps)
{
	if (out)
	{
		//calculates total population
		int total_pop = 0;
		for(auto it: in)
		{
			total_pop += it.second;
		}

		//calculates average population per representative
		float avg_pop_per_rep = static_cast<float>(total_pop) / num_reps;

		//gives minimum number of each reps for each state and a remainder
		//creates a vector of the statename, min # of reps and remainder
		float divide;
		int floor;
		float remain;
		int reps_used = 0;
		vector<pair<string, pair<int, float>>> state_floor_remain;
		for (auto it : in)
		{
			divide = static_cast<float>(it.second) / avg_pop_per_rep;
			floor = static_cast<int>(divide);
			remain = divide - floor;

			state_floor_remain.push_back(make_pair(it.first, make_pair(floor, remain)));

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
		sort_alphabetically_1(state_floor_remain);

		//prints the statename and reps into the output file
		out <<  "State, # of Reps" << endl;
		for (auto i : state_floor_remain)
		{
			out << i.first << ',' << i.second.first << endl;
		}

		out.close();
	}
	else
	{
		throw runtime_error("> Error: File does not exist\n");
	}

}

double Apportionment_Algorithm::priority(int population, int representatives)
{
	double numerator = static_cast<double>(population);
	double denominator = sqrt(representatives * (representatives + 1));
	return numerator / denominator;
}

void Apportionment_Algorithm::max_prio(vector<pair<int, pair<int, double>>>& a)
{
	double max = 0;
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
	a[pos].second.second = priority(a[pos].first, a[pos].second.first);
}


void Apportionment_Algorithm::huntington_hill_algorithm(vector<pair<string, int>>& in, ofstream& out, int num_reps)
{
	if (out)
	{
		// creates a vector that holds population, initial reps (1), and initial priority score
		vector<pair<int, pair<int, double>>> pop_rep_prio;
		for (auto it : in)
		{
			double prio_score = priority(it.second, 1);
			pop_rep_prio.push_back(make_pair(it.second, make_pair(1, prio_score)));
			num_reps--;
		}
		//checks to see if the number of states is less than number of reps and exits if that is the case
		if (num_reps < 0)
		{
			throw runtime_error("> Error: Number of representatives is less than the number of states");
		}

		// finds the highest priority and updates the rep count until there are no reps left
		while (num_reps > 0)
		{
			max_prio(pop_rep_prio);
			num_reps--;
		}

		// creates a vector that has the states and their final representative number
		vector<pair<string, int>> result;
		int i = 0;
		for (auto it : in)
		{
			result.push_back(make_pair(it.first, pop_rep_prio[i].second.first));
			i++;
		}

		//makes vector into alphabetical order
		sort_alphabetically_2(result);

		//prints the statename and reps into the output file
		out << "State, # of Reps" << endl;
		for (auto i : result)
		{
			out << i.first << ',' << i.second << endl;
		}
		out.close();
	}
	else
	{
		throw runtime_error("> Error: File does not exist\n");
	}
}


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
			cout << "> Error: non-positive number entered\n> Re-enter number of representatives (positive number): ";
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