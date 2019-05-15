#include "activity.hpp"
#include <algorithm>
#include <map>
#define IN true
#define OUT false
#define LAST_EVENT events.size()-1

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
	this->label_activity = copy->label_activity;
	for(unsigned i=0; i < copy->events.size(); ++i)
		this->events.push_back( new Event(copy->events[i]) );
}

/**
	* \brief Activity Constructor.
	*
	* \param filename : file containing every instances in csv format.
*//*
Activity::Activity(vector<Event*>& vector_event, bool correct)
{
	correct_activity = correct;
	for(unsigned i=0; i<vector_event.size(); ++i)
		events.push_back( new Event(vector_event[i]) );
}*/
/*
Activity::Activity(Event* event, bool correct)
{
	correct_activity = correct;
	events.push_back( new Event(event) );
}*/

Activity::Activity(Event* event)
{
	events.push_back( new Event(event) );
}

void Activity::write_file(ofstream& output)
{
	for(unsigned i=0; i<events.size(); ++i)
	{
		output << "\t" 
			   << events[i]->get_event()   << " "
			   << events[i]->get_chamber() << " "
			   << events[i]->get_id_puce() << " "
			   << events[i]->get_date()    << " "
			   << events[i]->get_time()    << endl;
	}
}

void Activity::print_activity()
{
	for(unsigned i=0; i<events.size(); ++i)
		events[i]->print_event();
}


bool Activity::check_and_append_event_to_activity(Event* event)
{
	if( !same_activity(event) )
		return false;
		
	events.push_back( new Event(event) );
	return true;
}

void Activity::append_event_to_activity(Event* event)
{
	events.push_back( new Event(event) );
}





// Verifie si c'est le même horaire (return true si oui, false sinon)
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
			event->get_minutes() <= events[LAST_EVENT]->get_minutes()+5
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
					event->get_minutes() <= events[LAST_EVENT]->get_minutes()+5
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
					event->get_minutes() <= events[LAST_EVENT]->get_minutes()+5
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
			60 - events[LAST_EVENT]->get_minutes() + event->get_minutes() <= 5
		   )
			return true;
			
		else if( event->get_hour() == events[LAST_EVENT]->get_hour() && 
				event->get_minutes() <= events[LAST_EVENT]->get_minutes()+5 
			   )
			return true;
			
	}

	return false;
}












/*



// On ne rajoute pas la puce 0
unsigned Activity::identify_different_puces(unsigned num_activity, 
	vector<unsigned>& different_puces, unsigned& nb_SHA)
{
	unsigned puce;
	nb_SHA = 0;
	for(unsigned j=0; j<activities[num_activity].size(); ++j)
	{
		puce = activities[num_activity][j]->get_id_puce();
		if(puce==0)
		{
			if(activities[num_activity][j]->get_event() == 8)
				++nb_SHA;
			continue;
		}
		if(std::find(different_puces.begin(), different_puces.end(), puce) == different_puces.end())
			different_puces.push_back(puce);
	}
	
	return different_puces.size();
}

void Activity::activity_per_person()
{
	unsigned person, nb_SHA;
	bool correct_activity = true;
	
	// all activities
	for(unsigned i=0; i<activities.size(); ++i)
	{
		vector<unsigned> different_puces;
		unsigned nb_different_puces = identify_different_puces(i, different_puces, nb_SHA);
		
		// if there is more than 1 person in 1 activity
		if(nb_different_puces > 1)
		{
			correct_activity = (nb_different_puces <= nb_SHA);
				
			map<unsigned, vector<Event*> > different_activities;

			for(unsigned j=0; j<activities[i].size(); ++j)
			{
				person = activities[i][j]->get_id_puce();
				
				if( person==0 )
				{
					//push dans toutes les keys
					for(unsigned k=0; k < different_puces.size(); ++k)
						different_activities[different_puces[k]].push_back( activities[i][j] );
				}
				else
					different_activities[person].push_back( activities[i][j] );
			}	
			
			activities[i].clear();
			for(auto it = different_activities.begin(); it != different_activities.end(); ++it)
			   activities.push_back( it->second );
		}
	}
	
}



*/





