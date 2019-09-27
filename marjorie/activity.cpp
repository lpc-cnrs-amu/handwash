#include "activity.hpp"
#include <algorithm>
#include <map>
#define LAST_EVENT events.size()-1
#define MINUTE_MAX 10
#define SHA_SURE true
#define SHA_POSSIBLE false
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
	this->first_person = copy->first_person;
	this->only_one_person = copy->only_one_person;
	this->is_in = copy->is_in;
	this->is_out = copy->is_out;
	this->is_inout = copy->is_inout;
	this->is_in_abandon = copy->is_in_abandon;
	this->is_out_abandon = copy->is_out_abandon;
	this->is_inout_abandon = copy->is_inout_abandon;
	
	this->alarm_index_in = copy->alarm_index_in;
	this->SHA_index_in = copy->SHA_index_in;
	this->SHA_during_alarm_index_in = copy->SHA_during_alarm_index_in;
	
	this->alarm_index_out = copy->alarm_index_out;
	this->SHA_index_out = copy->SHA_index_out;
	this->SHA_during_alarm_index_out = copy->SHA_during_alarm_index_out;
	
	this->alarm_index_inout = copy->alarm_index_inout;
	this->SHA_index_inout = copy->SHA_index_inout;
	this->SHA_during_alarm_index_inout = copy->SHA_during_alarm_index_inout;
			
	for(i=0; i < copy->events.size(); ++i)
		this->events.push_back( new Event(copy->events[i]) );
		
	for( auto it = copy->puces_with_time.begin(); it != copy->puces_with_time.end(); ++it )
		puces_with_time.insert(std::make_pair(it->first, it->second ));
		
	for(i=0; i < copy->label_activity.size(); ++i)
		this->label_activity.push_back( copy->label_activity[i] );
}

/**
	* \brief Activity Constructor.
	*
	* \param filename : file containing every instances in csv format.
*/
Activity::Activity(vector<Event*>& vector_event, int p, 
	map<int, unsigned>& puces_with_time_copy, bool one_person)
{
	unsigned i;
	
	main_person = p;
	only_one_person = one_person;
	
	for( auto it = puces_with_time_copy.begin(); it != puces_with_time_copy.end(); ++it )
		puces_with_time.insert(std::make_pair(it->first, it->second ));
	
	for(i=0; i < vector_event.size(); ++i)
		events.push_back( new Event(vector_event[i]) );
}

Activity::Activity(Activity* copy, vector<Event*>& vector_event)
{
	unsigned i;
	
	this->main_person = copy->main_person;
	this->first_person = copy->first_person;
	this->only_one_person = copy->only_one_person;
	this->is_in = copy->is_in;
	this->is_out = copy->is_out;
	this->is_inout = copy->is_inout;
	this->is_in_abandon = copy->is_in_abandon;
	this->is_out_abandon = copy->is_out_abandon;
	this->is_inout_abandon = copy->is_inout_abandon;
	
	this->alarm_index_in = copy->alarm_index_in;
	this->SHA_index_in = copy->SHA_index_in;
	this->SHA_during_alarm_index_in = copy->SHA_during_alarm_index_in;
	
	this->alarm_index_out = copy->alarm_index_out;
	this->SHA_index_out = copy->SHA_index_out;
	this->SHA_during_alarm_index_out = copy->SHA_during_alarm_index_out;
	
	this->alarm_index_inout = copy->alarm_index_inout;
	this->SHA_index_inout = copy->SHA_index_inout;
	this->SHA_during_alarm_index_inout = copy->SHA_during_alarm_index_inout;
			
	for(i=0; i < vector_event.size(); ++i)
		this->events.push_back( new Event(vector_event[i]) );
		
	for( auto it = copy->puces_with_time.begin(); it != copy->puces_with_time.end(); ++it )
		puces_with_time.insert(std::make_pair(it->first, it->second ));
		
	for(i=0; i < copy->label_activity.size(); ++i)
		this->label_activity.push_back( copy->label_activity[i] );
}

Activity::Activity(Event* event)
{
	events.push_back( new Event(event) );
}

	/* Getters */

unsigned Activity::get_chamber() { return events[0]->get_chamber(); }
bool Activity::is_alone() { return only_one_person; }

Label Activity::get_label(unsigned num)
{
	return label_activity[num];
}
unsigned Activity::get_nb_label() { return label_activity.size(); }

bool Activity::get_is_in() { return is_in; }
bool Activity::get_is_out() { return is_out; }
bool Activity::get_is_inout() { return is_inout; }
int Activity::get_person() { return main_person; }

bool Activity::is_abandon_inout()
{
	return is_inout_abandon;
}
bool Activity::is_abandon_in()
{
	return is_in_abandon;
}
bool Activity::is_abandon_out()
{
	return is_out_abandon;
}


