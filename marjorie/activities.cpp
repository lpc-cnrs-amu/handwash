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
		//activity_tmp->print_activity();
		append_activity = activity_tmp->check_and_append_event_to_activity( new Event(line, excel_csv) );
		
		if(!append_activity)
		{
			vector<Activity*> split_activity; 
			activity_tmp->activity_per_person(split_activity); 
			
			//activity_tmp->print_activity();
			if(split_activity.size()==0)
				activities.push_back( new Activity(activity_tmp) );
			else
			{
				for(unsigned nb_activities=0; nb_activities < split_activity.size(); ++nb_activities)
					activities.push_back( new Activity(split_activity[nb_activities]) );
			}
			
			
			activity_tmp->~Activity();
			activity_tmp = new Activity( new Event(line, excel_csv) );
			append_activity = true;
			
			activities[activities.size()-1]->print_activity();
			cout << endl << endl;
			
		}
	}
	if(append_activity)
	{
		vector<Activity*> split_activity;
		activity_tmp->activity_per_person(split_activity);
		
		if(split_activity.size()==0)
			activities.push_back( new Activity(activity_tmp) );
		else
		{
			for(unsigned nb_activities=0; nb_activities < split_activity.size(); ++nb_activities)
				activities.push_back( new Activity(split_activity[nb_activities]) );
		}
		
		
		activity_tmp->~Activity();
		activity_tmp = new Activity( new Event(line, excel_csv) );
		
		activities[activities.size()-1]->print_activity();
		cout << endl << endl;
	}

	database.close();
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
		activities[i]->write_file(output);
	
	output.close();
}
