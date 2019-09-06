#include <iostream>
#include <string.h>
#include <string>
#include <map>
#include <iomanip>
#include "person.hpp"
#include <chrono> 

using namespace std;
using namespace std::chrono;

/* GATHER DATA (ACTIVITY, LABEL...) FOR EACH PERSON */

void update_persons_stats(Activity* activity_tmp, map<unsigned, Person*>& person_stats, unsigned p)
{		
	if (person_stats.find(p) == person_stats.end())
		person_stats[ p ] = new Person();	
		
	// increase number of corresponding label
	unsigned nb_label = activity_tmp->get_nb_label();
	for(unsigned i=0; i < nb_label; ++i)
		person_stats[ p ]->incr_nb_label( activity_tmp->get_label(i) );
	
	
	// increase nb of corresponding activity
	if( activity_tmp->get_is_inout() )
	{
		person_stats[ p ]->incr_nb_activity_inout();
	}
	else
	{
		if( activity_tmp->get_is_in() )
			person_stats[ p ]->incr_nb_activity_in();
		
		if( activity_tmp->get_is_out() )
			person_stats[ p ]->incr_nb_activity_out();		
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
	unsigned cpt_line = 0;
	
	while(std::getline(database, line))
	{
		++cpt_line;
		if(cpt_line==1)
			continue;
		
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


/* CALCUL PERCENT, STATS */

void calcul_percent(Person* current_person)	
{
	current_person->calcul_percent();
}


/** a refaire */
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
	
		// WEIRD / IMPOSSIBLE
	float in_weird_sur_percent;
	float out_weird_sur_percent;
	float inout_weird_sur_percent;
	
	float in_impossible_sur_percent;
	float out_impossible_sur_percent;
	float inout_impossible_sur_percent;
	
	float in_weird_possible_percent;
	float out_weird_possible_percent;
	float inout_weird_possible_percent;
	
	
	output << "\"ID\";" 
		<< "\"total activity in sure\";"
		<< "\"total activity in possible\";"
		<< "\"total activity out sure\";"
		<< "\"total activity out possible\";" 
		<< "\"total activity inout sure\";"
		<< "\"total activity inout possible\";"
		
		<< "\"SHA in sure percent\";"
		<< "\"SHA in sure number\";"
		<< "\"SHA out sure percent\";"
		<< "\"SHA out sure number\";"
		<< "\"SHA inout sure percent\";"
		<< "\"SHA inout sure number\";"
		
		<< "\"SHA not taken in sure percent\";"
		<< "\"SHA not taken in sure number\";"
		<< "\"SHA not taken out sure percent\";"
		<< "\"SHA not taken out sure number\";"
		<< "\"SHA not taken inout sure percent\";"
		<< "\"SHA not taken inout sure number\";"
		
		<< "\"SHA in possible number\";"
		<< "\"SHA out possible number\";"
		<< "\"SHA inout possible number\";"
		
		
		<< "\"IN_NO_ALARM percent\";"
		<< "\"IN_NO_ALARM number\";"
		<< "\"IN_AFTER_ALARM percent\";"
		<< "\"IN_AFTER_ALARM number\";"
		<< "\"IN_DURING_ALARM percent\";" 
		<< "\"IN_DURING_ALARM number\";" 
		<< "\"IN_POSSIBLE_NO_ALARM percent\";"
		<< "\"IN_POSSIBLE_NO_ALARM number\";"
		<< "\"IN_POSSIBLE_AFTER_ALARM percent\";"
		<< "\"IN_POSSIBLE_AFTER_ALARM number\";"
		<< "\"IN_POSSIBLE_DURING_ALARM percent\";"
		<< "\"IN_POSSIBLE_DURING_ALARM number\";"
		<< "\"NOT_IN_NO_ALARM percent\";"
		<< "\"NOT_IN_NO_ALARM number\";"
		<< "\"NOT_IN_ALARM percent\";"
		<< "\"NOT_IN_ALARM number\";"
		
		<< "\"IN_WEIRD_SUR percent\";"
		<< "\"IN_WEIRD_SUR number\";"
		<< "\"IN_WEIRD_POSSIBLE percent\";"
		<< "\"IN_WEIRD_POSSIBLE number\";"
		<< "\"IN_IMPOSSIBLE_SUR percent\";"
		<< "\"IN_IMPOSSIBLE_SUR number\";"
		
		
		<< "\"OUT_NO_ALARM percent\";"
		<< "\"OUT_NO_ALARM number\";"
		<< "\"OUT_AFTER_ALARM percent\";"
		<< "\"OUT_AFTER_ALARM number\";"
		<< "\"OUT_DURING_ALARM percent\";" 
		<< "\"OUT_DURING_ALARM number\";" 
		<< "\"OUT_POSSIBLE_NO_ALARM percent\";"
		<< "\"OUT_POSSIBLE_NO_ALARM number\";"
		<< "\"OUT_POSSIBLE_AFTER_ALARM percent\";"
		<< "\"OUT_POSSIBLE_AFTER_ALARM number\";"
		<< "\"OUT_POSSIBLE_DURING_ALARM percent\";"
		<< "\"OUT_POSSIBLE_DURING_ALARM number\";"
		<< "\"NOT_OUT_NO_ALARM percent\";"
		<< "\"NOT_OUT_NO_ALARM number\";"
		<< "\"NOT_OUT_ALARM percent\";"
		<< "\"NOT_OUT_ALARM number\";"
		
		<< "\"OUT_WEIRD_SUR percent\";"
		<< "\"OUT_WEIRD_SUR number\";"
		<< "\"OUT_WEIRD_POSSIBLE percent\";"
		<< "\"OUT_WEIRD_POSSIBLE number\";"
		<< "\"OUT_IMPOSSIBLE_SUR percent\";"
		<< "\"OUT_IMPOSSIBLE_SUR number\";"
		
		
		<< "\"INOUT_NO_ALARM percent\";"
		<< "\"INOUT_NO_ALARM number\";"
		<< "\"INOUT_AFTER_ALARM percent\";"
		<< "\"INOUT_AFTER_ALARM number\";"
		<< "\"INOUT_DURING_ALARM percent\";" 
		<< "\"INOUT_DURING_ALARM number\";" 
		<< "\"INOUT_POSSIBLE_NO_ALARM percent\";"
		<< "\"INOUT_POSSIBLE_NO_ALARM number\";"
		<< "\"INOUT_POSSIBLE_AFTER_ALARM percent\";"
		<< "\"INOUT_POSSIBLE_AFTER_ALARM number\";"
		<< "\"INOUT_POSSIBLE_DURING_ALARM percent\";"
		<< "\"INOUT_POSSIBLE_DURING_ALARM number\";"
		<< "\"NOT_INOUT_NO_ALARM percent\";"
		<< "\"NOT_INOUT_NO_ALARM number\";"
		<< "\"NOT_INOUT_ALARM percent\";"
		<< "\"NOT_INOUT_ALARM number\";"
		
		<< "\"INOUT_WEIRD_SUR percent\";"
		<< "\"INOUT_WEIRD_SUR number\";"
		<< "\"INOUT_WEIRD_POSSIBLE percent\";"
		<< "\"INOUT_WEIRD_POSSIBLE number\";"
		<< "\"INOUT_IMPOSSIBLE_SUR percent\";"
		<< "\"INOUT_IMPOSSIBLE_SUR number\";"
		<< endl;
		

	
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
			not_inout_alarm_percent,
			
			in_weird_sur_percent,
			out_weird_sur_percent,
			inout_weird_sur_percent,

			in_impossible_sur_percent,
			out_impossible_sur_percent,
			inout_impossible_sur_percent,

			in_weird_possible_percent,
			out_weird_possible_percent,
			inout_weird_possible_percent
		);
		

		output << "\"" << it->first << "\";" 
			<< "\"" << it->second->get_nb_activity_in_sure_total() << "\";"
			<< "\"" << it->second->get_nb_activity_in_possible_total() << "\";"
			<< "\"" << it->second->get_nb_activity_out_sure_total() << "\";"
			<< "\"" << it->second->get_nb_activity_out_possible_total() << "\";"
			<< "\"" << it->second->get_nb_activity_inout_sure_total() << "\";"
			<< "\"" << it->second->get_nb_activity_inout_possible_total() << "\";"
			
			<< "\"" << std::fixed << std::setprecision(2) << SHA_in_sure_percent << "\";"
			<< "\"" << it->second->get_nb_SHA_taken_sure_in() << "\";"
			<< "\"" << std::fixed << std::setprecision(2) << SHA_out_sure_percent << "\";"
			<< "\"" << it->second->get_nb_SHA_taken_sure_out() << "\";"
			<< "\"" << std::fixed << std::setprecision(2) << SHA_inout_sure_percent << "\";"
			<< "\"" << it->second->get_nb_SHA_taken_sure_inout() << "\";"
			
			<< "\"" << std::fixed << std::setprecision(2) << SHA_not_taken_in_sure_percent << "\";"
			<< "\"" << it->second->get_nb_SHA_not_taken_sure_in() << "\";"
			<< "\"" << std::fixed << std::setprecision(2) << SHA_not_taken_out_sure_percent << "\";"
			<< "\"" << it->second->get_nb_SHA_not_taken_sure_out() << "\";"
			<< "\"" << std::fixed << std::setprecision(2) << SHA_not_taken_inout_sure_percent << "\";"
			<< "\"" << it->second->get_nb_SHA_not_taken_sure_inout() << "\";"
			
			<< "\""<< it->second->get_nb_SHA_taken_possible_in() <<"\";"
			<< "\""<< it->second->get_nb_SHA_taken_possible_out() <<"\";"
			<< "\""<< it->second->get_nb_SHA_taken_possible_inout() <<"\";"
			
				
			<< "\"" << std::fixed << std::setprecision(2) << in_no_alarm_percent << "\";"
			<< "\""<< it->second->get_nb_label( IN_NO_ALARM ) <<"\";"
			<< "\""<< std::fixed << std::setprecision(2) << in_after_alarm_percent  <<"\";"
			<< "\""<< it->second->get_nb_label( IN_AFTER_ALARM ) <<"\";"
			<< "\""<< std::fixed << std::setprecision(2) << in_during_alarm_percent <<"\";" 
			<< "\""<< it->second->get_nb_label( IN_DURING_ALARM ) <<"\";" 
			<< "\""<< std::fixed << std::setprecision(2) << in_possible_no_alarm_percent <<"\";"
			<< "\""<< it->second->get_nb_label( IN_POSSIBLE_NO_ALARM ) <<"\";"
			<< "\""<< std::fixed << std::setprecision(2) << in_possible_after_alarm_percent <<"\";"
			<< "\""<< it->second->get_nb_label( IN_POSSIBLE_AFTER_ALARM ) <<"\";"
			<< "\""<< std::fixed << std::setprecision(2) << in_possible_during_alarm_percent <<"\";"
			<< "\""<< it->second->get_nb_label( IN_POSSIBLE_DURING_ALARM ) <<"\";"
			<< "\""<< std::fixed << std::setprecision(2) << not_in_no_alarm_percent <<"\";"
			<< "\""<< it->second->get_nb_label( NOT_IN_NO_ALARM ) <<"\";"
			<< "\""<< std::fixed << std::setprecision(2) << not_in_alarm_percent <<"\";"
			<< "\""<< it->second->get_nb_label( NOT_IN_ALARM ) <<"\";"
			
			<< "\"" << std::fixed << std::setprecision(2) << in_weird_sur_percent << "\";"
			<< "\""<< it->second->get_nb_label( IN_WEIRD_SUR ) <<"\";"
			<< "\"" << std::fixed << std::setprecision(2) << in_weird_possible_percent << "\";"
			<< "\""<< it->second->get_nb_label( IN_WEIRD_POSSIBLE ) <<"\";"
			<< "\"" << std::fixed << std::setprecision(2) << in_impossible_sur_percent << "\";"
			<< "\""<< it->second->get_nb_label( IN_IMPOSSIBLE_SUR ) <<"\";"
			
				
			<< "\"" << std::fixed << std::setprecision(2) << out_no_alarm_percent << "\";"
			<< "\""<< it->second->get_nb_label( OUT_NO_ALARM ) <<"\";"
			<< "\""<< std::fixed << std::setprecision(2) << out_after_alarm_percent  <<"\";"
			<< "\""<< it->second->get_nb_label( OUT_AFTER_ALARM ) <<"\";"
			<< "\""<< std::fixed << std::setprecision(2) << out_during_alarm_percent <<"\";" 
			<< "\""<< it->second->get_nb_label( OUT_DURING_ALARM ) <<"\";" 
			<< "\""<< std::fixed << std::setprecision(2) << out_possible_no_alarm_percent <<"\";"
			<< "\""<< it->second->get_nb_label( OUT_POSSIBLE_NO_ALARM ) <<"\";"
			<< "\""<< std::fixed << std::setprecision(2) << out_possible_after_alarm_percent <<"\";"
			<< "\""<< it->second->get_nb_label( OUT_POSSIBLE_AFTER_ALARM ) <<"\";"
			<< "\""<< std::fixed << std::setprecision(2) << out_possible_during_alarm_percent <<"\";"
			<< "\""<< it->second->get_nb_label( OUT_POSSIBLE_DURING_ALARM ) <<"\";"
			<< "\""<< std::fixed << std::setprecision(2) << not_out_no_alarm_percent <<"\";"
			<< "\""<< it->second->get_nb_label( NOT_OUT_NO_ALARM ) <<"\";"
			<< "\""<< std::fixed << std::setprecision(2) << not_out_alarm_percent <<"\";"
			<< "\""<< it->second->get_nb_label( NOT_OUT_ALARM ) <<"\";"
			
			<< "\"" << std::fixed << std::setprecision(2) << out_weird_sur_percent << "\";"
			<< "\""<< it->second->get_nb_label( OUT_WEIRD_SUR ) <<"\";"
			<< "\"" << std::fixed << std::setprecision(2) << out_weird_possible_percent << "\";"
			<< "\""<< it->second->get_nb_label( OUT_WEIRD_POSSIBLE ) <<"\";"
			<< "\"" << std::fixed << std::setprecision(2) << out_impossible_sur_percent << "\";"
			<< "\""<< it->second->get_nb_label( OUT_IMPOSSIBLE_SUR ) <<"\";"
			
				
			<< "\"" << std::fixed << std::setprecision(2) << inout_no_alarm_percent << "\";"
			<< "\""<< it->second->get_nb_label( INOUT_NO_ALARM ) <<"\";"
			<< "\""<< std::fixed << std::setprecision(2) << inout_after_alarm_percent  <<"\";"
			<< "\""<< it->second->get_nb_label( INOUT_AFTER_ALARM ) <<"\";"
			<< "\""<< std::fixed << std::setprecision(2) << inout_during_alarm_percent <<"\";" 
			<< "\""<< it->second->get_nb_label( INOUT_DURING_ALARM ) <<"\";" 
			<< "\""<< std::fixed << std::setprecision(2) << inout_possible_no_alarm_percent <<"\";"
			<< "\""<< it->second->get_nb_label( INOUT_POSSIBLE_NO_ALARM ) <<"\";"
			<< "\""<< std::fixed << std::setprecision(2) << inout_possible_after_alarm_percent <<"\";"
			<< "\""<< it->second->get_nb_label( INOUT_POSSIBLE_AFTER_ALARM ) <<"\";"
			<< "\""<< std::fixed << std::setprecision(2) << inout_possible_during_alarm_percent <<"\";"
			<< "\""<< it->second->get_nb_label( INOUT_POSSIBLE_DURING_ALARM ) <<"\";"
			<< "\""<< std::fixed << std::setprecision(2) << not_inout_no_alarm_percent <<"\";"
			<< "\""<< it->second->get_nb_label( NOT_INOUT_NO_ALARM ) <<"\";"
			<< "\""<< std::fixed << std::setprecision(2) << not_inout_alarm_percent <<"\";"
			<< "\""<< it->second->get_nb_label( NOT_INOUT_ALARM ) <<"\";"
			
			<< "\"" << std::fixed << std::setprecision(2) << inout_weird_sur_percent << "\";"
			<< "\""<< it->second->get_nb_label( INOUT_WEIRD_SUR ) <<"\";"
			<< "\"" << std::fixed << std::setprecision(2) << inout_weird_possible_percent << "\";"
			<< "\""<< it->second->get_nb_label( INOUT_WEIRD_POSSIBLE ) <<"\";"
			<< "\"" << std::fixed << std::setprecision(2) << inout_impossible_sur_percent << "\";"
			<< "\""<< it->second->get_nb_label( INOUT_IMPOSSIBLE_SUR ) <<"\";"
			<< endl;
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
	
	return 0;
}