unsigned Activity::get_index_out()
{
	for( unsigned i=0; i<events.size(); ++i )
		if( !events[i]->get_in() )
			return i;
	return 0;
}

string Activity::get_start_time(bool out)
{
	unsigned index_out = get_index_out();
	
	// the start for the 'out', so it's not the activity's start
	if( out && index_out != 0 )
		return events[index_out]->get_date() + " " + events[index_out]->get_time();	
	else
		return events[0]->get_date() + " " + events[0]->get_time();
		
	return "NO OUT";
}


string Activity::get_end_time(bool in)
{
	unsigned index_out = get_index_out();
	
	// the end for the 'in', so it's not the activity's end
	if( in && index_out != 0 )
		return events[index_out-1]->get_date() + " " + events[index_out-1]->get_time();	
	else
		return events[events.size()-1]->get_date() + " " + events[events.size()-1]->get_time();
		
	return "NO IN";
}

int Activity::get_duration(unsigned in_out_inout)
{
	unsigned index_out = get_index_out();
	
	if( in_out_inout == 0 && index_out == 0 )
		return events[events.size()-1]->ecart_time(events[0]);
	else if( in_out_inout == 1 && index_out != 0 )
		return events[index_out-1]->ecart_time(events[0]);
	else if( in_out_inout == 2 && index_out != 0 )
		return events[events.size()-1]->ecart_time(events[index_out]);
		
	return -1;
}

Label Activity::get_label_in()
{
	for( unsigned i=0; i<label_activity.size(); ++i )
	{
		if( label_activity[i] == IN_NO_ALARM || 
			label_activity[i] == IN_AFTER_ALARM || 
			label_activity[i] == IN_DURING_ALARM || 
			label_activity[i] == NOT_IN_NO_ALARM || 
			label_activity[i] == NOT_IN_ALARM || 
			label_activity[i] == ABANDON_IN )
			return label_activity[i];
	}
	return IMPOSSIBLE;
}

Label Activity::get_label_out()
{
	for( unsigned i=0; i<label_activity.size(); ++i )
	{
		if( label_activity[i] == OUT_NO_ALARM || 
			label_activity[i] == OUT_AFTER_ALARM || 
			label_activity[i] == OUT_DURING_ALARM || 
			label_activity[i] == NOT_OUT_NO_ALARM || 
			label_activity[i] == NOT_OUT_ALARM || 
			label_activity[i] == ABANDON_OUT )
			return label_activity[i];
	}
	return IMPOSSIBLE;
}

Label Activity::get_label_inout()
{
	for( unsigned i=0; i<label_activity.size(); ++i )
	{
		if( label_activity[i] == INOUT_NO_ALARM || 
			label_activity[i] == INOUT_AFTER_ALARM || 
			label_activity[i] == INOUT_DURING_ALARM || 
			label_activity[i] == NOT_INOUT_NO_ALARM || 
			label_activity[i] == NOT_INOUT_ALARM || 
			label_activity[i] == ABANDON_INOUT )
			return label_activity[i];
	}
	return IMPOSSIBLE;
}

int Activity::get_alarm_index_in()
{
	return alarm_index_in;
}

int Activity::get_SHA_index_in()
{
	return SHA_index_in;
}

int Activity::get_SHA_during_alarm_index_in()
{
	return SHA_during_alarm_index_in;
}

int Activity::get_alarm_index_out()
{
	return alarm_index_out;
}

int Activity::get_SHA_index_out()
{
	return SHA_index_out;
}

int Activity::get_SHA_during_alarm_index_out()
{
	return SHA_during_alarm_index_out;
}

int Activity::get_alarm_index_inout()
{
	return alarm_index_inout;
}

int Activity::get_SHA_index_inout()
{
	return SHA_index_inout;
}

int Activity::get_SHA_during_alarm_index_inout()
{
	return SHA_during_alarm_index_inout;
}
	


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
	output << "\tNUMBER OF PERSON: " << puces_with_time.size() << endl << "\t";	
	for(auto it = puces_with_time.begin(); it != puces_with_time.end(); ++it)
		output << it->first << " ";
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
	cout << "\tNUMBER OF PERSON: " << puces_with_time.size() << endl << "\t";	
	for( auto it=puces_with_time.begin(); it != puces_with_time.end(); ++it )
		cout << it->first << " ";
	cout << endl;
	cout << "\tNUMBER OF LABELS: " << label_activity.size() << endl << "\t";	
	for(i=0; i < label_activity.size(); ++i)
		cout << label_activity[i] << " ";
	cout << endl;
	
	if(is_inout)
		cout << "\tINOUT" << endl;
	else
		cout << "\tPAS INOUT" << endl;
	if(is_in)
		cout << "\tIN" << endl;
	else
		cout << "\tPAS IN" << endl;
	if(is_out)
		cout << "\tOUT" << endl;
	else
		cout << "\tPAS OUT" << endl;
	
	for(i=0; i<events.size(); ++i)
		events[i]->print_event();
		
