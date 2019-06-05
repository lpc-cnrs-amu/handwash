#include "activity.hpp"
#include <algorithm>
#include <map>
#define LAST_EVENT events.size()-1
#define MINUTE_MAX 2
#define CODE_SHA 8
#define SHA_SURE true
#define SHA_POSSIBLE false
#define CODE_OPEN_DOOR 5
#define CODE_CLOSE_DOOR 6
#define CODE_ALARM 7
#define CODE_SHA_DURING_ALARM 10
#define MIN_SECONDS 5

using namespace std;


/**
 * \file activity.cpp
*/


	/* Constructors, Destructor */

/**
	* \brief Activity Destructor. Release the allocated memory.
*/
Activity::~Activity()
{
	for(unsigned i=0; i<events.size(); ++i)
	{
		events[i]->~Event();
		events[i] = NULL;
	}
	events.clear();
}

Activity::Activity(){ }

Activity::Activity(Activity* copy)
{
	unsigned i;
	
	this->main_person = copy->main_person;

	this->nb_SHA_sure_in = copy->nb_SHA_sure_in;
	this->nb_SHA_sure_out = copy->nb_SHA_sure_out;
	
	this->nb_SHA_possible_in = copy->nb_SHA_possible_in;
	this->nb_SHA_possible_out = copy->nb_SHA_possible_out;
	
	this->nb_SHA_sure_inout = copy->nb_SHA_sure_inout;
	this->nb_SHA_possible_inout = copy->nb_SHA_possible_inout;
	
	this->inout = copy->inout;
	this->SHA_not_taken_in = copy->SHA_not_taken_in;
	this->SHA_not_taken_out = copy->SHA_not_taken_out;
	this->SHA_not_taken_inout = copy->SHA_not_taken_inout;
			
	for(i=0; i < copy->events.size(); ++i)
		this->events.push_back( new Event(copy->events[i]) );
		
	for(i=0; i < copy->persons.size(); ++i)
		this->persons.push_back( copy->persons[i] );
		
	for(i=0; i < copy->label_activity.size(); ++i)
		this->label_activity.push_back( copy->label_activity[i] );
}

/**
	* \brief Activity Constructor.
	*
	* \param filename : file containing every instances in csv format.
*/
Activity::Activity(vector<Event*>& vector_event, unsigned p, vector<unsigned>& different_persons)
{
	unsigned i;
	
	main_person = p;
	
	for(i=0; i < vector_event.size(); ++i)
		events.push_back( new Event(vector_event[i]) );
		
	for(i=0; i < different_persons.size(); ++i)
		persons.push_back( different_persons[i] );
}

Activity::Activity(Event* event)
{
	events.push_back( new Event(event) );
}

	/* Getters */

unsigned Activity::get_person() { return main_person; }
unsigned Activity::get_nb_persons() { return persons.size(); }
unsigned Activity::get_nb_SHA_sure_in() { return nb_SHA_sure_in; }
unsigned Activity::get_nb_SHA_sure_out() { return nb_SHA_sure_out; }
unsigned Activity::get_nb_SHA_possible_in() { return nb_SHA_possible_in; }
unsigned Activity::get_nb_SHA_possible_out() { return nb_SHA_possible_out; }

unsigned Activity::get_nb_SHA_sure_inout() { return nb_SHA_sure_inout; }
unsigned Activity::get_nb_SHA_possible_inout() { return nb_SHA_possible_inout; }


bool Activity::get_SHA_not_taken_in() { return SHA_not_taken_in; }
bool Activity::get_SHA_not_taken_out() { return SHA_not_taken_out; }
bool Activity::get_SHA_not_taken_inout() { return SHA_not_taken_inout; }
bool Activity::get_inout() { return inout; }

bool Activity::get_theres_SHA_sure_in() { return theres_SHA_sure_in; }
bool Activity::get_theres_SHA_sure_out() { return theres_SHA_sure_out; }
bool Activity::get_theres_SHA_sure_inout() { return theres_SHA_sure_inout; }
bool Activity::get_theres_SHA_possible_in () { return theres_SHA_possible_in; }
bool Activity::get_theres_SHA_possible_out () { return theres_SHA_possible_out; }
bool Activity::get_theres_SHA_possible_inout () { return theres_SHA_possible_inout; }


	/* Print functions */


/**
	* \name write_file
	* \brief Write all activities in a file.
	* 
	* \param output : the file.
*/
void Activity::write_file(ofstream& output)
{
	unsigned i;
	
	output << "PERSON: " << main_person << endl;
	output << "\tNUMBER OF PERSON: " << persons.size() << endl << "\t";	
	for(i=0; i < persons.size(); ++i)
		output << persons[i] << " ";
	output << endl;

	output << "\tNUMBER SHA SURE IN : " << nb_SHA_sure_in << endl;
	output << "\tNUMBER SHA SURE OUT : " << nb_SHA_sure_out << endl;
	output << "\tNUMBER SHA POSSIBLE IN : " << nb_SHA_possible_in << endl;
	output << "\tNUMBER SHA POSSIBLE OUT : " << nb_SHA_possible_out << endl;
	output << "\tNUMBER SHA SURE INOUT : " << nb_SHA_sure_inout << endl;
	output << "\tNUMBER SHA POSSIBLE INOUT : " << nb_SHA_possible_inout << endl;
	output << "SHA NOT TAKEN IN : " << SHA_not_taken_in << endl;
	output << "SHA NOT TAKEN OUT : " << SHA_not_taken_out << endl;
	output << "SHA NOT TAKEN INOUT : " << SHA_not_taken_inout << endl;
	
	for(i=0; i<events.size(); ++i)
	{
		output << "\t" 
			   << events[i]->get_event()   << " "
			   << events[i]->get_chamber() << " "
			   << events[i]->get_id_puce() << " "
			   << events[i]->get_date()    << " "
			   << events[i]->get_time()    << " "
			   << events[i]->get_in()	   << endl;
	}
}

