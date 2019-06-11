#include <iostream>
#include <string.h>
#include <string>
#include <map>
#include <iomanip>
#include "person.hpp"
#include <chrono> 

using namespace std;
using namespace std::chrono;


void update_persons_stats(Activity* activity_tmp, map<unsigned, Person*>& person_stats, unsigned p)
{
	if (person_stats.find(p) == person_stats.end())
		person_stats[ p ] = new Person();	
		
	unsigned nb_label = activity_tmp->get_nb_label();
	for(unsigned i=0; i < nb_label; ++i)
		person_stats[ p ]->incr_nb_label( activity_tmp->get_label(i) ); 
		
	if( activity_tmp->get_inout() )
	{
		if( activity_tmp->get_theres_SHA_sure_inout() )
			person_stats[ p ]->incr_nb_activity_inout_sure();
		if( activity_tmp->get_theres_SHA_possible_inout() )
			person_stats[ p ]->incr_nb_activity_inout_possible();
	}
	else
	{
		if( activity_tmp->get_theres_SHA_sure_in() )
			person_stats[ p ]->incr_nb_activity_in_sure();
		
		if( activity_tmp->get_theres_SHA_sure_out() )
			person_stats[ p ]->incr_nb_activity_out_sure();
		
		if( activity_tmp->get_theres_SHA_possible_in() )
			person_stats[ p ]->incr_nb_activity_in_possible();
			
		if( activity_tmp->get_theres_SHA_possible_out() )
			person_stats[ p ]->incr_nb_activity_out_possible();	
	}	
}