/*
		bool first_person = false; // is the main person also the first person who have entered the room ?
		bool only_one_person = true; // true => there is one person in the activity, else false
		
		int alarm_index_in = -1;
		int SHA_index_in = -1;
		int SHA_during_alarm_index_in = -1;
		int alarm_index_out = -1;
		int SHA_index_out = -1;
		int SHA_during_alarm_index_out = -1;
		int alarm_index_inout = -1;
		int SHA_index_inout = -1;
		int SHA_during_alarm_index_inout = -1;	
	*/
}


	/* Append event to the current activity */


/**
	* \name check_and_append_event_to_activity
	* \brief Check if the event can be appended and do it if it can.
	* 
	* \param event : an event.
	* 
	* \return -1 if we have to ignored the event (useless code)
	* 		   1 if we can append this event
	* 		   0 if we can't append this event
*/
int Activity::check_and_append_event_to_activity(Event* event)
{
	int result = same_activity(event);
	if( result != 1 )
		return result;
		
	events.push_back( new Event(event) );
	return 1;
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
	* \return -1 if we have to ignored the event (useless code)
	* 		   1 if we can append this event
	* 		   0 if we can't append this event
*/
int Activity::same_activity(Event* event)
{
	
	// si c'est un code interprété : on ne le prend pas en compte
	if( !event->code_correct() )
		return -1;
	
	// si SHA avant entrée est différent d'au plus 2 secondes => ne pas le prendre en compte
	/** REFAIRE ECART TIME */
	if( events.size() == 1 && 
		( (events[LAST_EVENT]->get_event() == CODE_SHA || events[LAST_EVENT]->get_event() == CODE_SHA_DURING_ALARM) 
		&& event->ecart_time(events[LAST_EVENT]) > 2) )
		return 0;
	
	if( events.empty() )
		return 1;
	if( events[LAST_EVENT]->get_chamber() != event->get_chamber() ) 	
		return 0;
	
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
			return 1;
		
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
					return 1;
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
					return 1;
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
			return 1;
			
		else if( event->get_hour() == events[LAST_EVENT]->get_hour() && 
				 event->get_minutes() <= events[LAST_EVENT]->get_minutes()+MINUTE_MAX)
			return 1;
			
	}

	return 0;
}

/**
	* \name attributes_events
	* \brief Attributes the events "SHA" and "alarm" to their owners.
	* 
	* Fills the "puces_with_time" map with all the persons in the current activity
	* and their number of entrance.
	* 
*/
void Activity::attributes_events()
{
	int puce;
	for(unsigned i=0; i<events.size(); ++i)
	{
		puce = events[i]->get_id_puce();
		
		// if we didn't add the person yet (first time entering the room) we add them to puces_with_time
		if( puces_with_time.find(puce) == puces_with_time.end() )
		{
			puces_with_time[puce] = i;
			if( puces_with_time.size() > 2 || ( puces_with_time.size() == 2 && puces_with_time.find(0) == puces_with_time.end() ) )
				only_one_person = false;
		}
		
		if( events[i]->get_event() == CODE_SHA || events[i]->get_event() == CODE_SHA_DURING_ALARM )
			attributes_SHA(puce, i, only_one_person, events[i]->get_event());
			
		else if( events[i]->get_event() == CODE_ALARM )
			attributes_alarm(puce, i, only_one_person);
	}
	
	// attribue les SHA inconnues s'il n'y a eu qu'une personne dans l'activité
	attributes_unknown_SHA(only_one_person);
	attributes_unknown_alarm(only_one_person);
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
						events[i]->set_SHA(events[i]->get_code_sha(), it->first, SHA_SURE);
				}
			}
		}
	}
}

void Activity::attributes_unknown_alarm(bool only_one_person)
{
	if(only_one_person)
	{
		for( auto it = puces_with_time.begin(); it != puces_with_time.end(); ++it )
		{
			if( it->first != 0 )
			{
				for(unsigned i=0; i < events.size(); ++i)
				{
					if( events[i]->alarm_exist() && events[i]->get_attribution_alarm() == 0 )
						events[i]->set_alarm(it->first);
				}
			}
		}		
	}
}

