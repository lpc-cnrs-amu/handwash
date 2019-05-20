#include <iostream>
#include <string.h>
#include <string>
#include <map>
#include <iomanip>
#include "person.hpp"
#include "activity.hpp"

using namespace std;



void update_persons_stats(Activity* activity_tmp, map<unsigned, Person*>& person_stats, unsigned p)
{
	if (person_stats.find(p) == person_stats.end())
		person_stats[ p ] = new Person();
	
	person_stats[ p ]->add_nb_SHA_possible_in ( activity_tmp->get_nb_SHA_possible_in() );
	person_stats[ p ]->add_nb_SHA_possible_inout ( activity_tmp->get_nb_SHA_possible_inout() );
	person_stats[ p ]->add_nb_SHA_possible_out ( activity_tmp->get_nb_SHA_possible_out() );
	person_stats[ p ]->add_nb_SHA_sure_in ( activity_tmp->get_nb_SHA_sure_in() );
	person_stats[ p ]->add_nb_SHA_sure_inout ( activity_tmp->get_nb_SHA_sure_inout() );
	person_stats[ p ]->add_nb_SHA_sure_out ( activity_tmp->get_nb_SHA_sure_out() );
	
	if(activity_tmp->get_SHA_not_taken_in())
		person_stats[ p ]->incr_not_taken_in();
	if(activity_tmp->get_SHA_not_taken_out())
		person_stats[ p ]->incr_not_taken_out();
	if(activity_tmp->get_SHA_not_taken_inout())
		person_stats[ p ]->incr_not_taken_inout();	
		
	
	if( activity_tmp->get_inout() )
	{
		if( activity_tmp->get_theres_SHA_sure_inout() )
			person_stats[ p ]->incr_nb_SHA_inout_sure_total();
		if( activity_tmp->get_theres_SHA_possible_inout() )
			person_stats[ p ]->incr_nb_SHA_inout_possible_total();
	}
	else
	{
		if( activity_tmp->get_theres_SHA_sure_in() )
			person_stats[ p ]->incr_nb_SHA_in_sure_total();
		
		if( activity_tmp->get_theres_SHA_sure_out() )
			person_stats[ p ]->incr_nb_SHA_out_sure_total();
		
		if( activity_tmp->get_theres_SHA_possible_in() )
			person_stats[ p ]->incr_nb_SHA_in_possible_total();
			
		if( activity_tmp->get_theres_SHA_possible_out() )
			person_stats[ p ]->incr_nb_SHA_out_possible_total();	
	}	
}

/**
	* \brief Activity Constructor.
	*
	* \param filename : file containing every instances in csv format.
*/
void get_persons_stats(char* filename, bool excel_csv, map<unsigned, Person*>& person_stats)
{
	ifstream database(filename, ios::in);
	if(!database)
	{ 
		cerr << "Impossible to open the file " << filename << endl;
		exit(EXIT_FAILURE);
	}
	
	string line;
	bool append_activity = true;
	vector<Activity*> split_activity; 
	Activity* activity_tmp = new Activity();
	
	while(std::getline(database, line))
	{
		
		// add to the current activity
		append_activity = activity_tmp->check_and_append_event_to_activity( new Event(line, excel_csv) );
		
		// the current event is in another activity
		if(!append_activity)
		{
			activity_tmp->activity_per_person(split_activity);
			
			if(split_activity.size()==0)
				update_persons_stats(activity_tmp, person_stats, activity_tmp->get_person());
				
			else
			{
				for(unsigned nb_activities=0; nb_activities < split_activity.size(); ++nb_activities)
					update_persons_stats(split_activity[nb_activities], person_stats, split_activity[nb_activities]->get_person());
			}
			
			activity_tmp->~Activity();
			activity_tmp = new Activity( new Event(line, excel_csv) );
			append_activity = true;
		}
	}
	if(append_activity)
	{
		activity_tmp->activity_per_person(split_activity);
		
		if(split_activity.size()==0)
			update_persons_stats(activity_tmp, person_stats, activity_tmp->get_person());
		else
		{
			for(unsigned nb_activities=0; nb_activities < split_activity.size(); ++nb_activities)
				update_persons_stats(split_activity[nb_activities], person_stats, split_activity[nb_activities]->get_person());
		}
		
		activity_tmp->~Activity();
		activity_tmp = new Activity( new Event(line, excel_csv) );
	}

	database.close();
}


