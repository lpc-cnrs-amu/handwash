#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "event.hpp"
#include "sha.hpp"

#define NB_LABELS 24
enum Label
{
	// SHA pris dans le in (sur)
	IN_NO_ALARM,
	IN_AFTER_ALARM,
	IN_DURING_ALARM,
	// SHA pris dans le out (sur)
	OUT_NO_ALARM,
	OUT_AFTER_ALARM,
	OUT_DURING_ALARM,	
	// SHA pris dans le inout (sur)
	INOUT_NO_ALARM,
	INOUT_AFTER_ALARM,
	INOUT_DURING_ALARM,	
	
	// SHA possiblement pris dans le in
	IN_POSSIBLE_NO_ALARM,
	IN_POSSIBLE_AFTER_ALARM,
	IN_POSSIBLE_DURING_ALARM,
	// SHA possiblement pris dans le out
	OUT_POSSIBLE_NO_ALARM,
	OUT_POSSIBLE_AFTER_ALARM,
	OUT_POSSIBLE_DURING_ALARM,
	// SHA possiblement pris dans le inout
	INOUT_POSSIBLE_NO_ALARM,
	INOUT_POSSIBLE_AFTER_ALARM,
	INOUT_POSSIBLE_DURING_ALARM,
	
	// SHA pas pris dans le in
	NOT_IN_NO_ALARM,
	NOT_IN_ALARM,
	// SHA pas pris dans le out
	NOT_OUT_NO_ALARM,
	NOT_OUT_ALARM,
	// SHA pas pris dans le inout
	NOT_INOUT_NO_ALARM,
	NOT_INOUT_ALARM
};


/**
 * \file activities.hpp
*/


/** 
 * \class Activity
 * \brief Class representing an instance 
 * from the hygiene csv file. An activity is a group of events. 
 * An activity is associated to a person. If there is more than n>1 person, 
 * then we split the activity into n activity.
*/
class Activity
{
	private:
		std::vector<Event*> events;
		std::vector<unsigned> persons;
		
		unsigned main_person;	
		bool inout = false; // true => the activity is a very short one, false => there is an in and an out
		
		bool theres_SHA_sure_in = false;
		bool theres_SHA_sure_out = false;
		bool theres_SHA_sure_inout = false;
		bool theres_SHA_possible_in = false;
		bool theres_SHA_possible_out = false;
		bool theres_SHA_possible_inout = false;
				
		bool first_person = false;
				
		std::vector<Label> label_activity;

		
		bool same_activity(Event* event);
		unsigned identify_different_puces(std::vector<unsigned>& different_puces, std::map<unsigned, std::vector<Sha*> >& puces_to_SHA, unsigned& first_person_id);
		
		void destroy_map_different_activities(std::map<unsigned, std::vector<Event*> >& different_activities);
		void destroy_map_puces_to_SHA(std::map<unsigned, std::vector<Sha*> >& puces_to_SHA);
		
		unsigned finding_in_out_inout();
		void finding_labels(std::vector<Sha*>& SHA);
		void finding_label_in(unsigned index_ending, std::vector<Sha*>& SHA);
		void finding_label_out(unsigned index_begining);
		void finding_label_inout();
		
	public:
		Activity();
		Activity(Event* event);
		Activity(std::vector<Event*>& vector_event, unsigned p, std::vector<unsigned>& different_persons);
		Activity(Activity* copy);  		
		~Activity();
		
		unsigned get_person();
		unsigned get_nb_persons();
		
		void activity_per_person(std::vector<Activity*>& split_activity);
		void write_file(std::ofstream& output);
		void print_activity();
		void append_event_to_activity(Event* event);
		bool check_and_append_event_to_activity(Event* event);
		
		/* A CHANGER */
		unsigned get_nb_SHA_sure_in();
		unsigned get_nb_SHA_sure_out();
		unsigned get_nb_SHA_possible_in();
		unsigned get_nb_SHA_possible_out();

		unsigned get_nb_SHA_sure_inout();
		unsigned get_nb_SHA_possible_inout();


		bool get_SHA_not_taken_in();
		bool get_SHA_not_taken_out();
		bool get_SHA_not_taken_inout();
		bool get_inout();
		bool get_theres_SHA_sure_in();
		bool get_theres_SHA_sure_out();
		bool get_theres_SHA_sure_inout();
		bool get_theres_SHA_possible_in ();
		bool get_theres_SHA_possible_out ();
		bool get_theres_SHA_possible_inout ();
};
	

#endif