void Activity::attributes_SHA(int puce, unsigned num_event, bool only_one_person, 
	unsigned code_sha)
{
	bool unknown_sha = true;
	
	// si la puce appartient à quelqu'un ou s'il n'y a qu'une seule personne dans l'activité pour l'instant (probablement le 0)
	if( puce != 0 || puces_with_time.size() == 1 )
		events[num_event]->set_SHA(code_sha, puce, SHA_SURE);
		
	else
	{
		//gives the SHA to the only person if there is no one else
		if( only_one_person )
		{
			for( auto it = puces_with_time.begin(); it != puces_with_time.end(); ++it )
			{
				if( it->first != 0 )
				{
					events[num_event]->set_SHA(code_sha, it->first, SHA_SURE);
					unknown_sha = false;
				}
			} 
				
			//gives the SHA to no one (ambiguité = -1)
			if ( unknown_sha )
				events[num_event]->set_SHA(code_sha, -1, SHA_POSSIBLE);
		}

		//gives the SHA to no one (ambiguité = -1)
		else
			events[num_event]->set_SHA(code_sha, -1, SHA_POSSIBLE);
	}
}

int Activity::last_person()
{
	int last_puce = -1;
	unsigned prec = 0;
	if( puces_with_time.size() > 0 )
	{
		if( puces_with_time.size() == 1 )
			return puces_with_time.begin()->first;
		else
		{
			for( auto it = puces_with_time.begin(); it != puces_with_time.end(); ++it )
			{
				if( it->first != 0 && it->second >= prec)
				{
					last_puce = it->first;
					prec = it->second;
				}
			}
		}
	}
	return last_puce;	
}

void Activity::attributes_alarm(int puce, unsigned num_event, bool only_one_person)
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

		//gives the alarm to the last person who entered the room
		else
			events[num_event]->set_alarm(last_person());
	}	
}

// On supprime les puces 0 après un 6 s'il n'y a que des puces 0
void Activity::pretreat_activity()
{
	remove_only_5_6();
	
	unsigned code, puce, j;
	bool remove = false;
	
	for(unsigned i=0; i<events.size(); ++i)
	{
		code = events[i]->get_event();
		if( code == CODE_CLOSE_DOOR )
		{
			remove = true;
			for(j = i+1; j<events.size(); ++j)
			{
				puce = events[j]->get_id_puce();
				if( puce != 0 )
				{
					remove = false;
					break;
				}
			}
		}
		if(remove)
		{
			for(j = i+1; j<events.size(); ++j)
				events[j]->~Event();
			events.erase(events.begin() + (i+1), events.end());
			break;
		}
	}
}

void Activity::remove_only_5_6()
{
	unsigned last_index = 0;
	
	for(unsigned i=0; i < events.size(); i += 2)
	{
		if(i+1 < events.size())
		{

			if( (events[i]->get_event() != CODE_OPEN_DOOR ||
				 events[i+1]->get_event() != CODE_CLOSE_DOOR) &&
				(events[i]->get_event() != CODE_OPEN_DOOR ||
				 events[i+1]->get_event() != CODE_OPEN_DOOR) &&
				(events[i]->get_event() != CODE_CLOSE_DOOR ||
				 events[i+1]->get_event() != CODE_OPEN_DOOR))
			{
				last_index = i;
				break;
			}
		}
	}
	
	for(unsigned i=0; i<last_index; ++i)
		events[i]->~Event();
	
	events.erase(events.begin(), events.begin() + last_index);
}

void Activity::cut_activity(vector<Activity*>& split_activity)
{
	unsigned code, code_next, code_next_2;
	vector<Event*> cumulative_events;
	
	for(unsigned i=0; i<events.size(); ++i)
	{
		cumulative_events.push_back(new Event(events[i]));
		code = events[i]->get_event();
		if( code == CODE_CLOSE_DOOR )
		{
			if(i+1 < events.size())
			{
				code_next = events[i+1]->get_event();
				if(code_next == CODE_ALARM)
				{
					cumulative_events.push_back(new Event(events[i+1]));
					++i;
					if(i+1 < events.size())
					{
						code_next_2 = events[i+1]->get_event();
						if(code_next_2 == CODE_OPEN_DOOR)
						{
							if(i+2 < events.size() && events[i+2]->get_event() == CODE_SHOE_IN)
								cut_activity_bis(split_activity, cumulative_events);
						}
					}
				}
				else if(code_next == CODE_OPEN_DOOR)
				{
					if(i+2 < events.size() && events[i+2]->get_event() == CODE_SHOE_IN)
						cut_activity_bis(split_activity, cumulative_events);
				}
			}
		}		
	}
	cut_activity_bis(split_activity, cumulative_events);
}