/**
	* \name print_activity
	* \brief Write all activities in the console.
*/
void Activity::print_activity()
{
	unsigned i;
	
	cout << "PERSON: " << main_person << endl;
	cout << "\tNUMBER OF PERSON: " << persons.size() << endl << "\t";	
	for(i=0; i < persons.size(); ++i)
		cout << persons[i] << " ";
	cout << endl;

	cout << "\tNUMBER SHA SURE IN : " << nb_SHA_sure_in << endl;
	cout << "\tNUMBER SHA SURE OUT : " << nb_SHA_sure_out << endl;
	cout << "\tNUMBER SHA POSSIBLE IN : " << nb_SHA_possible_in << endl;
	cout << "\tNUMBER SHA POSSIBLE OUT : " << nb_SHA_possible_out << endl;
	cout << "\tNUMBER SHA SURE INOUT : " << nb_SHA_sure_inout << endl;
	cout << "\tNUMBER SHA POSSIBLE INOUT : " << nb_SHA_possible_inout << endl;
	cout << "SHA NOT TAKEN IN : " << SHA_not_taken_in << endl;
	cout << "SHA NOT TAKEN OUT : " << SHA_not_taken_out << endl;
	cout << "SHA NOT TAKEN INOUT : " << SHA_not_taken_inout << endl;
	
	for(i=0; i<events.size(); ++i)
	{
		cout << "\t" 
			 << events[i]->get_event()   << " "
			 << events[i]->get_chamber() << " "
			 << events[i]->get_id_puce() << " "
			 << events[i]->get_date()    << " "
			 << events[i]->get_time()    << " "
			 << events[i]->get_in()	   << endl;
	}
}


	/* Append event to the current activity */


/**
	* \name check_and_append_event_to_activity
	* \brief Check if the event can be appended and do it if it can.
	* 
	* \param event : an event.
	* 
	* \return True if we have appended the event to the activity, else false
*/
bool Activity::check_and_append_event_to_activity(Event* event)
{
	if( !same_activity(event) )
		return false;
		
	events.push_back( new Event(event) );
	return true;
}

/**
	* \name append_event_to_activity
	* \brief Append the event to the current activity.
	* 
	* \param event : an event.
*/
void Activity::append_event_to_activity(Event* event)
{
	events.push_back( new Event(event) );
}


	/* Check if an event is in an activity */


/**
	* \name same_activity
	* \brief Check if the event is in the same current activity's schedule 
	* to know if we can append this event or not.
	* 
	* \param event : an event.
	* 
	* \return True if we can append this event, else false.
*/
bool Activity::same_activity(Event* event)
{
	if(events.empty())
		return true;
	if( events[LAST_EVENT]->get_chamber() != event->get_chamber() ) 	
		return false;
	
		
	// Case : not the same date
	if( events[LAST_EVENT]->get_date() != event->get_date() )
	{
		// Case : not the same year BUT same event
		// ex : last event = 31 dec 2018 23h59 AND new event = 01 jan 2019 00h00
		if( events[LAST_EVENT]->get_year() != event->get_year() &&
			event->get_year() == events[LAST_EVENT]->get_year()+1 && 
			events[LAST_EVENT]->get_month() == 12 && 
			event->get_month() == 1 && 
			events[LAST_EVENT]->get_day() == 31 && 
			event->get_day() == 1 && 
			events[LAST_EVENT]->get_hour() == 23 && 
			event->get_hour() == 0 && 
			event->get_minutes() <= events[LAST_EVENT]->get_minutes()+MINUTE_MAX
		   )
			return true;
		
		// Case : same year
		else if( events[LAST_EVENT]->get_year() == event->get_year() )
		{
			
			// Case : not the same month BUT same event
			// Ex: last event = 31 jan 2018 23h59 AND new event = 01 fev 2018 00h01
			if( events[LAST_EVENT]->get_month() != event->get_month() )
			{
				if( events[LAST_EVENT]->get_month()+1 == event->get_month() && 
					event->get_day() == 1 && 
					events[LAST_EVENT]->get_day() == events[LAST_EVENT]->last_day_month() &&
					events[LAST_EVENT]->get_hour() == 23 && 
					event->get_hour() == 0 && 
					event->get_minutes() <= events[LAST_EVENT]->get_minutes()+MINUTE_MAX
				   )
					return true;
			}
			
			// Case : same month, not the same day BUT same event
			// Ex: last event = 24 avr 2018 23h59 AND new event = 25 avr 2018 00h01
			else
			{
				if( event->get_day() == events[LAST_EVENT]->get_day()+1 &&
					events[LAST_EVENT]->get_hour() == 23 && 
					event->get_hour() == 0 && 
					event->get_minutes() <= events[LAST_EVENT]->get_minutes()+MINUTE_MAX
				  )
					return true;
			}
		}
		
	}
	// Case : same date
	else
	{
		// Case : not the same hour BUT same event
		// ex : last event = 24 avr 2018 22h59 AND new event = 24 avr 2018 23h01
		if( event->get_hour() != events[LAST_EVENT]->get_hour() &&
			event->get_hour() == events[LAST_EVENT]->get_hour()+1 && 
			60 - events[LAST_EVENT]->get_minutes() + event->get_minutes() <= MINUTE_MAX
		   )
			return true;
			
		else if( event->get_hour() == events[LAST_EVENT]->get_hour() && 
				event->get_minutes() <= events[LAST_EVENT]->get_minutes()+MINUTE_MAX)
			return true;
			
	}

	return false;
}


	/* Split activities if there is several persons in one activity */


