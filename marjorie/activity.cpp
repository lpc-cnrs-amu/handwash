#include "activity.hpp"
#include <algorithm>
#include <map>
#define LAST_EVENT events.size()-1
#define MINUTE_MAX 5
#define CODE_SHA 8
#define SHA_SURE true
#define SHA_POSSIBLE false
#define CODE_OPEN_DOOR 5
#define CODE_CLOSE_DOOR 6
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
	this->label_activity = copy->label_activity;
	this->nb_SHA_sure = copy->nb_SHA_sure;
	this->nb_SHA_possible = copy->nb_SHA_possible;
			
	for(i=0; i < copy->events.size(); ++i)
		this->events.push_back( new Event(copy->events[i]) );
		
	for(i=0; i < copy->persons.size(); ++i)
		this->persons.push_back( copy->persons[i] );
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
	unsigned i;
	
	output << "PERSON: " << main_person << endl;
	output << "\tNUMBER OF PERSON: " << persons.size() << endl << "\t";
	
	for(i=0; i < persons.size(); ++i)
		output << persons[i] << " ";
	output << endl;
	
	output << "\tNUMBER SHA : " << nb_SHA_sure << endl;
	output << "\tNUMBER SHA POSSIBLE : " << nb_SHA_possible << endl;
	
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

void Activity::print_activity()
{
	unsigned i;
	
	cout << "PERSON: " << main_person << endl;
	cout << "\tNUMBER OF PERSON: " << persons.size() << endl << "\t";
	
	for(i=0; i < persons.size(); ++i)
		cout << persons[i] << " ";
	cout << endl;
	
	cout << "\tNUMBER SHA : " << nb_SHA_sure << endl;
	cout << "\tNUMBER SHA POSSIBLE : " << nb_SHA_possible << endl;
	
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

unsigned Activity::get_person()
{
	return main_person;
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










// L'idée est de séparer les personnes directement après avoir trouvé une activité 
// (avant de faire activities.push_back dans activities.cpp)





// On ne rajoute pas la puce 0
unsigned Activity::identify_different_puces(vector<unsigned>& different_puces, 
	map<unsigned, vector<bool> >& puces_to_SHA)
{
	unsigned puce;
	for(unsigned i=0; i<events.size(); ++i)
	{
		puce = events[i]->get_id_puce();
		
		if(puce==0)
		{
			if(events[i]->get_event() == CODE_SHA)
			{
				//accorder le SHA à different_puces[0]
				if(different_puces.size() == 1)
					puces_to_SHA[different_puces[0]].push_back( SHA_SURE );

				//accorder le SHA à toutes les different_puces
				else if(different_puces.size() > 1)
					for(unsigned k=0; k<different_puces.size(); ++k)
						puces_to_SHA[different_puces[k]].push_back( SHA_POSSIBLE );
			
			}
			continue;
		}
		if(std::find(different_puces.begin(), different_puces.end(), puce) == different_puces.end())
			different_puces.push_back(puce);
	}
	
	return different_puces.size();
}


void Activity::activity_per_person(vector<Activity*>& split_activity)
{
	unsigned person;
	
	for(unsigned i=0; i<split_activity.size(); ++i)
		split_activity[i]->~Activity();

	vector<unsigned> different_puces;
	map<unsigned, vector<bool> > puces_to_SHA;
	unsigned nb_different_puces = identify_different_puces(different_puces, puces_to_SHA);
	
	
	// if there is more than 1 person in 1 activity
	if(nb_different_puces > 1)
	{
		//correct_activity = (nb_different_puces <= nb_SHA);
		map<unsigned, vector<Event*> > different_activities; // key = person, value = vector of events

		for(unsigned i=0; i<events.size(); ++i)
		{
			person = events[i]->get_id_puce();
			
			if( person==0 )
			{
				//push dans toutes les keys
				for(unsigned k=0; k < different_puces.size(); ++k)
					different_activities[different_puces[k]].push_back( new Event(events[i]) );
			}
			else
				different_activities[person].push_back( new Event(events[i]) );
		}	
		
		for(auto it = different_activities.begin(); it != different_activities.end(); ++it) 
		{			
			split_activity.push_back( new Activity(it->second, it->first, different_puces) );
			for(auto it2 = puces_to_SHA.begin(); it2 != puces_to_SHA.end(); ++it2) 
			{
				if( it->first == it2->first )
					split_activity[split_activity.size()-1]->count_SHA(it2->second);
			}
		}
		
		
	}
	else
	{
		if(nb_different_puces == 1)
			main_person = different_puces[0];
		else
			main_person = 0;
			
		persons.push_back(main_person);
		count_SHA_and_deciding_in_or_out();
	}
		
}


void Activity::count_SHA_and_deciding_in_or_out()
{
	events[0]->set_in(true);
	unsigned event_out = 0;
	int ecart_in_seconds = 0;
	int ecart_max = 0;
	bool only_5_or_6 = true;
	
	for(unsigned i=0; i < events.size(); ++i)
	{
		if( events[i]->get_event() == CODE_SHA )
			++nb_SHA_sure;
		
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
		events[event_out]->set_in(OUT);
}


void Activity::count_SHA(vector<bool>& sha)
{
	for(unsigned i=0; i < sha.size(); ++i)
	{
		if(sha[i])
			++nb_SHA_sure;
		else
			++nb_SHA_possible;
	}
	
	
	events[0]->set_in(true);
	unsigned event_out = 0;
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
		events[event_out]->set_in(OUT);
}
