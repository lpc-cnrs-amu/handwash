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
unsigned id_debug=0;


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

/**
	* \brief Activity Copy Constructor.
	*
	* \param copy : the activity to copy.
*/
Activity::Activity(Activity* copy)
{
	unsigned i;
	
	this->main_person = copy->main_person;
	this->inout = copy->inout;
	this->first_person = copy->first_person;
	this->is_in = copy->is_in;
	this->is_out = copy->is_out;
	this->is_inout = copy->is_inout;
			
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
Activity::Activity(vector<Event*>& vector_event, unsigned p, map<unsigned, unsigned>& puces_with_time_copy)
{
	unsigned i;
	
	main_person = p;
	
	for(auto it = puces_with_time_copy.begin(); it != puces_with_time_copy.end(); ++it)
		puces_with_time.insert(std::pair<it->first,it->second>);
	
	for(i=0; i < vector_event.size(); ++i)
		events.push_back( new Event(vector_event[i]) );
}

Activity::Activity(Event* event)
{
	events.push_back( new Event(event) );
}

	/* Getters */

Label Activity::get_label(unsigned num)
{
	return label_activity[num];
}
unsigned Activity::get_nb_label() { return label_activity.size(); }
bool Activity::get_inout() { return inout; }

unsigned Activity::get_person() { return main_person; }
unsigned Activity::get_nb_persons() { return persons.size(); }

bool Activity::get_is_in() { return is_in; }
bool Activity::get_is_out() { return is_out; }
bool Activity::get_is_inout() { return is_inout; }


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
	output << "\tNUMBER OF LABELS: " << label_activity.size() << endl << "\t";	
	for(i=0; i < label_activity.size(); ++i)
		output << label_activity[i] << " ";
	output << endl;
	
	output << "\t";
	for(i=0; i<events.size(); ++i)
		events[i]->print_event(output);
	
	
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
	cout << "\tNUMBER OF LABELS: " << label_activity.size() << endl << "\t";	
	for(i=0; i < label_activity.size(); ++i)
		cout << label_activity[i] << " ";
	cout << endl;
	
	for(i=0; i<events.size(); ++i)
		events[i]->print_event();
	
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
void Activity::attributes_unknown_SHA(bool only_one_person)
{
	if( only_one_person )
	{
		for( auto it = puces_with_time.begin(); it != puces_with_time.end(); ++it )
		{
			if( it->first != 0 )
			{
				for(unsigned i=0; i < events.size(); ++i)
				{
					if( events[i]->sha_exist() && events[i]->get_sha_person_id() == 0 )
						events[i]->set_SHA(it->first, SHA_SURE);
				}
			}
		}
	}
}

void Activity::attributes_SHA(unsigned puce, unsigned num_event, bool only_one_person)
{
	bool unknown_sha = true;
	
	// si la puce appartient à quelqu'un ou s'il n'y a qu'une seule personne dans l'activité pour l'instant (probablement le 0)
	if( puce != 0 || puces_with_time.size() == 1 )
		events[num_event]->set_SHA(puce, SHA_SURE);
		
	else
	{
		//gives the SHA to the only person if there is no one else
		if( only_one_person )
		{
			for( auto it = puces_with_time.begin(); it != puces_with_time.end(); ++it )
			{
				if( it->first != 0 )
				{
					events[num_event]->set_SHA(it->first, SHA_SURE);
					unknown_sha = false;
				}
			} 
				
			//gives the SHA to no one (ambiguité = -1)
			if ( unknown_sha )
				events[num_event]->set_SHA(-1, SHA_POSSIBLE);
		}

		//gives the SHA to no one (ambiguité = -1)
		else
			events[num_event]->set_SHA(-1, SHA_POSSIBLE);
	}
}


void Activity::attributes_alarm(unsigned puce, unsigned num_event, bool only_one_person)
{
	bool unknown_alarm = true;
	
	// si la puce appartient à quelqu'un ou s'il n'y a qu'une seule personne dans l'activité pour l'instant (probablement le 0)
	if( puce != 0 || puces_with_time.size() == 1 )
		events[num_event]->set_alarm(puce);
		
	else
	{
		//gives the alarm to the only person if there is no one else
		if( only_one_person )
		{
			for( auto it = puces_with_time.begin(); it != puces_with_time.end(); ++it )
			{
				if( it->first != 0 )
				{
					events[num_event]->set_alarm(it->first);
					unknown_alarm = false;
				}
			} 
				
			//gives the alarm to no one (ambiguité = -1)
			if ( unknown_alarm )
				events[num_event]->set_alarm(-1);
		}

		//gives the alarm to no one (ambiguité = -1)
		else
			events[num_event]->set_alarm(-1);
	}	
}

/**
	* \name attributes_SHA
	* \brief Attributes the SHAs to their owners.
	* 
	* Fills the "different_puces" vector with all the persons in the current activity.
	* 
	* Knows who are the first person who has entered the room.
	* 
	* \param first_person_id : first person who has entered the room.
*/
void Activity::attributes_events()
{
	unsigned puce;
	for(unsigned i=0; i<events.size(); ++i)
	{
		puce = events[i]->get_id_puce();
		
		// if we didn't add the person yet (first time entering the room) we add them to puces_with_time
		if( puces_with_time.find(puce) == puces_with_time.end() )
		{
			puces_with_time[puce] = i;
			if( puces_with_time.size() > 2 || ( puces_with_time.size() == 2 && puces_with_time.find(0) != puces_with_time.end() ) )
				only_one_person = false;
		}
		
		if( events[i]->get_event() == CODE_SHA || events[i]->get_event() == CODE_SHA_DURING_ALARM )
			attributes_SHA(puce, i, only_one_person);
			
		else if( events[i]->get_event() == CODE_ALARM )
			attributes_alarm(puce, i, only_one_person);
	}
	
	// attribue les SHA inconnues s'il n'y a eu qu'une personne dans l'activité
	attributes_unknown_SHA(only_one_person);
}

// Identify who is the first person who has entered the room
int Activity::first_person_entered()
{
	int first_puce = -1;
	unsigned prec = 1000;
	if( puces_with_time.size() > 0 )
	{
		if( puces_with_time.size() == 1 )
			return puces_with_time.begin()->first;
		else
		{
			for( auto it = puces_with_time.begin(); it != puces_with_time.end(); ++it )
			{
				if( it->first != 0 && it->second < prec)
				{
					first_puce = it->first;
					prec = it->first;
				}
			}
		}
	}
	return first_puce;
}


void Activity::split_activities(vector<Activity*>& split_activity, unsigned first_person_id)
{
	map<unsigned, vector<Event*> > different_activities; // key = person, value = vector of events

	// Accords events to each persons
	for(unsigned i=0; i<events.size(); ++i)
	{
		person = events[i]->get_id_puce();
		
		// this event is related to everyone
		if( person==0 )
		{
			for( auto it = puces_with_time.begin(); it != puces_with_time.end(); ++it )
				if( it->first != 0 )
					different_activities[it->first].push_back( new Event(events[i]) );
		}
		// this event is related to a specific person
		else
			different_activities[person].push_back( new Event(events[i]) );
	}	
	
	// Create activities for each persons with the events we accorded to each persons
	for(auto it = different_activities.begin(); it != different_activities.end(); ++it) 
	{		
		split_activity.push_back( new Activity(it->second, it->first, puces_with_time) ); 
		if( it->first == first_person_id )
			split_activity[split_activity.size()-1]->first_person = true;
		
		// find labels for the Activity we just created
		/** a refaire */
		for(auto it2 = puces_to_SHA.begin(); it2 != puces_to_SHA.end(); ++it2) 
			if( it->first == it2->first )
				split_activity[split_activity.size()-1]->finding_labels(it2->second);
	}
	/** + faire les abandons d'activités */
	
	
	// Release the allocated memory for the different_activities map
	destroy_map_different_activities(different_activities);
}

/**
	* \name activity_per_person
	* \brief Split activities if there is several persons in one activity.
	* 
	* \param split_activity : vector to be filled with the activities split from the current activity.
*/
void Activity::activity_per_person(vector<Activity*>& split_activity)
{
	// Removes all previous activities not related to our business anymore
	for(unsigned i=0; i<split_activity.size(); ++i)
		split_activity[i]->~Activity();
	split_activity.clear();


	++id_debug;

	// Who are the person(s) in the current activity ? + events attribution
	attributes_events();
	unsigned first_person_id = first_person_entered();
	
	
	/** REFAIRE CES IF **/
	
	if(only_one_person)
	{
		first_person = true;
		if(puces_with_time.size()==1)
		{
			main_person = puces_with_time.begin()->first;
			finding_labels();				
		}
		else
		{
			for(auto it2 = puces_with_time.begin(); it2 != puces_with_time.end(); ++it2) 
			{
				if(it2->first != 0)
				{
					main_person = it2->first;
					finding_labels();
				}
			}
		}
	}
	/** peut etre que ce n'est plus utile de scinder les activités si nb personne > 1 */
	else
		split_activities(split_activity, first_person_id);
		
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




	/* Finding labels */

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
	
	return index_out;
}


void Activity::finding_labels()
{	
	unsigned index_out = finding_in_out_inout();
		
	// inout
	if(index_out == 0)
	{
		//cout << " je suis dans inout "<< endl;
		finding_label_inout(SHA);
	}
	
	// in and out
	else
	{
		//cout << "je suis dans in et out " << endl;
		finding_label_in(index_out);
		finding_label_out(index_out);
	}
	
}

bool Activity::finding_label_in(unsigned index_ending)
{
	int alarm_index = -1;
	int SHA_index = -1;
	int SHA_during_alarm_index = -1;
	unsigned id_line_event;
	unsigned code_event;
	
	for(unsigned num_event=0; num_event < index_ending; ++num_event)
	{
		id_line_event = events[num_event]->get_unique_id();
		code_event = events[num_event]->get_event();
		
		if( alarm != -1 )
			alarm_index = num_event;
			
		else if( sha != NULL )
		{
			if( events[num_event]->get_sha_person_id() > 0 )
			{
				if( code_event == CODE_SHA )
					SHA_index = num_event;
				else
					SHA_during_alarm_index = num_event;
			}
			else
			{
				label_activity.push_back( ABANDON_IN );
				return false;
			}
		}
	}
	
	
	is_in = true;
	
	// Alarm 0, SHA taken 0, SHA taken during alarm 0
	if( alarm_index == -1 && SHA_index == -1 && SHA_during_alarm_index == -1 )
		label_activity.push_back( NOT_IN_NO_ALARM );
		
	// Alarm 0, SHA taken 0, SHA taken during alarm 1
	else if( alarm_index == -1 && SHA_index == -1 && SHA_during_alarm_index != -1 )
		label_activity.push_back( IN_DURING_ALARM );
		
	// Alarm 0, SHA taken 1, SHA taken during alarm 0
	else if( alarm_index == -1 && SHA_index != -1 && SHA_during_alarm_index == -1 )
		label_activity.push_back( IN_NO_ALARM );
		
	// Alarm 0, SHA taken 1, SHA taken during alarm 1
	else if( alarm_index == -1 && SHA_index != -1 && SHA_during_alarm_index != -1 )
	{
		/*
		if(SHA_index_sure < alarm_index)
			//cerr << "weird ! sha pris AVANT l'alarme" << endl;
			label_activity.push_back( IN_WEIRD_SUR );
		else
		{
			
			label_activity.push_back( IN_AFTER_ALARM );
		}
		*/
	}
	
	// Alarm 1, SHA taken 0, SHA taken during alarm 0
	else if( alarm_index != -1 && SHA_index == -1 && SHA_during_alarm_index == -1 )
		label_activity.push_back( NOT_IN_ALARM );
		
	// Alarm 1, SHA taken 0, SHA taken during alarm 1
	else if( alarm_index != -1 && SHA_index == -1 && SHA_during_alarm_index_sure != -1 )
	{
		/*
		if(alarm_index < SHA_during_alarm_index_sure)
			label_activity.push_back( IN_DURING_ALARM );
		else
			label_activity.push_back( IN_WEIRD_SUR );
		*/
	}
	
	// Alarm 1, SHA taken 1, SHA taken during alarm 0
	else if(alarm_index != -1 && SHA_index != -1 && SHA_during_alarm_index == -1  )
	{
		if(alarm_index < SHA_index)
			label_activity.push_back( IN_AFTER_ALARM );
		else
			label_activity.push_back( IN_NO_ALARM );
	}
	
	// Alarm 1, SHA taken 1, SHA taken during alarm 1
	else if( alarm_index != -1 && SHA_index != -1 && SHA_during_alarm_index != -1 )
	{
		/*
		if(alarm_index < SHA_during_alarm_index_sure < SHA_index_sure)
			label_activity.push_back( IN_DURING_ALARM );
		else
			label_activity.push_back( IN_WEIRD_SUR );
		*/
	}
	
	else
		label_activity.push_back( IMPOSSIBLE );
	return true;
	
}
void Activity::finding_label_out(unsigned index_begining, vector<Sha*>& SHA)
{
	int alarm_index = -1;
	int SHA_index = -1;
	int SHA_during_alarm_index = -1;
	unsigned id_line_event;
	
	for(unsigned i=index_begining; i < events.size(); ++i)
	{
		id_line_event = events[i]->get_unique_id();
		//cout << id_line_event << endl;
		
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
	
	is_out = true;
	
	// Alarm 0, SHA taken 0, SHA taken during alarm 0
	if( alarm_index == -1 && SHA_index == -1 && SHA_during_alarm_index == -1 )
		label_activity.push_back( NOT_OUT_NO_ALARM );
		
	// Alarm 0, SHA taken 0, SHA taken during alarm 1
	else if( alarm_index == -1 && SHA_index == -1 && SHA_during_alarm_index != -1 )
		label_activity.push_back( OUT_DURING_ALARM );
		
	// Alarm 0, SHA taken 1, SHA taken during alarm 0
	else if( alarm_index == -1 && SHA_index != -1 && SHA_during_alarm_index == -1 )
		label_activity.push_back( OUT_NO_ALARM );
		
	// Alarm 0, SHA taken 1, SHA taken during alarm 1
	else if( alarm_index == -1 && SHA_index != -1 && SHA_during_alarm_index != -1 )
	{
		/*
		if(SHA_index_sure < alarm_index)
			//cerr << "weird ! sha pris AVANT l'alarme" << endl;
			label_activity.push_back( IN_WEIRD_SUR );
		else
		{
			
			label_activity.push_back( IN_AFTER_ALARM );
		}
		*/
	}
	
	// Alarm 1, SHA taken 0, SHA taken during alarm 0
	else if( alarm_index != -1 && SHA_index == -1 && SHA_during_alarm_index == -1 )
		label_activity.push_back( NOT_OUT_ALARM );
		
	// Alarm 1, SHA taken 0, SHA taken during alarm 1
	else if( alarm_index != -1 && SHA_index == -1 && SHA_during_alarm_index_sure != -1 )
	{
		/*
		if(alarm_index < SHA_during_alarm_index_sure)
			label_activity.push_back( IN_DURING_ALARM );
		else
			label_activity.push_back( IN_WEIRD_SUR );
		*/
	}
	
	// Alarm 1, SHA taken 1, SHA taken during alarm 0
	else if(alarm_index != -1 && SHA_index != -1 && SHA_during_alarm_index == -1  )
	{
		/*
		if(SHA_during_alarm_index_sure < SHA_index_sure)
		{
			//is_in = true;
			label_activity.push_back( IN_DURING_ALARM );
		}
		else
			//cerr << "weird ! alarme retenti alors qu'on a pris le SHA" << endl; 
			label_activity.push_back( IN_WEIRD_SUR );
		*/
	}
	
	// Alarm 1, SHA taken 1, SHA taken during alarm 1
	else if( alarm_index != -1 && SHA_index != -1 && SHA_during_alarm_index != -1 )
	{
		/*
		if(alarm_index < SHA_during_alarm_index_sure < SHA_index_sure)
			label_activity.push_back( IN_DURING_ALARM );
		else
			label_activity.push_back( IN_WEIRD_SUR );
		*/
	}
	
	else
		//cerr << "CAS IMPOSSIBLE NON PRIS EN COMPTE" << endl;
		label_activity.push_back( IN_IMPOSSIBLE_SUR );
	
}
void Activity::finding_label_inout(vector<Sha*>& SHA)
{
	int alarm_index = -1;
	int SHA_index = -1;
	int SHA_during_alarm_index = -1;
	unsigned id_line_event;
	
	for(unsigned i=0; i < events.size(); ++i)
	{
		id_line_event = events[i]->get_unique_id();
		//cout << id_line_event << endl;
		
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
	
	is_inout = true;
	
	// Alarm 0, SHA taken 0, SHA taken during alarm 0
	if( alarm_index == -1 && SHA_index == -1 && SHA_during_alarm_index == -1 )
		label_activity.push_back( NOT_INOUT_NO_ALARM );
		
	// Alarm 0, SHA taken 0, SHA taken during alarm 1
	else if( alarm_index == -1 && SHA_index == -1 && SHA_during_alarm_index != -1 )
		label_activity.push_back( INOUT_DURING_ALARM );
		
	// Alarm 0, SHA taken 1, SHA taken during alarm 0
	else if( alarm_index == -1 && SHA_index != -1 && SHA_during_alarm_index == -1 )
		label_activity.push_back( INOUT_NO_ALARM );
		
	// Alarm 0, SHA taken 1, SHA taken during alarm 1
	else if( alarm_index == -1 && SHA_index != -1 && SHA_during_alarm_index != -1 )
	{
		/*
		if(SHA_index_sure < alarm_index)
			//cerr << "weird ! sha pris AVANT l'alarme" << endl;
			label_activity.push_back( IN_WEIRD_SUR );
		else
		{
			
			label_activity.push_back( IN_AFTER_ALARM );
		}
		*/
	}
	
	// Alarm 1, SHA taken 0, SHA taken during alarm 0
	else if( alarm_index != -1 && SHA_index == -1 && SHA_during_alarm_index == -1 )
		label_activity.push_back( NOT_INOUT_ALARM );
		
	// Alarm 1, SHA taken 0, SHA taken during alarm 1
	else if( alarm_index != -1 && SHA_index == -1 && SHA_during_alarm_index_sure != -1 )
	{
		/*
		if(alarm_index < SHA_during_alarm_index_sure)
			label_activity.push_back( IN_DURING_ALARM );
		else
			label_activity.push_back( IN_WEIRD_SUR );
		*/
	}
	
	// Alarm 1, SHA taken 1, SHA taken during alarm 0
	else if(alarm_index != -1 && SHA_index != -1 && SHA_during_alarm_index == -1  )
	{
		/*
		if(SHA_during_alarm_index_sure < SHA_index_sure)
		{
			//activity_sure_in = true;
			label_activity.push_back( IN_DURING_ALARM );
		}
		else
			//cerr << "weird ! alarme retenti alors qu'on a pris le SHA" << endl; 
			label_activity.push_back( IN_WEIRD_SUR );
		*/
	}
	
	// Alarm 1, SHA taken 1, SHA taken during alarm 1
	else if( alarm_index != -1 && SHA_index != -1 && SHA_during_alarm_index != -1 )
	{
		/*
		if(alarm_index < SHA_during_alarm_index_sure < SHA_index_sure)
			label_activity.push_back( IN_DURING_ALARM );
		else
			label_activity.push_back( IN_WEIRD_SUR );
		*/
	}
	
	else
		//cerr << "CAS IMPOSSIBLE NON PRIS EN COMPTE" << endl;
		label_activity.push_back( IN_IMPOSSIBLE_SUR );
}

