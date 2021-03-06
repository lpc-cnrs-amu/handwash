#include <iostream>
#include <string.h>
#include <string>
#include <map>
#include <iomanip>
#include "activities.hpp"
#include "person.hpp"
#include <chrono> 

using namespace std;
using namespace std::chrono;

/* GATHER DATA (ACTIVITY, LABEL...) FOR EACH PERSON */

void update_persons_stats(Activity* activity_tmp, map<int, Person*>& person_stats, int p)
{		
	if (person_stats.find(p) == person_stats.end())
		person_stats[ p ] = new Person();	
		
	// increase number of corresponding label
	unsigned nb_label = activity_tmp->get_nb_label();
	for(unsigned i=0; i < nb_label; ++i)
		person_stats[ p ]->incr_label( activity_tmp->get_label(i) );
	
	
	// increase nb of corresponding activity
	if( activity_tmp->get_is_inout() )
	{
		person_stats[ p ]->incr_nb_activity_inout();
		if(activity_tmp->is_SHA_30_sec_inout__in())
			person_stats[ p ]->incr_nb_SHA_30_sec_inout();
	}
	else
	{
		if( activity_tmp->get_is_in() )
		{
			person_stats[ p ]->incr_nb_activity_in();
			if(activity_tmp->is_SHA_30_sec_in())
				person_stats[ p ]->incr_nb_SHA_30_sec_in();
		}
		
		if( activity_tmp->get_is_out() )
		{
			person_stats[ p ]->incr_nb_activity_out();
			if(activity_tmp->is_SHA_30_sec_out())
				person_stats[ p ]->incr_nb_SHA_30_sec_out();
		}	
	}
	
	
}



/** On commence par là !
* On regarde les activités
* on associe les stats de l'activité à la personne
*/
void get_persons_stats(char* filename, bool excel_csv, map<int, Person*>& person_stats)
{
	Activities act(filename, excel_csv);
	cout << "All activities OK !" << endl;
	unsigned nb_activities = act.get_nb_activities();
	for(unsigned i=0; i<nb_activities; ++i)
		update_persons_stats(act.activities[i], person_stats, act.get_person(i));
	
}


/* CALCUL PERCENT, STATS */

void write_file(map<int, Person*>& person_stats, char* filename)
{
	ofstream output(filename, ios::out | ios::trunc);
	if(!output)
	{
		cerr << "Impossible to open the file " << filename << endl;
		exit(EXIT_FAILURE);		
	}
	
	output << "\"ID\";" 
		<< "\"total activity in\";"
		<< "\"total activity out\";" 
		<< "\"total activity inout\";"
		
		<< "\"SHA in percent\";"
		<< "\"SHA in number\";"
		<< "\"SHA out percent\";"
		<< "\"SHA out number\";"
		<< "\"SHA inout percent\";"
		<< "\"SHA inout number\";"
		
		<< "\"SHA not taken in percent\";"
		<< "\"SHA not taken in number\";"
		<< "\"SHA not taken out percent\";"
		<< "\"SHA not taken out number\";"
		<< "\"SHA not taken inout percent\";"
		<< "\"SHA not taken inout number\";"
		
		<< "\"IN_NO_ALARM percent\";"
		<< "\"IN_NO_ALARM number\";"
		<< "\"IN_AFTER_ALARM percent\";"
		<< "\"IN_AFTER_ALARM number\";"
		<< "\"IN_DURING_ALARM percent\";" 
		<< "\"IN_DURING_ALARM number\";" 
		<< "\"NOT_IN_NO_ALARM percent\";"
		<< "\"NOT_IN_NO_ALARM number\";"
		<< "\"NOT_IN_ALARM percent\";"
		<< "\"NOT_IN_ALARM number\";"	
		
		<< "\"OUT_NO_ALARM percent\";"
		<< "\"OUT_NO_ALARM number\";"
		<< "\"OUT_AFTER_ALARM percent\";"
		<< "\"OUT_AFTER_ALARM number\";"
		<< "\"OUT_DURING_ALARM percent\";" 
		<< "\"OUT_DURING_ALARM number\";"
		<< "\"NOT_OUT_NO_ALARM percent\";"
		<< "\"NOT_OUT_NO_ALARM number\";"
		<< "\"NOT_OUT_ALARM percent\";"
		<< "\"NOT_OUT_ALARM number\";"
		
		
		<< "\"INOUT_NO_ALARM percent\";"
		<< "\"INOUT_NO_ALARM number\";"
		<< "\"INOUT_AFTER_ALARM percent\";"
		<< "\"INOUT_AFTER_ALARM number\";"
		<< "\"INOUT_DURING_ALARM percent\";" 
		<< "\"INOUT_DURING_ALARM number\";" 
		<< "\"NOT_INOUT_NO_ALARM percent\";"
		<< "\"NOT_INOUT_NO_ALARM number\";"
		<< "\"NOT_INOUT_ALARM percent\";"
		<< "\"NOT_INOUT_ALARM number\";"

		<< "\"ABANDON_IN percent\";"
		<< "\"ABANDON_IN number\";"	
		<< "\"ABANDON_OUT percent\";"
		<< "\"ABANDON_OUT number\";"
		<< "\"ABANDON_INOUT percent\";"
		<< "\"ABANDON_INOUT number\";"
		
		<< "\"SHA in 30 sec percent\";" 
		<< "\"SHA in 30 sec number\";"
		<< "\"SHA out 30 sec percent\";"
		<< "\"SHA out 30 sec number\";"
		<< "\"SHA inout 30 sec percent\";"
		<< "\"SHA inout 30 sec number\";"
		
		<< "\"IMPOSSIBLE percent\";"
		<< "\"IMPOSSIBLE number\";"
		
		<< endl;
		

	for(auto it = person_stats.begin(); it != person_stats.end(); it++ )
	{	
		it->second->calcul_percent();
		it->second->write_person(it->first, output);
	}
	output.close();
}

void destroy_persons(map<int, Person*>& person_stats)
{
	for(auto it = person_stats.begin(); it != person_stats.end(); it++ )
		it->second->~Person();
}

void print_person_stats(map<int, Person*>& person_stats)
{
	for(auto it = person_stats.begin(); it != person_stats.end(); it++ )
	{
		it->second->print_person(it->first);
	}
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
	map<int, Person*> person_stats; //key = id de la personne
	get_persons_stats(argv[1], excel, person_stats);
	write_file(person_stats, argv[3]);
	//print_person_stats(person_stats);
	
	destroy_persons(person_stats);
	auto stop = high_resolution_clock::now(); 
	auto duration = duration_cast<std::chrono::minutes>(stop - start);
	auto duration_seconds = duration_cast<std::chrono::seconds>(stop - start);
	cout << "Time taken : " << endl;
	cout << duration.count() << " minutes" << endl; 
	cout << "(so : " << duration_seconds.count() << " seconds)" << endl; 
	
	return 0;
}
