#include "activities.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;


Activities::~Activities()
{
	for(unsigned i=0; i<activities.size(); ++i)
	{
		activities[i]->~Activity();
		activities[i] = NULL;
	}
	activities.clear();
}

/**
	* \brief Activity Constructor.
	*
	* \param filename : file containing every instances in csv format.
*/
Activities::Activities(char* filename, bool excel_csv)
{
	ifstream database(filename, ios::in);
	if(!database)
	{ 
		cerr << "Impossible to open the file " << filename << endl;
		exit(EXIT_FAILURE);
	}
	
	string line;
	bool append_activity = true;
	
	Activity* activity_tmp = new Activity();
	
	while(std::getline(database, line))
	{
		activity_tmp->print_activity();
		append_activity = activity_tmp->check_and_append_event_to_activity( new Event(line, excel_csv) );
		
		if(!append_activity)
		{
			activities.push_back( new Activity(activity_tmp) );
			activity_tmp->~Activity();
			activity_tmp = new Activity( new Event(line, excel_csv) );
			append_activity = true;
		}
		
	}
	if(append_activity)
	{
		activities.push_back( new Activity(activity_tmp) );
		activity_tmp->~Activity();
		activity_tmp = new Activity( new Event(line, excel_csv) );
		append_activity = true;
	}

	database.close();
	//activity_per_person();
}



// Write ALL activities
void Activities::write_file(char* filename)
{
	ofstream output(filename, ios::out | ios::trunc);
	if(!output)
	{
		cerr << "Impossible to open the file " << filename << endl;
		exit(EXIT_FAILURE);		
	}
	
	for(unsigned i=0; i<activities.size(); ++i)
	{
		output << "ACTIVITY " << i+1 << endl;
		activities[i]->write_file(output);
	}	
	output.close();
}