void Activity::cut_activity_bis(vector<Activity*>& split_activity,
	vector<Event*>& cumulative_events)
{
	split_activity.push_back(new Activity(this, cumulative_events));
	for(unsigned i=0; i<cumulative_events.size(); ++i)
		cumulative_events[i]->~Event();
	cumulative_events.clear();
}


void Activity::remove_after_6()
{
	unsigned code, code_next, puce, j;
	bool remove = false;
	
	for(unsigned i=0; i<events.size(); ++i)
	{
		code = events[i]->get_event();
		if( code == CODE_CLOSE_DOOR )
		{
			remove = true;
			for(j = i+1; j<events.size(); ++j)
			{
				puce = events[j]->get_id_puce();
				code_next = events[j]->get_event();
				if( puce != 0 && code_next != CODE_ALARM )
				{
					remove = false;
					break;
				}
			}
		}
		if(remove)
		{
			for(j = i+1; j<events.size(); ++j)
				events[j]->~Event();
			events.erase(events.begin() + (i+1), events.end());
			break;
		}
	}
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
					prec = it->second;
				}
			}
		}
	}
	return first_puce;
}

void destroy_vector(vector<Activity*>& vect)
{
	for(unsigned i=0; i<vect.size(); ++i)
		vect[i]->~Activity();
	vect.clear();
}

void Activity::add_activity(vector<Activity*>& destination, vector<Activity*>& send)
{
	destroy_vector(destination);
	for(unsigned i=0; i<send.size(); ++i)
	{
		destination.push_back(new Activity(send[i]));
		if(destination[destination.size()-1]->events[0]->get_unique_id() == 3024865)
			destination[destination.size()-1]->print_activity();
	}
}

void Activity::split_activities(vector<Activity*>& split_activity,int first_person_id)
{
	map<int, vector<Event*> > different_activities; // key = person, value = vector of events
	vector<Activity*> tmp_cut_activity;
	vector<Activity*> save_activity;
	int person;
	
	// Accords events to each persons
	for(unsigned i=0; i<events.size(); ++i)
	{
		person = events[i]->get_id_puce();
		
		// this event is related to everyone
		if( ( !events[i]->sha_exist() || (events[i]->sha_exist() && events[i]->get_sha_person_id()==-1) ) && !events[i]->alarm_exist() && person==0 )
		{
			for( auto it = puces_with_time.begin(); it != puces_with_time.end(); ++it )
				if( it->first != 0 )
					different_activities[it->first].push_back( new Event(events[i]) );
		}
		// this event is related to a specific person
		else
		{
			if( events[i]->alarm_exist() )
				different_activities[events[i]->get_attribution_alarm()].push_back( new Event(events[i]) );
			else if( events[i]->sha_exist() )
				different_activities[events[i]->get_sha_person_id()].push_back( new Event(events[i]) );
			else
				different_activities[person].push_back( new Event(events[i]) );
		}
	}	
	
	// Create activities for each persons with the events we accorded to each persons
	for( auto it = different_activities.begin(); it != different_activities.end(); ++it ) 
	{		
		split_activity.push_back( new Activity(it->second, it->first, puces_with_time, false) ); 
		split_activity[split_activity.size()-1]->pretreat_activity();
		if( it->first == first_person_id )
			split_activity[split_activity.size()-1]->first_person = true;

		// find labels for the Activity we just created
		for( auto it2 = puces_with_time.begin(); it2 != puces_with_time.end(); ++it2 ) 
		{
			if( it->first == it2->first )
			{
				split_activity[split_activity.size()-1]->cut_activity(tmp_cut_activity);
				if(tmp_cut_activity.size()==0)
					cout << "ERROR" << endl;
				else
				{
					for(unsigned i=0; i<tmp_cut_activity.size(); ++i)
					{
						tmp_cut_activity[i]->remove_after_6();
						tmp_cut_activity[i]->finding_labels();
						if(tmp_cut_activity[i]->events[0]->get_unique_id() == 3024865)
							tmp_cut_activity[i]->print_activity();
						save_activity.push_back(new Activity(tmp_cut_activity[i])); // save les tmp_cut_activity
						
					}
				}	
				
			}
			destroy_vector(tmp_cut_activity); // mettre à zero tmp_cut_activity
		}
	}
	add_activity(split_activity, save_activity); // mettre tous les save activity dans split_activity
	destroy_vector(save_activity);
	
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

	// Who are the person(s) in the current activity ? + events attribution
	attributes_events();
	int first_person_id = first_person_entered();
	
	if(only_one_person)
	{
		first_person = true;
		if(puces_with_time.size()==1)
		{
			main_person = puces_with_time.begin()->first;
			pretreat_activity();
			
			cut_activity(split_activity);
			
			if(split_activity.size()==0)
				cout << "ERROR" << endl;
			else
			{
				for(unsigned i=0; i<split_activity.size(); ++i)
				{
					split_activity[i]->remove_after_6();
					split_activity[i]->finding_labels();
				}
			}			
		}
		else
		{
			
			for(auto it2 = puces_with_time.begin(); it2 != puces_with_time.end(); ++it2) 
			{
				if(it2->first != 0)
				{
					main_person = it2->first;
					pretreat_activity();
					cut_activity(split_activity);
					if(split_activity.size()==0)
						cout << "ERROR" << endl;
					else
					{
						for(unsigned i=0; i<split_activity.size(); ++i)
						{
							split_activity[i]->remove_after_6();
							split_activity[i]->finding_labels();
						}
					}
				}
			}
		}
		//print_activity();
	}
	else
		split_activities(split_activity, first_person_id);
}