// L'idée est de séparer les personnes directement après avoir trouvé une activité 
// (avant de faire activities.push_back dans activities.cpp)
/**
	* \name identify_different_puces
	* \brief Identifies all the persons in the current activity.
	* 
	* Fills the "different_puces" vector with all the persons in the current activity.
	* Doesn't add the person "0".
	* 
	* Knows who are the first person who has entered the room.
	* 
	* Gives the SHAs to the persons. 
	* 
	* \param different_puces : vector to be filled with all the persons (not the "0"). 
	* \param puces_to_SHA : map to be filled with key=id of a person, value=vector of SHA (true = SHA sure, false = SHA possible).
	* \param first_person_id : first person who has entered the room.
	* 
	* \return The number of persons on the current activity.
*/
unsigned Activity::identify_different_puces(vector<unsigned>& different_puces, 
	map<unsigned, vector<Sha*> >& puces_to_SHA, unsigned& first_person_id)
{
	unsigned puce;
	for(unsigned i=0; i<events.size(); ++i)
	{
		puce = events[i]->get_id_puce();
		
		if(events[i]->get_event() == CODE_SHA || events[i]->get_event() == CODE_SHA_DURING_ALARM)
		{
			if( puce != 0 )
				puces_to_SHA[puce].push_back( new Sha(events[i]->get_unique_id(), SHA_SURE) );
				
			else
			{
				//gives the SHA to different_puces[0] if there is no one else
				if(different_puces.size() == 1)
					puces_to_SHA[different_puces[0]].push_back( new Sha(events[i]->get_unique_id(), SHA_SURE) );

				//gives the SHA to all persons who are in the room
				else if(different_puces.size() > 1)
					for(unsigned k=0; k<different_puces.size(); ++k)
						puces_to_SHA[different_puces[k]].push_back( new Sha(events[i]->get_unique_id(), SHA_POSSIBLE) );

			}
		}		
		
		// we don't add the "0"
		if(puce==0)
			continue;
		
		// if we didn't add the person yet (first time entering the room) we add them to different_puces
		if(std::find(different_puces.begin(), different_puces.end(), puce) == different_puces.end())
			different_puces.push_back(puce);
	}
	
	// Gives empty vector on the puces_to_SHA map for people who don't have a SHA
	for(unsigned i=0; i<different_puces.size(); ++i)
		if(puces_to_SHA.find(different_puces[i]) == puces_to_SHA.end())
			puces_to_SHA[different_puces[i]] = {};
	
	
	// Identify who is the first person who has entered the room
	if(different_puces.size() > 0)
		first_person_id = different_puces[0];
	else
		first_person_id = 0;
	
	return different_puces.size();
}


/**
	* \name activity_per_person
	* \brief Split activities if there is several persons in one activity.
	* 
	* \param split_activity : vector to be filled with the activities split from the current activity.
*/
void Activity::activity_per_person(vector<Activity*>& split_activity)
{
	// Removes all activities not related to our business
	for(unsigned i=0; i<split_activity.size(); ++i)
		split_activity[i]->~Activity();
	split_activity.clear();

	// Who are the person(s) in the current activity ?
	unsigned person;
	vector<unsigned> different_puces;
	map<unsigned, vector<Sha*> > puces_to_SHA;
	unsigned first_person_id = 0;
	unsigned nb_different_puces = identify_different_puces(different_puces, puces_to_SHA, first_person_id);
	
	
	// if there is more than 1 person in the current activity
	if(nb_different_puces > 1)
	{
		map<unsigned, vector<Event*> > different_activities; // key = person, value = vector of events

		// Accords events to each persons
		for(unsigned i=0; i<events.size(); ++i)
		{
			person = events[i]->get_id_puce();
			
			// this event is related to everyone
			if( person==0 )
				for(unsigned k=0; k < different_puces.size(); ++k)
					different_activities[different_puces[k]].push_back( new Event(events[i]) );
			
			// this event is related to a specific person
			else
				different_activities[person].push_back( new Event(events[i]) );
		}	
		
		// Create activities for each persons with the events we accorded to each persons
		for(auto it = different_activities.begin(); it != different_activities.end(); ++it) 
		{			
			split_activity.push_back( new Activity(it->second, it->first, different_puces) );
			if( it->first == first_person_id )
				split_activity[split_activity.size()-1]->first_person = true;
			
			// Count the SHAs for the Activity we just created
			for(auto it2 = puces_to_SHA.begin(); it2 != puces_to_SHA.end(); ++it2) 
				if( it->first == it2->first )
					split_activity[split_activity.size()-1]->finding_labels(it2->second);
		}
		
		// Release the allocated memory for the different_activities map
		destroy_map_different_activities(different_activities);
	}
	
	// If there is not several person in the current activity
	else
	{
		// If there is just 1 person in the current activity
		if(nb_different_puces == 1)
			main_person = different_puces[0];
		// If there is no one in the current activity (all id = 0)
		else
			main_person = 0;
			
		// Add the person to the vector
		persons.push_back(main_person);
		// Finding labels
		finding_labels(puces_to_SHA);
	}
	destroy_map_puces_to_SHA(puces_to_SHA->second); // a revoir pour comment envoyer la valeur de la map
		
}