/** On commence par là !
* On regarde les activités
* on associe les stats de l'activité à la personne
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
		
		// sur (1 personne dans l'activité)
		if(split_activity.size()==0)
			update_persons_stats(activity_tmp, person_stats, activity_tmp->get_person());
			
		// possible (plusieurs personnes dans l'activité)
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


void calcul_percent(
	Person* current_person,
	float& SHA_in_sure_percent,
	float& SHA_not_taken_in_sure_percent,
	float& SHA_in_possible_percent,
	float& SHA_out_sure_percent,
	float& SHA_not_taken_out_sure_percent,
	float& SHA_out_possible_percent,
	float& SHA_inout_sure_percent,
	float& SHA_not_taken_inout_sure_percent,
	float& SHA_inout_possible_percent,
	float& in_no_alarm_percent,
	float& in_after_alarm_percent,
	float& in_during_alarm_percent, 
	float& in_possible_no_alarm_percent,
	float& in_possible_after_alarm_percent,
	float& in_possible_during_alarm_percent, 	
	float& not_in_no_alarm_percent,
	float& not_in_alarm_percent,
	float& out_no_alarm_percent,
	float& out_after_alarm_percent,
	float& out_during_alarm_percent, 
	float& out_possible_no_alarm_percent,
	float& out_possible_after_alarm_percent,
	float& out_possible_during_alarm_percent, 	
	float& not_out_no_alarm_percent,
	float& not_out_alarm_percent,
	float& inout_no_alarm_percent,
	float& inout_after_alarm_percent,
	float& inout_during_alarm_percent, 
	float& inout_possible_no_alarm_percent,
	float& inout_possible_after_alarm_percent,
	float& inout_possible_during_alarm_percent, 	
	float& not_inout_no_alarm_percent,
	float& not_inout_alarm_percent
)	
{
	unsigned total_in_sur = current_person->get_nb_activity_in_sure_total();
	unsigned total_in_possible = current_person->get_nb_activity_in_possible_total();
		
	unsigned total_out_sur = current_person->get_nb_activity_out_sure_total();
	unsigned total_out_possible = current_person->get_nb_activity_out_possible_total();
		
	unsigned total_inout_sur = current_person->get_nb_activity_inout_sure_total();
	unsigned total_inout_possible = current_person->get_nb_activity_inout_possible_total();
	
	// IN
		// IN SUR
	if(total_in_sur == 0) // aucune activité sur en entrant
	{
		SHA_in_sure_percent = 0;
		in_no_alarm_percent = 0;
		in_after_alarm_percent = 0;
		in_during_alarm_percent = 0;
		SHA_not_taken_in_sure_percent = 0;
		not_in_no_alarm_percent = 0;
		not_in_alarm_percent = 0;
	}
	else
	{
		// nb SHA taken - sur
		SHA_in_sure_percent = 100 * current_person->get_nb_SHA_taken_sure_in() / total_in_sur;
			// Within those SHA taken :
		in_no_alarm_percent = 100 * current_person->get_nb_label( IN_NO_ALARM ) / current_person->get_nb_SHA_taken_sure_in(); // a changer
		in_after_alarm_percent = 100 * current_person->get_nb_label( IN_AFTER_ALARM ) / current_person->get_nb_SHA_taken_sure_in();
		in_during_alarm_percent = 100 * current_person->get_nb_label( IN_DURING_ALARM ) / current_person->get_nb_SHA_taken_sure_in();	
		
		// nb SHA not taken - sur
		SHA_not_taken_in_sure_percent = 100 * current_person->get_nb_SHA_not_taken_sure_in()  / total_in_sur;
			// Within those SHA not taken
		not_in_no_alarm_percent = 100 * current_person->get_nb_label( NOT_IN_NO_ALARM ) / current_person->get_nb_SHA_not_taken_sure_in(); 
		not_in_alarm_percent = 100 * current_person->get_nb_label( NOT_IN_ALARM ) / current_person->get_nb_SHA_not_taken_sure_in();
	}
	
	
		// IN POSSIBLE
	if(total_in_possible == 0) // aucune activité 'possible' en entrant
	{
		SHA_in_possible_percent = 0;
		in_possible_no_alarm_percent = 0;
		in_possible_after_alarm_percent = 0;
		in_possible_during_alarm_percent = 0;
	}
	else
	{
		// nb SHA taken - possible
		SHA_in_possible_percent = 100 * current_person->get_nb_SHA_taken_possible_in() / total_in_possible;
			// Within those SHA taken :
		in_no_alarm_percent = 100 * current_person->get_nb_label( IN_POSSIBLE_NO_ALARM ) / current_person->get_nb_SHA_taken_possible_in();
		in_after_alarm_percent = 100 * current_person->get_nb_label( IN_POSSIBLE_AFTER_ALARM ) / current_person->get_nb_SHA_taken_possible_in();
		in_during_alarm_percent = 100 * current_person->get_nb_label( IN_POSSIBLE_DURING_ALARM ) / current_person->get_nb_SHA_taken_possible_in();		
	}
	
	
	// OUT
		// OUT SUR
	if(total_out_sur == 0) // aucune activité sur en sortant
	{
		SHA_out_sure_percent = 0;
		out_no_alarm_percent = 0;
		out_after_alarm_percent = 0;
		out_during_alarm_percent = 0;
		SHA_not_taken_out_sure_percent = 0;
		not_out_no_alarm_percent = 0;
		not_out_alarm_percent = 0;
	}
	else
	{
		// nb SHA taken - sur
		SHA_out_sure_percent = 100 * current_person->get_nb_SHA_taken_sure_out() / total_out_sur;
			// Within those SHA taken :
		out_no_alarm_percent = 100 * current_person->get_nb_label( OUT_NO_ALARM ) / current_person->get_nb_SHA_taken_sure_out();
		out_after_alarm_percent = 100 * current_person->get_nb_label( OUT_AFTER_ALARM ) / current_person->get_nb_SHA_taken_sure_out();
		out_during_alarm_percent = 100 * current_person->get_nb_label( OUT_DURING_ALARM ) / current_person->get_nb_SHA_taken_sure_out();	
		
		// nb SHA not taken - sur
		SHA_not_taken_out_sure_percent = 100 * current_person->get_nb_SHA_not_taken_sure_out()  / total_out_sur;
			// Within those SHA not taken
		not_out_no_alarm_percent = 100 * current_person->get_nb_label( NOT_OUT_NO_ALARM ) / current_person->get_nb_SHA_not_taken_sure_out(); 
		not_out_alarm_percent = 100 * current_person->get_nb_label( NOT_OUT_ALARM ) / current_person->get_nb_SHA_not_taken_sure_out();
	}
	
	
		// OUT POSSIBLE
	if(total_out_possible == 0) // aucune activité 'possible' en sortant
	{
		SHA_out_possible_percent = 0;
		out_possible_no_alarm_percent = 0;
		out_possible_after_alarm_percent = 0;
		out_possible_during_alarm_percent = 0;
	}
	else
	{
		// nb SHA taken - possible
		SHA_out_possible_percent = 100 * current_person->get_nb_SHA_taken_possible_out() / total_out_possible;
			// Within those SHA taken :
		out_no_alarm_percent = 100 * current_person->get_nb_label( OUT_POSSIBLE_NO_ALARM ) / current_person->get_nb_SHA_taken_possible_out();
		out_after_alarm_percent = 100 * current_person->get_nb_label( OUT_POSSIBLE_AFTER_ALARM ) / current_person->get_nb_SHA_taken_possible_out();
		out_during_alarm_percent = 100 * current_person->get_nb_label( OUT_POSSIBLE_DURING_ALARM ) / current_person->get_nb_SHA_taken_possible_out();		
	}
	
	
	// INOUT
		// INOUT SUR
	if(total_inout_sur == 0) // aucune activité sur en entrant/sortant
	{
		SHA_inout_sure_percent = 0;
		inout_no_alarm_percent = 0;
		inout_after_alarm_percent = 0;
		inout_during_alarm_percent = 0;
		SHA_not_taken_inout_sure_percent = 0;
		not_inout_no_alarm_percent = 0;
		not_inout_alarm_percent = 0;
	}
	else
	{
		// nb SHA taken - sur
		SHA_inout_sure_percent = 100 * current_person->get_nb_SHA_taken_sure_inout() / total_inout_sur;
			// Within those SHA taken :
		inout_no_alarm_percent = 100 * current_person->get_nb_label( INOUT_NO_ALARM ) / current_person->get_nb_SHA_taken_sure_inout();
		inout_after_alarm_percent = 100 * current_person->get_nb_label( INOUT_AFTER_ALARM ) / current_person->get_nb_SHA_taken_sure_inout();
		inout_during_alarm_percent = 100 * current_person->get_nb_label( INOUT_DURING_ALARM ) / current_person->get_nb_SHA_taken_sure_inout();	
		
		// nb SHA not taken - sur
		SHA_not_taken_inout_sure_percent = 100 * current_person->get_nb_SHA_not_taken_sure_inout()  / total_inout_sur;
			// Within those SHA not taken
		not_inout_no_alarm_percent = 100 * current_person->get_nb_label( NOT_INOUT_NO_ALARM ) / current_person->get_nb_SHA_not_taken_sure_inout(); 
		not_inout_alarm_percent = 100 * current_person->get_nb_label( NOT_INOUT_ALARM ) / current_person->get_nb_SHA_not_taken_sure_inout();
	}
	
	
		// INOUT POSSIBLE
	if(total_inout_possible == 0) // aucune activité 'possible' en entrant/sortant
	{
		SHA_inout_possible_percent = 0;
		inout_possible_no_alarm_percent = 0;
		inout_possible_after_alarm_percent = 0;
		inout_possible_during_alarm_percent = 0;
	}
	else
	{
		// nb SHA taken - possible
		SHA_inout_possible_percent = 100 * current_person->get_nb_SHA_taken_possible_inout() / total_inout_possible;
			// Within those SHA taken :
		inout_no_alarm_percent = 100 * current_person->get_nb_label( INOUT_POSSIBLE_NO_ALARM ) / current_person->get_nb_SHA_taken_possible_inout();
		inout_after_alarm_percent = 100 * current_person->get_nb_label( INOUT_POSSIBLE_AFTER_ALARM ) / current_person->get_nb_SHA_taken_possible_inout();
		inout_during_alarm_percent = 100 * current_person->get_nb_label( INOUT_POSSIBLE_DURING_ALARM ) / current_person->get_nb_SHA_taken_possible_inout();		
	}	

}


void write_file(map<unsigned, Person*>& person_stats, char* filename)
{
	ofstream output(filename, ios::out | ios::trunc);
	if(!output)
	{
		cerr << "Impossible to open the file " << filename << endl;
		exit(EXIT_FAILURE);		
	}
	
		// Specific
	// IN
	float in_no_alarm_percent;
	float in_after_alarm_percent;
	float in_during_alarm_percent; 
	float in_possible_no_alarm_percent;
	float in_possible_after_alarm_percent;
	float in_possible_during_alarm_percent; 	
	float not_in_no_alarm_percent;
	float not_in_alarm_percent;
	
	// OUT
	float out_no_alarm_percent;
	float out_after_alarm_percent;
	float out_during_alarm_percent; 
	float out_possible_no_alarm_percent;
	float out_possible_after_alarm_percent;
	float out_possible_during_alarm_percent; 	
	float not_out_no_alarm_percent;
	float not_out_alarm_percent;
	
	// INOUT
	float inout_no_alarm_percent;
	float inout_after_alarm_percent;
	float inout_during_alarm_percent; 
	float inout_possible_no_alarm_percent;
	float inout_possible_after_alarm_percent;
	float inout_possible_during_alarm_percent; 	
	float not_inout_no_alarm_percent;
	float not_inout_alarm_percent;
	
		// Total
	float SHA_in_sure_percent;
	float SHA_not_taken_in_sure_percent;
	float SHA_in_possible_percent;
	float SHA_out_sure_percent;
	float SHA_not_taken_out_sure_percent;
	float SHA_out_possible_percent;
	float SHA_inout_sure_percent;
	float SHA_not_taken_inout_sure_percent;
	float SHA_inout_possible_percent;
	

	output << "%Infos :" << endl;
	output << "%Everything after a '%' in the same line is a comment, if you want to write anything put a '%' first !" << endl 
		   << "%The ID '0' corresponds to no one in particular (could be the patient or visitors)." << endl << endl;
	
	for(auto it = person_stats.begin(); it != person_stats.end(); it++ )
	{	
		calcul_percent(it->second, 
			SHA_in_sure_percent,
			SHA_not_taken_in_sure_percent,
			SHA_in_possible_percent,
			SHA_out_sure_percent,
			SHA_not_taken_out_sure_percent,
			SHA_out_possible_percent,
			SHA_inout_sure_percent,
			SHA_not_taken_inout_sure_percent,
			SHA_inout_possible_percent,
			in_no_alarm_percent,
			in_after_alarm_percent,
			in_during_alarm_percent, 
			in_possible_no_alarm_percent,
			in_possible_after_alarm_percent,
			in_possible_during_alarm_percent, 	
			not_in_no_alarm_percent,
			not_in_alarm_percent,
			out_no_alarm_percent,
			out_after_alarm_percent,
			out_during_alarm_percent, 
			out_possible_no_alarm_percent,
			out_possible_after_alarm_percent,
			out_possible_during_alarm_percent, 	
			not_out_no_alarm_percent,
			not_out_alarm_percent,
			inout_no_alarm_percent,
			inout_after_alarm_percent,
			inout_during_alarm_percent, 
			inout_possible_no_alarm_percent,
			inout_possible_after_alarm_percent,
			inout_possible_during_alarm_percent, 	
			not_inout_no_alarm_percent,
			not_inout_alarm_percent
		);
		
		// faire aussi les totaux (total_sur_in, total_sur_out, total_sur_inout, possible_in, possible_out, possible_inout
		
		output << it->first << endl; // ID
		
		// in no alarm
		output << std::fixed << std::setprecision(2) << in_no_alarm_percent << endl;
		output << it->second->get_nb_label( IN_NO_ALARM ) << endl;
		
		// in after alarm
		output << std::fixed << std::setprecision(2) << in_after_alarm_percent  << endl;
		output << it->second->get_nb_label( IN_AFTER_ALARM ) << endl;
		
		// in during alarm
		output << std::fixed << std::setprecision(2) << in_during_alarm_percent << endl;
		output << it->second->get_nb_label( IN_DURING_ALARM ) << endl;
		
		// in possible no alarm
		output << std::fixed << std::setprecision(2) << in_possible_no_alarm_percent << endl;
		output << it->second->get_nb_label( IN_POSSIBLE_NO_ALARM ) << endl;
		
		// in possible after alarm
		output << std::fixed << std::setprecision(2) << in_possible_after_alarm_percent << endl;
		output << it->second->get_nb_label( IN_POSSIBLE_AFTER_ALARM ) << endl;
		
		// in possible during alarm
		output << std::fixed << std::setprecision(2) << in_possible_during_alarm_percent << endl; 
		output << it->second->get_nb_label( IN_POSSIBLE_DURING_ALARM ) << endl;
			
		// not taken in no alarm
		output << std::fixed << std::setprecision(2) << not_in_no_alarm_percent << endl;
		output << it->second->get_nb_label( NOT_IN_NO_ALARM ) << endl;
		
		// not taken in alarm
		output << std::fixed << std::setprecision(2) << not_in_alarm_percent << endl;
		output << it->second->get_nb_label( NOT_IN_ALARM ) << endl;
		
		// out no alarm
		output << std::fixed << std::setprecision(2) << out_no_alarm_percent << endl;
		output << it->second->get_nb_label( OUT_NO_ALARM ) << endl;
		
		// out after alarm
		output << std::fixed << std::setprecision(2) << out_after_alarm_percent << endl;
		output << it->second->get_nb_label( OUT_AFTER_ALARM ) << endl;
		
		// out during alarm
		output << std::fixed << std::setprecision(2) << out_during_alarm_percent << endl; 
		output << it->second->get_nb_label( OUT_DURING_ALARM ) << endl;
		
		// out possible no alarm
		output << std::fixed << std::setprecision(2) << out_possible_no_alarm_percent << endl;
		output << it->second->get_nb_label( OUT_POSSIBLE_NO_ALARM ) << endl;
		
		// out possible after alarm
		output << std::fixed << std::setprecision(2) << out_possible_after_alarm_percent << endl;
		output << it->second->get_nb_label( OUT_POSSIBLE_AFTER_ALARM ) << endl;
		
		// out possible during alarm
		output << std::fixed << std::setprecision(2) << out_possible_during_alarm_percent << endl; 
		output << it->second->get_nb_label( OUT_POSSIBLE_DURING_ALARM ) << endl;
			
		// not taken out no alarm
		output << std::fixed << std::setprecision(2) << not_out_no_alarm_percent << endl;
		output << it->second->get_nb_label( NOT_OUT_NO_ALARM ) << endl;
		
		// not taken out alarm
		output << std::fixed << std::setprecision(2) << not_out_alarm_percent << endl;
		output << it->second->get_nb_label( NOT_OUT_ALARM ) << endl;
		
		// inout no alarm
		output << std::fixed << std::setprecision(2) << inout_no_alarm_percent << endl;
		output << it->second->get_nb_label( INOUT_NO_ALARM ) << endl;
		
		// inout after alarm
		output << std::fixed << std::setprecision(2) << inout_after_alarm_percent << endl;
		output << it->second->get_nb_label( INOUT_AFTER_ALARM ) << endl;
		
		// inout during alarm
		output << std::fixed << std::setprecision(2) << inout_during_alarm_percent << endl; 
		output << it->second->get_nb_label( INOUT_DURING_ALARM ) << endl;
		
		// inout possible no alarm
		output << std::fixed << std::setprecision(2) << inout_possible_no_alarm_percent << endl;
		output << it->second->get_nb_label( INOUT_POSSIBLE_NO_ALARM ) << endl;
		
		// inout possible after alarm
		output << std::fixed << std::setprecision(2) << inout_possible_after_alarm_percent << endl;
		output << it->second->get_nb_label( INOUT_POSSIBLE_AFTER_ALARM ) << endl;
		
		// inout possible during alarm
		output << std::fixed << std::setprecision(2) << inout_possible_during_alarm_percent << endl; 	
		output << it->second->get_nb_label( INOUT_POSSIBLE_DURING_ALARM ) << endl;
		
		// not taken inout no alarm
		output << std::fixed << std::setprecision(2) << not_inout_no_alarm_percent << endl;
		output << it->second->get_nb_label( NOT_INOUT_NO_ALARM ) << endl;
		
		// not taken inout alarm
		output << std::fixed << std::setprecision(2) << not_inout_alarm_percent << endl;
		output << it->second->get_nb_label( NOT_INOUT_ALARM ) << endl;
		
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
	/*
	auto start = high_resolution_clock::now();
	map<unsigned, Person*> person_stats; //key = id de la personne
	get_persons_stats(argv[1], excel, person_stats);
	write_file(person_stats, argv[3]);
	
	destroy_persons(person_stats);
	auto stop = high_resolution_clock::now(); 
	auto duration = duration_cast<std::chrono::minutes>(stop - start);
	auto duration_seconds = duration_cast<std::chrono::seconds>(stop - start);
	cout << "Time taken : " << endl;
	cout << duration.count() << " minutes" << endl; 
	cout << "(so : " << duration_seconds.count() << " seconds)" << endl; 
	*/
	return 0;
}