/**
	* \name destroy_map_different_activities
	* \brief Release the allocated memory for the different_activities map
	* 
	* \param different_activities : the map to destroy.
*/
void Activity::destroy_map_different_activities(map<int, vector<Event*> >& different_activities)
{
	unsigned i;
	for(auto it = different_activities.begin(); it != different_activities.end(); ++it) 
		for(i=0; i < it->second.size(); ++i)
			it->second[i]->~Event();
}


bool Activity::is_correct()
{
	for(unsigned i=0; i<events.size(); ++i)
	{
		if(events[i]->get_id_puce() != 0)
			return true;
	}
	return false;
	
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
	if(events[0]->get_unique_id() == 3024865)
		cout << "INDEX OUT = " << index_out << endl;
	
	return index_out;
}


void Activity::finding_labels()
{	
	unsigned index_out = finding_in_out_inout();
	bool result;
	
	// inout
	if(index_out == 0)
	{
		result = finding_label_inout();
		if(!result)
			is_inout_abandon = true;
		else
			is_inout = true;
	}
	
	// in and out
	else
	{
		result = finding_label_in(index_out);
		if(!result)
			is_in_abandon = true;
		else
			is_in = true;
		result = finding_label_out(index_out);
		if(!result)
			is_out_abandon = true;
		else
			is_out = true;
	}
	
}

bool Activity::finding_label_in(unsigned index_ending)
{
	unsigned code_event;
	bool abandon_activity = false;
	
	for(unsigned num_event=0; num_event < index_ending; ++num_event)
	{
		code_event = events[num_event]->get_event();				
							
		if( events[num_event]->alarm_exist() && events[num_event]->get_attribution_alarm() == static_cast<int>(main_person) && alarm_index_in == -1 )
			alarm_index_in = num_event;
			
		else if( events[num_event]->sha_exist() )
		{
			if( events[num_event]->get_sha_person_id() > 0 )
			{
				if( code_event == CODE_SHA && SHA_index_in == -1)
					SHA_index_in = num_event;
				else if( code_event == CODE_SHA_DURING_ALARM && SHA_during_alarm_index_in == -1 )
					SHA_during_alarm_index_in = num_event;
				abandon_activity = false;
			}
			else
			{
				if( SHA_index_in == -1 && SHA_during_alarm_index_in == -1 )
					abandon_activity = true;
				else
					abandon_activity = false;
					
			}
		}
	}
	
	
	
	if( abandon_activity )
	{
		label_activity.push_back( ABANDON_IN );
		return false;
	}
	
	// Alarm 0, SHA taken 0, SHA taken during alarm 0
	if( alarm_index_in == -1 && SHA_index_in == -1 && SHA_during_alarm_index_in == -1 )
		label_activity.push_back( NOT_IN_NO_ALARM );
		
	// Alarm 0, SHA taken 0, SHA taken during alarm 1
	else if( alarm_index_in == -1 && SHA_index_in == -1 && SHA_during_alarm_index_in != -1 )
		label_activity.push_back( IN_DURING_ALARM );
		
	// Alarm 0, SHA taken 1, SHA taken during alarm 0
	else if( alarm_index_in == -1 && SHA_index_in != -1 && SHA_during_alarm_index_in == -1 )
		label_activity.push_back( IN_NO_ALARM );
		
	// Alarm 0, SHA taken 1, SHA taken during alarm 1
	else if( alarm_index_in == -1 && SHA_index_in != -1 && SHA_during_alarm_index_in != -1 )
	{
		if(SHA_index_in < SHA_during_alarm_index_in)
		{
			label_activity.push_back( ABANDON_IN );
			return false;
		}
		else
			label_activity.push_back( IN_DURING_ALARM );
	}
	
	// Alarm 1, SHA taken 0, SHA taken during alarm 0
	else if( alarm_index_in != -1 && SHA_index_in == -1 && SHA_during_alarm_index_in == -1 )
		label_activity.push_back( NOT_IN_ALARM );
		
	// Alarm 1, SHA taken 0, SHA taken during alarm 1
	else if( alarm_index_in != -1 && SHA_index_in == -1 && SHA_during_alarm_index_in != -1 )
	{
		if(alarm_index_in < SHA_during_alarm_index_in)
			label_activity.push_back( IN_DURING_ALARM );
		else
		{
			label_activity.push_back( ABANDON_IN );
			return false;
		}
	}
	
	// Alarm 1, SHA taken 1, SHA taken during alarm 0
	else if(alarm_index_in != -1 && SHA_index_in != -1 && SHA_during_alarm_index_in == -1  )
	{
		if(alarm_index_in < SHA_index_in)
			label_activity.push_back( IN_AFTER_ALARM );
		else
			label_activity.push_back( IN_NO_ALARM );
	}
	
	// Alarm 1, SHA taken 1, SHA taken during alarm 1
	else if( alarm_index_in != -1 && SHA_index_in != -1 && SHA_during_alarm_index_in != -1 )
	{
		label_activity.push_back( ABANDON_IN );
		return false;
	}
	
	else
	{
		label_activity.push_back( IMPOSSIBLE );
		return false;
	}
		
	return true;
}


