#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "event.hpp"

#define NB_LABELS

enum Label
{
	POSSIBLE_SHA, // SHA a peut etre été pris (impossible de savoir car plusieurs personnes dans la piece)
	
	SHA_IN_NO_OUT, //SHA pris dans le in, rien dans le out
	SHA_OUT_NO_IN, //SHA pris dans le out, rien dans le in
	SHA_ONLY_IN, //SHA pris dans une petite activité(que du in)
	SHA_IN_AND_OUT, // SHA pris dans le in, SHA pris dans le out
	
	SHA_IN_ALARM_NO_OUT, //SHA pris avec alarme dans le in, rien dans le out
	SHA_OUT_ALARM_NO_IN, //SHA pris avec alarme dans le out, rien dans le in
	SHA_ONLY_IN_ALARM, //SHA pris avec alarme dans une petite activité(que du in)
	SHA_IN_ALARM_AND_OUT,	//SHA pris avec alarme dans le in, SHA pris sans alarme dans le out
	SHA_IN_AND_OUT_ALARM, // SHA pris sans alarme dans le in, SHA pris avec alarme dans le out
	SHA_IN_ALARM_AND_OUT_ALARM, // SHA pris avec alarme dans le in, SHA pris avec alarme dans le out
	
	SHA_NO_IN_ALARM, //SHA pas pris dans le in alors qu'il y a eu l'alarme, 
	
};


/**
 * \file activities.hpp
*/


/** 
 * \class Activity
 * \brief Class representing an instance  
 * from the hygiene csv file. 
*/
class Activity
{
	private:
		std::vector<Event*> events;
		std::vector<unsigned> persons;
		
		unsigned main_person;
		unsigned nb_SHA_sure = 0;
		unsigned nb_SHA_possible = 0;
		
		Label label_activity = UNINDENTIFIED_WASH;

		
		
		bool same_activity(Event* event);
		unsigned identify_different_puces(std::vector<unsigned>& different_puces, std::map<unsigned, std::vector<bool> >& puces_to_SHA);
		void count_SHA(std::vector<bool>& sha);
		void count_SHA_and_deciding_in_or_out();
		
	public:
		Activity();
		Activity(Event* event);
		Activity(std::vector<Event*>& vector_event, unsigned p, std::vector<unsigned>& different_persons);
		Activity(Activity* copy);  		
		~Activity();
		
		unsigned get_person();
		
		void activity_per_person(std::vector<Activity*>& split_activity);
		void write_file(std::ofstream& output);
		void print_activity();
		void append_event_to_activity(Event* event);
		bool check_and_append_event_to_activity(Event* event);
};
	

#endif

