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
	//this->label_activity = copy->label_activity;

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




unsigned Activity::get_nb_SHA_sure_in() { return nb_SHA_sure_in; }
unsigned Activity::get_nb_SHA_sure_out() { return nb_SHA_sure_out; }
unsigned Activity::get_nb_SHA_possible_in() { return nb_SHA_possible_in; }
unsigned Activity::get_nb_SHA_possible_out() { return nb_SHA_possible_out; }

unsigned Activity::get_nb_SHA_sure_inout() { return nb_SHA_sure_inout; }
unsigned Activity::get_nb_SHA_possible_inout() { return nb_SHA_possible_inout; }


bool Activity::get_SHA_not_taken_in() { return SHA_not_taken_in; }
bool Activity::get_SHA_not_taken_out() { return SHA_not_taken_out; }
bool Activity::get_SHA_not_taken_inout() { return SHA_not_taken_inout; }






void Activity::write_file(ofstream& output)
{
	unsigned i;
	
	output << "PERSON: " << main_person << endl;
	output << "\tNUMBER OF PERSON: " << persons.size() << endl << "\t";
	
	for(i=0; i < persons.size(); ++i)
		output << persons[i] << " ";
	output << endl;
	
	/*output << "\tNUMBER SHA : " << nb_SHA_sure << endl;
	output << "\tNUMBER SHA POSSIBLE : " << nb_SHA_possible << endl;*/

	
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
		
		if(puce==0)
			continue;
		
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
	split_activity.clear();

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










// il n'y a pas de SHA possible quand il y a 1 seule personne dans la chambre
// (que des SHA surs)
void Activity::count_SHA_and_deciding_in_or_out()
{
	events[0]->set_in(true);
	unsigned event_out = 0;
	unsigned index_out = 0;
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
	{
		index_out = event_out;
		events[event_out]->set_in(OUT);
	}
	
	inout = false;
	if(index_out == 0)
		inout = true;
		
	if(inout)
		nb_SHA_sure_inout = nb_SHA_sure;
	else
		count_SHA_in_and_out(index_out);
		
	set_SHA_not_taken();
}


void Activity::count_SHA(vector<bool>& sha)
{
	// Count number of SHA sure and SHA possible
	count_SHA_sure_and_possible(sha);
	
	// Search where is the out
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
	
	// number of SHA sure/possible in : inout
	if(inout)
	{
		nb_SHA_possible_inout = nb_SHA_possible;
		nb_SHA_sure_inout = nb_SHA_sure;
	}
	// number of SHA sure/possible in : in and out
	else
		count_SHA_in_and_out(index_out);
		
	set_SHA_not_taken();
}


// Count number of SHA sure/possible 
void Activity::count_SHA_sure_and_possible(vector<bool>& sha)
{
	for(unsigned i=0; i < sha.size(); ++i)
	{
		if(sha[i])
			++nb_SHA_sure;
		else
			++nb_SHA_possible;
	}
}


// Count number of SHA sure/possible in : in, out and inout
void Activity::count_SHA_in_and_out(unsigned index_out)
{
	bool out=false;
	unsigned n_sha = 0;
	unsigned id_e;
	for(unsigned i=0; i < events.size(); ++i)
	{
		if( i!=0 && i == index_out )
		{
			n_sha = 0;
			out=true;
		}
		
		id_e = events[i]->get_event();
		
		// Prise du SHA
		if( id_e == CODE_SHA || id_e == CODE_SHA_DURING_ALARM )
		{
			++n_sha;
			
			//c'est un SHA possible
			if( n_sha > nb_SHA_sure )
			{
				if(!out)
					++ nb_SHA_possible_in;
				else
					++ nb_SHA_possible_out;
			}
			//c'est un SHA sure
			else
			{
				if(!out)
					++ nb_SHA_sure_in;
				else
					++ nb_SHA_sure_out;			
			}
		}
	}	
}


void Activity::set_SHA_not_taken()
{
	if(inout)
	{
		if( nb_SHA_sure_inout == 0 && nb_SHA_possible_inout == 0 )
			SHA_not_taken_inout = true;
	}
	else
	{
		if( nb_SHA_sure_in == 0 && nb_SHA_possible_in == 0 )
			SHA_not_taken_in = true;
		if( nb_SHA_sure_out == 0 && nb_SHA_possible_out == 0 )
			SHA_not_taken_out = true;
	}
}






/** ANALYSES PLUS POUSSEES ET PLUS COMPLETES */
/** ================================================================================

void Activity::give_labels()
{
	unsigned id_e;
	bool is_in = true;
	bool only_in = false;
	vector<unsigned> index_SHA_in;
	vector<unsigned> index_alarm_in;
	vector<unsigned> index_SHA_out;
	vector<unsigned> index_alarm_out;
	
	vector<unsigned> index_SHA_during_alarm_in;
	vector<unsigned> index_SHA_during_alarm_out;
		
	for(unsigned i=0; i < events.size(); ++i)
	{
		id_e = events[i]->get_event();
		if( !events[i]->get_in() )
			is_in = false;
		
		if(is_in)
		{
			if( id_e == CODE_ALARM )
				index_alarm_in.push_back(i);
			else if( id_e == CODE_SHA )
				index_SHA_in.push_back(i);
			else if( id_e == CODE_SHA_DURING_ALARM )
				index_SHA_during_alarm_in.push_back(i);
		}
		else
		{
			if( id_e == CODE_ALARM )
				index_alarm_out.push_back(i);
			else if( id_e == CODE_SHA )
				index_SHA_out.push_back(i);		
			else if( id_e == CODE_SHA_DURING_ALARM )
				index_SHA_during_alarm_out.push_back(i);				
		}
	
	}
	if( is_in )
		only_in = true;
	
	
	if(only_in)
		analyse_only_in(index_SHA_in, index_alarm_in, index_SHA_during_alarm_in);
	else
		analyse_activity(index_SHA_in, index_alarm_in, index_SHA_out, index_alarm_out, only_in);
	
}




void Activity::analyse_activity(vector<unsigned>& index_SHA_in,
	vector<unsigned>& index_alarm_in, vector<unsigned>& index_SHA_out,
	vector<unsigned>& index_alarm_out, bool only_in)
{

}


// Analyse les petites activités (on considère : entrée = sortie).
void Activity::analyse_only_in(
	vector<unsigned>& index_SHA_in, 
	vector<unsigned>& index_alarm_in, 
	vector<unsigned>& index_SHA_during_alarm_in)
{
	

	//Le SHA n’a pas été pris
	if( index_alarm_in.empty() && index_SHA_in.empty() )
		label_activity.push_back( SHA_NO_ONLY_IN ); 	
	
	//Le SHA a été pris
	else if( index_alarm_in.empty() && !index_SHA_in.empty() )
		for(unsigned i=0; i<index_SHA_in.size(); ++i)
			label_activity.push_back( SHA_ONLY_IN ); 
	
	//Le SHA n'a pas été pris avec l'alarme
	else if( !index_alarm_in.empty() && index_SHA_in.empty() )
		label_activity.push_back( SHA_NO_ONLY_IN_ALARM );

	//Le SHA a été pris pendant l'alarme
	else if( index_alarm_in.empty() && index_SHA_in.empty() && !index_SHA_during_alarm_in.empty())
		for(unsigned i=0; i < index_SHA_during_alarm_in.size(); ++i)
			label_activity.push_back( SHA_DURING_ONLY_IN );
	
	
	
	
	//Le SHA a été pris avec l’alarme
	//else if( !index_alarm_in.empty() && !index_SHA_in.empty() )
	//{
		//for(unsigned i=0; i < index_SHA_in.size(); ++i)
		//{
			//for(unsigned j=0; j < index_alarm_in.size(); ++j)
			//{
			//	if( index_SHA_in[i] < index_alarm_in[j] ) // Si on a pris le SHA avant l'alarme
			//}
		//}
	//}

		
	
	else
		label_activity.push_back( UNUSUAL );
}


======================================================================================
*/