bool Activity::finding_label_out(unsigned index_begining)
{
	unsigned code_event;
	bool abandon_activity = false;
	
	for(unsigned num_event=index_begining; num_event < events.size(); ++num_event)
	{
		code_event = events[num_event]->get_event();				
		
		if( events[num_event]->alarm_exist() && events[num_event]->get_attribution_alarm() == static_cast<int>(main_person) && alarm_index_out == -1 )
			alarm_index_out = num_event;
			
		else if( events[num_event]->sha_exist() )
		{
			if( events[num_event]->get_sha_person_id() > 0 )
			{
				if( code_event == CODE_SHA && SHA_index_out == -1)
					SHA_index_out = num_event;
				else if( code_event == CODE_SHA_DURING_ALARM && SHA_during_alarm_index_out == -1 )
					SHA_during_alarm_index_out = num_event;
				abandon_activity = false;
			}
			else
			{
				if( SHA_index_out == -1 && SHA_during_alarm_index_out == -1 )
					abandon_activity = true;
				else
					abandon_activity = false;
					
			}
		}
	}
	if( abandon_activity )
	{
		label_activity.push_back( ABANDON_OUT );
		return false;
	}
	
	// Alarm 0, SHA taken 0, SHA taken during alarm 0
	if( alarm_index_out == -1 && SHA_index_out == -1 && SHA_during_alarm_index_out == -1 )
		label_activity.push_back( NOT_OUT_NO_ALARM );
		
	// Alarm 0, SHA taken 0, SHA taken during alarm 1
	else if( alarm_index_out == -1 && SHA_index_out == -1 && SHA_during_alarm_index_out != -1 )
		label_activity.push_back( OUT_DURING_ALARM );
		
	// Alarm 0, SHA taken 1, SHA taken during alarm 0
	else if( alarm_index_out == -1 && SHA_index_out != -1 && SHA_during_alarm_index_out == -1 )
		label_activity.push_back( OUT_NO_ALARM );
		
	// Alarm 0, SHA taken 1, SHA taken during alarm 1
	else if( alarm_index_out == -1 && SHA_index_out != -1 && SHA_during_alarm_index_out != -1 )
	{
		if(SHA_index_out < SHA_during_alarm_index_out)
		{
			label_activity.push_back( ABANDON_OUT );
			return false;
		}
		else
			label_activity.push_back( OUT_DURING_ALARM );
	}
	
	// Alarm 1, SHA taken 0, SHA taken during alarm 0
	else if( alarm_index_out != -1 && SHA_index_out == -1 && SHA_during_alarm_index_out == -1 )
		label_activity.push_back( NOT_OUT_ALARM );
		
	// Alarm 1, SHA taken 0, SHA taken during alarm 1
	else if( alarm_index_out != -1 && SHA_index_out == -1 && SHA_during_alarm_index_out != -1 )
	{
		if(alarm_index_out < SHA_during_alarm_index_out)
			label_activity.push_back( OUT_DURING_ALARM );
		else
		{
			label_activity.push_back( ABANDON_OUT );
			return false;
		}
	}
	
	// Alarm 1, SHA taken 1, SHA taken during alarm 0
	else if(alarm_index_out != -1 && SHA_index_out != -1 && SHA_during_alarm_index_out == -1  )
	{
		if(alarm_index_out < SHA_index_out)
			label_activity.push_back( OUT_AFTER_ALARM );
		else
			label_activity.push_back( OUT_NO_ALARM );
	}
	
	// Alarm 1, SHA taken 1, SHA taken during alarm 1
	else if( alarm_index_out != -1 && SHA_index_out != -1 && SHA_during_alarm_index_out != -1 )
	{
		label_activity.push_back( ABANDON_OUT );
		return false;
	}
	
	else
	{
		label_activity.push_back( IMPOSSIBLE );
		return false;
	}
		
	return true;
	
}


