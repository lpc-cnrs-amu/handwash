#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "event.hpp"

enum Label
{
	UNINDENTIFIED_WASH, /** we don't know who washed their hands (several persons in the room) */
	
			//WASH HANDS
		//wash hands without alarm
	WASH_INOUT, /** very short activity, wash their hands once */
	WASH_IN_AND_OUT, /** wash their hands when entering the room and when exiting the room */
	WASH_IN, /** wash their hands only when entering the room */
	WASH_OUT, /** wash their hands only when exiting the room */

		//wash hands after the alarm beeped
	WASH_INOUT_ALARM, /** very short activity, wash their hands once */
	WASH_IN_AND_OUT_ALARM, /** wash their hands when entering the room and when exiting the room */
	WASH_IN_ALARM, /** wash their hands only when entering the room */
	WASH_OUT_ALARM /** wash their hands only when exiting the room */	
	
			//NOT WASH HANDS
		//not wash
		
		//not wash after the alarm beeped
	
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