/**
	* \name destroy_map_different_activities
	* \brief Release the allocated memory for the different_activities map
	* 
	* \param different_activities : the map to destroy.
*/
void Activity::destroy_map_different_activities(map<unsigned, vector<Event*> >& different_activities)
{
	unsigned i;
	for(auto it = different_activities.begin(); it != different_activities.end(); ++it) 
		for(i=0; i < it->second.size(); ++i)
			it->second[i]->~Event();
}


void Activity::destroy_map_puces_to_SHA(map<unsigned, vector<Sha*> >& puces_to_SHA)
{
	unsigned i;
	for(auto it = puces_to_SHA.begin(); it != puces_to_SHA.end(); ++it) 
		for(i=0; i < it->second.size(); ++i)
			it->second[i]->~Sha();
}

	/* Finding labels */


// il n'y a pas de SHA possible quand il y a 1 seule personne dans la chambre
// (que des SHA surs)

unsigned Activity::finding_in_out_inout()
{
	events[0]->set_in(true);
	unsigned event_out = 0;
	unsigned index_out = 0;
	int ecart_in_seconds = 0;
	int ecart_max = 0;
	bool only_5_or_6 = true;
	
	for(unsigned i=0; i < events.size(); ++i)
	{
		if( events[i]->get_event() != CODE_OPEN_DOOR && events[i]->get_event() != CODE_CLOSE_DOOR )
			only_5_or_6 = false;
			
		if( i > 0 )
		{
			ecart_in_seconds = events[i]->ecart_time(events[i-1]);
			if(!only_5_or_6 && ecart_in_seconds >= ecart_max )
			{
				ecart_max = ecart_in_seconds;
				event_out = i;
			}
		}
	}
	
	if( ecart_max > MIN_SECONDS )
	{
		index_out = event_out;
		events[event_out]->set_in(OUT);
	}
	
	inout = false;
	if(index_out == 0)
		inout = true;
	
	return index_out;
}