bool Activity::finding_label_inout()
{
	unsigned code_event;
	bool abandon_activity = false;
	
	for(unsigned num_event=0; num_event < events.size(); ++num_event)
	{
		code_event = events[num_event]->get_event();				
						
		if( events[num_event]->alarm_exist() && events[num_event]->get_attribution_alarm() == static_cast<int>(main_person) && alarm_index_inout == -1 )
			alarm_index_inout = num_event;
			
			
		else if( events[num_event]->sha_exist() )
		{
			if( events[num_event]->get_sha_person_id() > 0 )
			{
				if( code_event == CODE_SHA && SHA_index_inout == -1)
					SHA_index_inout = num_event;
				else if( code_event == CODE_SHA_DURING_ALARM && SHA_during_alarm_index_inout == -1 )
					SHA_during_alarm_index_inout = num_event;
				abandon_activity = false;
			}
			else
			{
				if( SHA_index_inout == -1 && SHA_during_alarm_index_inout == -1 )
					abandon_activity = true;
				else
					abandon_activity = false;
					
			}
		}
	}
	
	if(events[0]->get_unique_id() == 3024865)
		cout << "\t\t\t" << alarm_index_inout << " " << SHA_index_inout << " " << SHA_during_alarm_index_inout << endl<< endl;	
	
	if( abandon_activity )
	{
		label_activity.push_back( ABANDON_INOUT );
		return false;
	}
	if(events[0]->get_unique_id() == 3024865)
		cout << "JE SUIS LA" << endl << endl;

	
	// Alarm 0, SHA taken 0, SHA taken during alarm 0
	if( alarm_index_inout == -1 && SHA_index_inout == -1 && SHA_during_alarm_index_inout == -1 ){
		
		label_activity.push_back( NOT_INOUT_NO_ALARM );
	}
		
	// Alarm 0, SHA taken 0, SHA taken during alarm 1
	else if( alarm_index_inout == -1 && SHA_index_inout == -1 && SHA_during_alarm_index_inout != -1 )
		label_activity.push_back( INOUT_DURING_ALARM );
		
	// Alarm 0, SHA taken 1, SHA taken during alarm 0
	else if( alarm_index_inout == -1 && SHA_index_inout != -1 && SHA_during_alarm_index_inout == -1 )
		label_activity.push_back( INOUT_NO_ALARM );
		
	// Alarm 0, SHA taken 1, SHA taken during alarm 1
	else if( alarm_index_inout == -1 && SHA_index_inout != -1 && SHA_during_alarm_index_inout != -1 )
	{
		if(SHA_index_inout < SHA_during_alarm_index_inout)
		{
			label_activity.push_back( ABANDON_INOUT );
			return false;
		}
		else
			label_activity.push_back( INOUT_DURING_ALARM );
	}
	
	// Alarm 1, SHA taken 0, SHA taken during alarm 0
	else if( alarm_index_inout != -1 && SHA_index_inout == -1 && SHA_during_alarm_index_inout == -1 )
		label_activity.push_back( NOT_INOUT_ALARM );
		
	// Alarm 1, SHA taken 0, SHA taken during alarm 1
	else if( alarm_index_inout != -1 && SHA_index_inout == -1 && SHA_during_alarm_index_inout != -1 )
	{
		if(alarm_index_inout < SHA_during_alarm_index_inout)
			label_activity.push_back( INOUT_DURING_ALARM );
		else
		{
			label_activity.push_back( ABANDON_INOUT );
			return false;
		}
	}
	
	// Alarm 1, SHA taken 1, SHA taken during alarm 0
	else if(alarm_index_inout != -1 && SHA_index_inout != -1 && SHA_during_alarm_index_inout == -1  )
	{
		if(alarm_index_inout < SHA_index_inout)
			label_activity.push_back( INOUT_AFTER_ALARM );
		else
			label_activity.push_back( INOUT_NO_ALARM );
	}
	
	// Alarm 1, SHA taken 1, SHA taken during alarm 1
	else if( alarm_index_inout != -1 && SHA_index_inout != -1 && SHA_during_alarm_index_inout != -1 )
	{
		label_activity.push_back( ABANDON_INOUT );
		return false;
	}
	
	else
	{
		label_activity.push_back( IMPOSSIBLE );
		return false;
	}
		
	return true;
}