void write_file(map<unsigned, Person*>& person_stats, char* filename)
{
	ofstream output(filename, ios::out | ios::trunc);
	if(!output)
	{
		cerr << "Impossible to open the file " << filename << endl;
		exit(EXIT_FAILURE);		
	}
	/*
	
	output << "      |            SHA taken                                  |            SHA not taken            |" << endl;
	output << "      |_______________________________________________________|_____________________________________|" << endl;
	output << "  ID  |           sur             |       possible            |                 sure                |" << endl;
	output << "      |___________________________|___________________________|_____________________________________|" << endl;
	output << "      |   in   |   out  |  inout  |   in   |   out  |  inout  |     in     |     out    |   inout   |" << endl;
	output << "______|________|________|_________|________|________|_________|____________|____________|___________|" << endl;
	*/
	
	for(auto it = person_stats.begin(); it != person_stats.end(); it++ )
	{/*
		float sure_out = 100*it->second->nb_SHA_sure_out / it->second->nb_SHA_out_sure_total;
		
		
		output << setfill(' ') << setw (3) << it->first << " | " << setfill(' ') << setw (3) << 100*it->second->nb_SHA_sure_in / it->second->nb_SHA_in_sure_total << 
			" | " << setfill(' ') << setw (3) << 100*it->second->nb_SHA_sure_out / it->second->nb_SHA_out_sure_total
		*/
		
		
		
		
		
		
		
		output << "PERSON : " << it->first << endl
			   << "\t SHA_NOT_TAKEN_IN: " << it->second->nb_not_taken_in << endl
			   << "\t SHA_NOT_TAKEN_OUT: " << it->second->nb_not_taken_out << endl
			   << "\t SHA_NOT_TAKEN_INOUT: " << it->second->nb_not_taken_inout << endl
			   
			   << "\t nb_SHA_sure_in: " << it->second->nb_SHA_sure_in << endl
			   << "\t nb_SHA_sure_out: " << it->second->nb_SHA_sure_out << endl
			   << "\t nb_SHA_sure_inout: " << it->second->nb_SHA_sure_inout << endl
			   
			   << "\t nb_SHA_possible_in: " << it->second->nb_SHA_possible_in << endl
			   << "\t nb_SHA_possible_out: " << it->second->nb_SHA_possible_out << endl
			   << "\t nb_SHA_possible_inout: " << it->second->nb_SHA_possible_inout << endl
			   
			   
			   << "\t\tPERCENT" << endl;
			   
		if (it->second->nb_SHA_in_sure_total == 0)
			output << "\t SHA_NOT_TAKEN_IN: 0 %" << endl;
		else
			output << "\t SHA_NOT_TAKEN_IN: " << 100*it->second->nb_not_taken_in / it->second->nb_SHA_in_sure_total << " %" << endl;
			
		if(it->second->nb_SHA_out_sure_total == 0)	
			output << "\t SHA_NOT_TAKEN_OUT: 0 %" << endl;
		else
			output << "\t SHA_NOT_TAKEN_OUT: " << 100*it->second->nb_not_taken_out / it->second->nb_SHA_out_sure_total << " %" << endl;
			
		if(it->second->nb_SHA_inout_sure_total == 0)	
			output << "\t SHA_NOT_TAKEN_INOUT: 0 %" << endl;
		else
			output << "\t SHA_NOT_TAKEN_INOUT: " << 100*it->second->nb_not_taken_inout / it->second->nb_SHA_inout_sure_total << " %" << endl;
			   
			   
		if(it->second->nb_SHA_in_sure_total == 0)	   
			output<< "\t nb_SHA_sure_in: 0 %" << endl;
		else
			output<< "\t nb_SHA_sure_in: " << 100*it->second->nb_SHA_sure_in / it->second->nb_SHA_in_sure_total << " %" << endl;
			
		
		if(it->second->nb_SHA_out_sure_total == 0)
			output << "\t nb_SHA_sure_out: 0 %" << endl;
		else
			output << "\t nb_SHA_sure_out: " << 100*it->second->nb_SHA_sure_out / it->second->nb_SHA_out_sure_total << " %" << endl;
			
			
			
		if(it->second->nb_SHA_inout_sure_total == 0)
			output << "\t nb_SHA_sure_inout: 0 %" << endl;
		else
			output << "\t nb_SHA_sure_inout: " << 100*it->second->nb_SHA_sure_inout / it->second->nb_SHA_inout_sure_total << " %" << endl;
			   
			   
		if(it->second->nb_SHA_in_possible_total == 0)
			output << "\t nb_SHA_possible_in: 0 %" << endl;
		else
			output << "\t nb_SHA_possible_in: " << 100*it->second->nb_SHA_possible_in/ it->second->nb_SHA_in_possible_total << " %" << endl;
			
		if(it->second->nb_SHA_out_possible_total == 0)
			output << "\t nb_SHA_possible_out: 0 %" << endl;
		else
			output << "\t nb_SHA_possible_out: " << 100*it->second->nb_SHA_possible_out / it->second->nb_SHA_out_possible_total << " %" << endl;
			
			
		if(it->second->nb_SHA_inout_possible_total == 0)
			output << "\t nb_SHA_possible_inout: 0 %" << endl ;
		else
			output << "\t nb_SHA_possible_inout: " << 100*it->second->nb_SHA_possible_inout / it->second->nb_SHA_inout_possible_total << " %" << endl << endl;
			   
	}	
	
	
	output.close();
}

void destroy_persons(map<unsigned, Person*>& person_stats)
{
	for(auto it = person_stats.begin(); it != person_stats.end(); it++ )
		it->second->~Person();
}


int main(int argc, char** argv) 
{
	if(argc != 4)
	{
		cerr << "Usage: " << argv[0] << " filename (in csv format) excel_csv_or_not (1 or 0) filename_output" << endl; 
		exit(EXIT_FAILURE);
	}

	bool excel = false;
	if( !strcmp(argv[2],"1") )
		excel = true;
	
	map<unsigned, Person*> person_stats; //key = id de la personne
	get_persons_stats(argv[1], excel, person_stats);
	write_file(person_stats, argv[3]);
	
	destroy_persons(person_stats);
	return 0;
}