// Fonctions quand il y a qu'1 personne dans l'activité de base
void Activity::finding_labels(vector<Sha*>& SHA)
{	
	unsigned index_out = finding_in_out_inout();
		
	// label sure : inout
	if(inout)
		finding_label_inout();
	
	// label sure : in and out
	else
	{
		finding_label_in(index_out);
		finding_label_out(index_out);
	}
	
}
void Activity::finding_label_in(unsigned index_ending, vector<Sha*>& SHA)
{
	int alarm_index = -1;
	int SHA_index_sure = -1;
	int SHA_index_possible = -1;
	int SHA_during_alarm_index_sure = -1;
	int SHA_during_alarm_index_possible = -1;
	unsigned id_line_event;
	
	for(unsigned i=0; i < index_ending; ++i)
	{
		id_line_event = events[i]->get_unique_id();
		
		if( events[i]->get_event() == CODE_ALARM  )
			alarm_index = i;
		else if( events[i]->get_event() == CODE_SHA  )
		{
			for(unsigned k=0; k < SHA.size(); ++k)
			{
				if( id_line_event == SHA[k]->get_unique_id() )
				{
					if( SHA[k]->get_sure() )
						SHA_index_sure = i;
					else
						SHA_index_possible = i;
				}
			}
		}
		else if( events[i]->get_event() == CODE_SHA_DURING_ALARM  )
		{
			for(unsigned k=0; k < SHA.size(); ++k)
			{
				if( id_line_event == SHA[k]->get_unique_id() )
				{
					if( SHA[k]->get_sure() )
						SHA_during_alarm_index_sure = i;
					else
						SHA_during_alarm_index_possible = i;
				}
			}
		}
	}
	
	if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		label_activity.push_back( NOT_IN_NO_ALARM );
		theres_SHA_sure_in = true;
	}
		
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		label_activity.push_back( NOT_IN_ALARM );
		theres_SHA_sure_in = true;
	}
		
	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		label_activity.push_back( IN_NO_ALARM );
		theres_SHA_sure_in = true;
	}
		
	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		if(SHA_index_sure < alarm_index)
			cerr << "weird ! sha pris AVANT l'alarme" << endl;
		else
		{
			theres_SHA_sure_in = true;
			label_activity.push_back( IN_AFTER_ALARM );
		}
	}
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		theres_SHA_sure_in = true;
		label_activity.push_back( IN_DURING_ALARM );
	}
		
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		cerr << "weird ! alarme + sha pendant alarme" << endl; 
		
	}
	
	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		if(SHA_during_alarm_index_sure < SHA_index_sure)
		{
			theres_SHA_sure_in = true;
			label_activity.push_back( IN_DURING_ALARM );
		}
		else
			cerr << "weird ! alarme retenti alors qu'on a pris le SHA" << endl; 
	}
	
	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		cerr << "weird ! alarme + sha + sha pendant l'alarme" << endl;
	}
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		label_activity.push_back( IN_POSSIBLE_NO_ALARM );
		theres_SHA_possible_in = true;
	}
	
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		if(SHA_index_possible < alarm_index)
			cerr << "weird ! sha possible pris AVANT l'alarme" << endl;
		else
		{
			theres_SHA_possible_in = true;
			label_activity.push_back( IN_POSSIBLE_AFTER_ALARM );
		}
	}


	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		label_activity.push_back( IN_NO_ALARM );
		theres_SHA_sure_in = true;
	}	
	
	
	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		if(alarm_index < SHA_index_sure && alarm_index < SHA_index_possible)
		{
			theres_SHA_sure_in = true;
			label_activity.push_back( IN_AFTER_ALARM );
		}
		else if(SHA_index_sure < alarm_index)
		{
			theres_SHA_sure_in = true;
			label_activity.push_back( IN_NO_ALARM );
		}
		else
			cerr << "impossible de savoir ! sha possible + sha sur + alarme" << endl;
	}	
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		label_activity.push_back( IN_DURING_ALARM );
		theres_SHA_sure_in = true;
	}	
	
	
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		if(SHA_during_alarm_index_sure < alarm_index && alarm_index < SHA_index_possible || alarm_index < SHA_index_possible && SHA_index_possible < SHA_during_alarm_index_sure)
		{
			theres_SHA_sure_in = true;
			label_activity.push_back( IN_DURING_ALARM );
		}
		else
			cerr << "weird ! sha possible + sha pendant l'alarme sur + alarme" << endl;
	}	


	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		if(SHA_during_alarm_index_sure < SHA_index_sure)
		{
			theres_SHA_sure_in = true;
			label_activity.push_back( IN_DURING_ALARM );
		}
		else
			cerr << "weird ! sha possible + sha pendant l'alarme sur + sha sur" << endl;
	}	

	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		if(SHA_during_alarm_index_sure < alarm_index && SHA_during_alarm_index_sure < SHA_index_sure && SHA_during_alarm_index_sure < SHA_index_possible)
		{
			theres_SHA_sure_in = true;
			label_activity.push_back( IN_DURING_ALARM );
		}
		else
			cerr << "weird ! sha possible + sha pendant l'alarme sur + sha sur + alarme" << endl;
		
	}	
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		theres_SHA_possible_in = true;
		label_activity.push_back( IN_POSSIBLE_DURING_ALARM );
	}


	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_during_alarm_index_possible < alarm_index)
		{
			theres_SHA_possible_in = true;
			label_activity.push_back( IN_POSSIBLE_DURING_ALARM );
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible" << endl;
	}
	
	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		label_activity.push_back( IN_NO_ALARM );
		theres_SHA_sure_in = true;
	}


	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_index_sure < alarm_index)
		{
			theres_SHA_sure_in = true;
			label_activity.push_back( IN_NO_ALARM );
		}
		else if(alarm_index < SHA_index_sure && SHA_index_sure < SHA_during_alarm_index_possible)
		{
			theres_SHA_sure_in = true;
			label_activity.push_back( IN_AFTER_ALARM );
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha sur" << endl;
	}	
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		label_activity.push_back( IN_DURING_ALARM );
		theres_SHA_sure_in = true;
	}	
	
	
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_during_alarm_index_sure < alarm_index && SHA_during_alarm_index_sure < SHA_during_alarm_index_possible)
		{
			theres_SHA_sure_in = true;
			label_activity.push_back( IN_DURING_ALARM );
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;
	}		
	
	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_during_alarm_index_sure < alarm_index && SHA_during_alarm_index_sure < SHA_index_possible)
		{
			theres_SHA_sure_in = true;
			label_activity.push_back( IN_DURING_ALARM );
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;		
	}
	
	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;		
	}	
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;
	}
	
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;
	}
	
	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		theres_SHA_sure_in = true;
		label_activity.push_back( IN_NO_ALARM );
	}
		
	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		if(alarm_index < SHA_index_sure && SHA_index_sure < SHA_index_possible && SHA_index_sure < SHA_during_alarm_index_possible)
		{
			theres_SHA_sure_in = true;
			label_activity.push_back( IN_AFTER_ALARM );
		}
		else if(SHA_index_sure < alarm_index)
		{
			theres_SHA_sure_in = true;
			label_activity.push_back( IN_NO_ALARM );
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;
	}
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		theres_SHA_sure_in = true;
		label_activity.push_back( IN_DURING_ALARM );
	}
		
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_during_alarm_index_sure < alarm_index)
		{
			theres_SHA_sure_in = true;
			label_activity.push_back( IN_DURING_ALARM );
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;
	}
	
	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_during_alarm_index_sure < SHA_index_sure)
		{
			theres_SHA_sure_in = true;
			label_activity.push_back(IN_DURING_ALARM);
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;			
	}
	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_during_alarm_index_sure < SHA_index_sure &&S HA_during_alarm_index_sure < alarm_index)
		{
			theres_SHA_sure_in = true;
			label_activity.push_back(IN_DURING_ALARM);
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;		
	}
	
	else
		cerr << "CAS IMPOSSIBLE NON PRIS EN COMPTE" << endl;
	
}
void Activity::finding_label_out(unsigned index_begining)
{
	int alarm_index = -1;
	int SHA_index_sure = -1;
	int SHA_index_possible = -1;
	int SHA_during_alarm_index_sure = -1;
	int SHA_during_alarm_index_possible = -1;
	unsigned id_line_event;
	
	for(unsigned i=0; i < index_ending; ++i)
	{
		id_line_event = events[i]->get_unique_id();
		
		if( events[i]->get_event() == CODE_ALARM  )
			alarm_index = i;
		else if( events[i]->get_event() == CODE_SHA  )
		{
			for(unsigned k=0; k < SHA.size(); ++k)
			{
				if( id_line_event == SHA[k]->get_unique_id() )
				{
					if( SHA[k]->get_sure() )
						SHA_index_sure = i;
					else
						SHA_index_possible = i;
				}
			}
		}
		else if( events[i]->get_event() == CODE_SHA_DURING_ALARM  )
		{
			for(unsigned k=0; k < SHA.size(); ++k)
			{
				if( id_line_event == SHA[k]->get_unique_id() )
				{
					if( SHA[k]->get_sure() )
						SHA_during_alarm_index_sure = i;
					else
						SHA_during_alarm_index_possible = i;
				}
			}
		}
	}	
	

		
	if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		theres_SHA_sure_out = true;
		label_activity.push_back( NOT_OUT_NO_ALARM );
	}
		
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		theres_SHA_sure_out = true;
		label_activity.push_back( NOT_OUT_ALARM );
	}
		
	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		theres_SHA_sure_out = true;
		label_activity.push_back( OUT_NO_ALARM );
	}
		
	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		if(SHA_index_sure < alarm_index)
			cerr << "weird ! sha pris AVANT l'alarme" << endl;
		else
		{
			theres_SHA_sure_out = true;
			label_activity.push_back( OUT_AFTER_ALARM );
		}
	}
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		theres_SHA_sure_out = true;
		label_activity.push_back( OUT_DURING_ALARM );
	}
		
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		cerr << "weird ! alarme + sha pendant alarme" << endl; 
		
	}
	
	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		if(SHA_during_alarm_index_sure < SHA_index_sure)
		{
			theres_SHA_sure_out = true;
			label_activity.push_back( OUT_DURING_ALARM );
		}
		else
			cerr << "weird ! alarme retenti alors qu'on a pris le SHA" << endl; 
	}
	
	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		cerr << "weird ! alarme + sha + sha pendant l'alarme" << endl;
	}
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		theres_SHA_possible_out = true;
		label_activity.push_back( OUT_POSSIBLE_NO_ALARM );
	}
	
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		if(SHA_index_possible < alarm_index)
			cerr << "weird ! sha possible pris AVANT l'alarme" << endl;
		else
		{
			theres_SHA_possible_out = true;
			label_activity.push_back( OUT_POSSIBLE_AFTER_ALARM );
		}
	}


	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		label_activity.push_back( OUT_NO_ALARM );
		theres_SHA_sure_out = true;
	}	
	
	
	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		if(alarm_index < SHA_index_sure && alarm_index < SHA_index_possible)
		{
			theres_SHA_sure_out = true;
			label_activity.push_back( OUT_AFTER_ALARM );
		}
		else if(SHA_index_sure < alarm_index)
		{
			theres_SHA_sure_out = true;
			label_activity.push_back( OUT_NO_ALARM );
		}
		else
			cerr << "impossible de savoir ! sha possible + sha sur + alarme" << endl;
	}	
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		label_activity.push_back( OUT_DURING_ALARM );
		theres_SHA_sure_out = true;
	}	
	
	
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		if(SHA_during_alarm_index_sure < alarm_index && alarm_index < SHA_index_possible || alarm_index < SHA_index_possible && SHA_index_possible < SHA_during_alarm_index_sure)
		{
			theres_SHA_sure_out = true;
			label_activity.push_back( OUT_DURING_ALARM );
		}
		else
			cerr << "weird ! sha possible + sha pendant l'alarme sur + alarme" << endl;
	}	


	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		if(SHA_during_alarm_index_sure < SHA_index_sure)
		{
			theres_SHA_sure_out = true;
			label_activity.push_back( OUT_DURING_ALARM );
		}
		else
			cerr << "weird ! sha possible + sha pendant l'alarme sur + sha sur" << endl;
	}	

	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		if(SHA_during_alarm_index_sure < alarm_index && SHA_during_alarm_index_sure < SHA_index_sure && SHA_during_alarm_index_sure < SHA_index_possible)
		{
			theres_SHA_sure_out = true;
			label_activity.push_back( OUT_DURING_ALARM );
		}
		else
			cerr << "weird ! sha possible + sha pendant l'alarme sur + sha sur + alarme" << endl;
		
	}	
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		theres_SHA_possible_out = true;
		label_activity.push_back( OUT_POSSIBLE_DURING_ALARM );
	}


	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_during_alarm_index_possible < alarm_index)
		{
			theres_SHA_possible_out = true;
			label_activity.push_back( OUT_POSSIBLE_DURING_ALARM );
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible" << endl;
	}
	
	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		label_activity.push_back( OUT_NO_ALARM );
		theres_SHA_sure_out = true;
	}


	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_index_sure < alarm_index)
		{
			theres_SHA_sure_out = true;
			label_activity.push_back( OUT_NO_ALARM );
		}
		else if(alarm_index < SHA_index_sure && SHA_index_sure < SHA_during_alarm_index_possible)
		{
			theres_SHA_sure_out = true;
			label_activity.push_back( OUT_AFTER_ALARM );
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha sur" << endl;
	}	
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		label_activity.push_back( OUT_DURING_ALARM );
		theres_SHA_sure_out = true;
	}	
	
	
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_during_alarm_index_sure < alarm_index && SHA_during_alarm_index_sure < SHA_during_alarm_index_possible)
		{
			theres_SHA_sure_out = true;
			label_activity.push_back( OUT_DURING_ALARM );
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;
	}		
	
	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_during_alarm_index_sure < alarm_index && SHA_during_alarm_index_sure < SHA_index_possible)
		{
			theres_SHA_sure_out = true;
			label_activity.push_back( OUT_DURING_ALARM );
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;		
	}
	
	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;		
	}	
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;
	}
	
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;
	}
	
	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		theres_SHA_sure_out = true;
		label_activity.push_back( OUT_NO_ALARM );
	}
		
	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		if(alarm_index < SHA_index_sure && SHA_index_sure < SHA_index_possible && SHA_index_sure < SHA_during_alarm_index_possible)
		{
			theres_SHA_sure_out = true;
			label_activity.push_back( OUT_AFTER_ALARM );
		}
		else if(SHA_index_sure < alarm_index)
		{
			theres_SHA_sure_out = true;
			label_activity.push_back( OUT_NO_ALARM );
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;
	}
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		theres_SHA_sure_out = true;
		label_activity.push_back( OUT_DURING_ALARM );
	}
		
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_during_alarm_index_sure < alarm_index)
		{
			theres_SHA_sure_out = true;
			label_activity.push_back( OUT_DURING_ALARM );
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;
	}
	
	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_during_alarm_index_sure < SHA_index_sure)
		{
			theres_SHA_sure_out = true;
			label_activity.push_back(OUT_DURING_ALARM);
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;			
	}
	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_during_alarm_index_sure < SHA_index_sure &&S HA_during_alarm_index_sure < alarm_index)
		{
			theres_SHA_sure_out = true;
			label_activity.push_back(OUT_DURING_ALARM);
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;		
	}
	
	else
		cerr << "CAS IMPOSSIBLE NON PRIS EN COMPTE" << endl;
	
}
void Activity::finding_label_inout()
{
	int alarm_index = -1;
	int SHA_index_sure = -1;
	int SHA_index_possible = -1;
	int SHA_during_alarm_index_sure = -1;
	int SHA_during_alarm_index_possible = -1;
	unsigned id_line_event;
	
	for(unsigned i=0; i < index_ending; ++i)
	{
		id_line_event = events[i]->get_unique_id();
		
		if( events[i]->get_event() == CODE_ALARM  )
			alarm_index = i;
		else if( events[i]->get_event() == CODE_SHA  )
		{
			for(unsigned k=0; k < SHA.size(); ++k)
			{
				if( id_line_event == SHA[k]->get_unique_id() )
				{
					if( SHA[k]->get_sure() )
						SHA_index_sure = i;
					else
						SHA_index_possible = i;
				}
			}
		}
		else if( events[i]->get_event() == CODE_SHA_DURING_ALARM  )
		{
			for(unsigned k=0; k < SHA.size(); ++k)
			{
				if( id_line_event == SHA[k]->get_unique_id() )
				{
					if( SHA[k]->get_sure() )
						SHA_during_alarm_index_sure = i;
					else
						SHA_during_alarm_index_possible = i;
				}
			}
		}
	}		
	
			theres_SHA_sure_inout = true;
			theres_SHA_possible_inout = true;	
	
	if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		theres_SHA_sure_inout = true;
		label_activity.push_back( NOT_INOUT_NO_ALARM );
	}
		
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		theres_SHA_sure_inout = true;
		label_activity.push_back( NOT_INOUT_ALARM );
	}
		
	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		theres_SHA_sure_inout = true;
		label_activity.push_back( INOUT_NO_ALARM );
	}
		
	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		if(SHA_index_sure < alarm_index)
			cerr << "weird ! sha pris AVANT l'alarme" << endl;
		else
		{
			theres_SHA_sure_inout = true;
			label_activity.push_back( INOUT_AFTER_ALARM );
		}
	}
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		theres_SHA_sure_inout = true;
		label_activity.push_back( INOUT_DURING_ALARM );
	}
		
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		cerr << "weird ! alarme + sha pendant alarme" << endl; 
		
	}
	
	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		if(SHA_during_alarm_index_sure < SHA_index_sure)
		{
			theres_SHA_sure_inout = true;
			label_activity.push_back( INOUT_DURING_ALARM );
		}
		else
			cerr << "weird ! alarme retenti alors qu'on a pris le SHA" << endl; 
	}
	
	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible == -1)
	{
		cerr << "weird ! alarme + sha + sha pendant l'alarme" << endl;
	}
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		theres_SHA_possible_inout = true;	
		label_activity.push_back( INOUT_POSSIBLE_NO_ALARM );
	}
	
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		if(SHA_index_possible < alarm_index)
			cerr << "weird ! sha possible pris AVANT l'alarme" << endl;
		else
		{
			theres_SHA_possible_inout = true;
			label_activity.push_back( INOUT_POSSIBLE_AFTER_ALARM );
		}
	}


	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		label_activity.push_back( INOUT_NO_ALARM );
		theres_SHA_sure_inout = true;
	}	
	
	
	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		if(alarm_index < SHA_index_sure && alarm_index < SHA_index_possible)
		{
			theres_SHA_sure_inout = true;
			label_activity.push_back( INOUT_AFTER_ALARM );
		}
		else if(SHA_index_sure < alarm_index)
		{
			theres_SHA_sure_inout = true;
			label_activity.push_back( INOUT_NO_ALARM );
		}
		else
			cerr << "impossible de savoir ! sha possible + sha sur + alarme" << endl;
	}	
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		label_activity.push_back( INOUT_DURING_ALARM );
		theres_SHA_sure_inout = true;
	}	
	
	
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		if(SHA_during_alarm_index_sure < alarm_index && alarm_index < SHA_index_possible || alarm_index < SHA_index_possible && SHA_index_possible < SHA_during_alarm_index_sure)
		{
			theres_SHA_sure_inout = true;
			label_activity.push_back( INOUT_DURING_ALARM );
		}
		else
			cerr << "weird ! sha possible + sha pendant l'alarme sur + alarme" << endl;
	}	


	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		if(SHA_during_alarm_index_sure < SHA_index_sure)
		{
			theres_SHA_sure_inout = true;
			label_activity.push_back( INOUT_DURING_ALARM );
		}
		else
			cerr << "weird ! sha possible + sha pendant l'alarme sur + sha sur" << endl;
	}	

	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible == -1)
	{
		if(SHA_during_alarm_index_sure < alarm_index && SHA_during_alarm_index_sure < SHA_index_sure && SHA_during_alarm_index_sure < SHA_index_possible)
		{
			theres_SHA_sure_inout = true;
			label_activity.push_back( INOUT_DURING_ALARM );
		}
		else
			cerr << "weird ! sha possible + sha pendant l'alarme sur + sha sur + alarme" << endl;
		
	}	
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		theres_SHA_possible_inout = true;	
		label_activity.push_back( INOUT_POSSIBLE_DURING_ALARM );
	}


	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_during_alarm_index_possible < alarm_index)
		{
			theres_SHA_possible_inout = true;	
			label_activity.push_back( INOUT_POSSIBLE_DURING_ALARM );
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible" << endl;
	}
	
	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		label_activity.push_back( INOUT_NO_ALARM );
		theres_SHA_sure_inout = true;
	}


	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_index_sure < alarm_index)
		{
			theres_SHA_sure_inout = true;
			label_activity.push_back( INOUT_NO_ALARM );
		}
		else if(alarm_index < SHA_index_sure && SHA_index_sure < SHA_during_alarm_index_possible)
		{
			theres_SHA_sure_inout = true;
			label_activity.push_back( INOUT_AFTER_ALARM );
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha sur" << endl;
	}	
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		label_activity.push_back( INOUT_DURING_ALARM );
		theres_SHA_sure_inout = true;
	}	
	
	
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_during_alarm_index_sure < alarm_index && SHA_during_alarm_index_sure < SHA_during_alarm_index_possible)
		{
			theres_SHA_sure_inout = true;
			label_activity.push_back( INOUT_DURING_ALARM );
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;
	}		
	
	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_during_alarm_index_sure < alarm_index && SHA_during_alarm_index_sure < SHA_index_possible)
		{
			theres_SHA_sure_inout = true;
			label_activity.push_back( INOUT_DURING_ALARM );
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;		
	}
	
	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible == -1 && SHA_during_alarm_index_possible != -1)
	{
		cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;		
	}	
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;
	}
	
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;
	}
	
	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		theres_SHA_sure_inout = true;
		label_activity.push_back( INOUT_NO_ALARM );
	}
		
	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure == -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		if(alarm_index < SHA_index_sure && SHA_index_sure < SHA_index_possible && SHA_index_sure < SHA_during_alarm_index_possible)
		{
			theres_SHA_sure_inout = true;
			label_activity.push_back( INOUT_AFTER_ALARM );
		}
		else if(SHA_index_sure < alarm_index)
		{
			theres_SHA_sure_inout = true;
			label_activity.push_back( INOUT_NO_ALARM );
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;
	}
	
	else if(alarm_index == -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		theres_SHA_sure_inout = true;
		label_activity.push_back( INOUT_DURING_ALARM );
	}
		
	else if(alarm_index != -1 && SHA_index_sure == -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_during_alarm_index_sure < alarm_index)
		{
			theres_SHA_sure_inout = true;
			label_activity.push_back( INOUT_DURING_ALARM );
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;
	}
	
	else if(alarm_index == -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_during_alarm_index_sure < SHA_index_sure)
		{
			theres_SHA_sure_inout = true;
			label_activity.push_back(INOUT_DURING_ALARM);
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;			
	}
	else if(alarm_index != -1 && SHA_index_sure != -1 && SHA_during_alarm_index_sure != -1 && SHA_index_possible != -1 && SHA_during_alarm_index_possible != -1)
	{
		if(SHA_during_alarm_index_sure < SHA_index_sure &&S HA_during_alarm_index_sure < alarm_index)
		{
			theres_SHA_sure_inout = true;
			label_activity.push_back(INOUT_DURING_ALARM);
		}
		else
			cerr << "weird ! alarme + sha pendant l'alarme possible + sha pendant l'alarme sur" << endl;		
	}
	
	else
		cerr << "CAS IMPOSSIBLE NON PRIS EN COMPTE" << endl;
}

