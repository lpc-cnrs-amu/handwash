#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "event.hpp"
#include "sha.hpp"

#define NB_LABELS 19
enum Label
{
	// SHA pris dans le in (sur)
	/** 0 */ IN_NO_ALARM,
	/** 1 */ IN_AFTER_ALARM,
	/** 2 */ IN_DURING_ALARM,
	// SHA pris dans le out (sur)
	/** 3 */ OUT_NO_ALARM,
	/** 4 */ OUT_AFTER_ALARM,
	/** 5 */ OUT_DURING_ALARM,	
	// SHA pris dans le inout (sur)
	/** 6 */ INOUT_NO_ALARM,
	/** 7 */ INOUT_AFTER_ALARM,
	/** 8 */ INOUT_DURING_ALARM,	
	
	// SHA pas pris dans le in
	/** 9 */ NOT_IN_NO_ALARM,
	/** 10 */ NOT_IN_ALARM,
	// SHA pas pris dans le out
	/** 11 */ NOT_OUT_NO_ALARM,
	/** 12 */ NOT_OUT_ALARM,
	// SHA pas pris dans le inout
	/** 13 */ NOT_INOUT_NO_ALARM,
	/** 14 */ NOT_INOUT_ALARM,
	
	// abandon de l'activité
	/** 15 */ ABANDON_IN,
	/** 16 */ ABANDON_OUT,
	/** 17 */ ABANDON_INOUT,
	
	// cas impossible
	/** 18 */ IMPOSSIBLE
};


/**
 * \file activity.hpp
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
		/* Attributes */
		std::vector<Event*> events;
		std::vector<Label> label_activity;
		std::map<int, unsigned> puces_with_time;
		
		Time* start_time = NULL;
		Time* end_time = NULL;
		int main_person; // the activity belongs to the main person
		bool is_in = false;
		bool is_out = false;
		bool is_inout = false;
		bool is_in_abandon = false;
		bool is_out_abandon = false;
		bool is_inout_abandon = false;
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
		
		std::string message_abandon_in = "valide";
		std::string message_abandon_out = "valide";
		std::string message_abandon_inout = "valide";

		/* Methods */
		void set_nb_persons(std::vector<Activity*>& split_activity);
		void add_activity(std::vector<Activity*>& destination, std::vector<Activity*>& send);
		void pretreat_activity();
		void remove_only_5_6();
		int same_activity		(Event* event);
		void finding_labels();
		bool finding_label_in	(unsigned index_ending);
		bool finding_label_out	(unsigned index_begining);
		bool finding_label_inout();
		
		int first_person_entered();
		int last_person();
		unsigned finding_in_out_inout();
		unsigned get_index_out();
		
		void attributes_unknown_alarm(bool only_one_person);
		void attributes_unknown_SHA(bool only_one_person);
		void attributes_SHA(int puce, unsigned num_event, bool only_one_person, 
			unsigned code_sha);
		void attributes_alarm(int puce, unsigned num_event, bool only_one_person);
		void attributes_events();
		void split_activities(std::vector<Activity*>& split_activity, 
			int first_person_id);
	
		void destroy_map_different_activities(std::map<int, std::vector<Event*> >& different_activities);
		void cut_activity(std::vector<Activity*>& split_activity);
		void cut_activity_bis(std::vector<Activity*>& split_activity,
			std::vector<Event*>& cumulative_events);
		void remove_after_6();

		
	public:
		Activity();
		Activity(Event* event);
		Activity(std::vector<Event*>& vector_event, int p, 
			std::map<int, unsigned>& puces_with_time_copy, bool one_person);
		Activity(Activity* copy);
		Activity(Activity* copy, std::vector<Event*>& vector_event);
		~Activity();
		
		
		void activity_per_person(std::vector<Activity*>& split_activity);
		void write_file(std::ofstream& output);
		void print_activity();
		void append_event_to_activity(Event* event);
		int check_and_append_event_to_activity(Event* event);
		
		Label get_label(unsigned num);
		unsigned get_nb_label();
		
		std::string get_message_abandon_in();
		std::string get_message_abandon_out();
		std::string get_message_abandon_inout();
		
		bool get_is_in();
		bool get_is_out();
		bool get_is_inout();
		
		bool is_abandon_inout();
		bool is_abandon_in();
		bool is_abandon_out();
		
		int get_person();
		unsigned get_chamber();
		std::string get_start_time(bool out = false);
		std::string get_end_time(bool in = false);
		int get_duration(unsigned in_out_inout = 0);
		
		Label get_label_inout();
		Label get_label_in();
		Label get_label_out();
		
		int get_alarm_index_in();
		int get_SHA_index_in();
		int get_SHA_during_alarm_index_in();
		
		int get_alarm_index_out();
		int get_SHA_index_out();
		int get_SHA_during_alarm_index_out();
		
		int get_alarm_index_inout();
		int get_SHA_index_inout();
		int get_SHA_during_alarm_index_inout();	
		
		bool is_alone();
		bool is_correct();
		
		unsigned set_start_time();
		unsigned set_end_time();
		
		void clear_label();
		void set_label(Label label);
		void set_message_abandon_in(std::string message);
		void set_message_abandon_out(std::string message);
		void set_message_abandon_inout(std::string message);
		
		bool is_start_time_inf(Activity* act);
		bool is_end_time_inf(Activity* act);
		bool is_start_time_inf_end_time(Activity* act);
		
		std::string get_start_time_date();
		std::string get_start_time_time();
		void set_is_in(bool set);
		void set_is_abandon_in(bool set);
		void set_is_out(bool set);
		void set_is_abandon_out(bool set);
		void set_is_inout(bool set);
		void set_is_abandon_inout(bool set);
		

		bool is_SHA_30_sec_in();
		bool is_SHA_30_sec_out();
		bool is_SHA_30_sec_inout__in();
		bool is_SHA_30_sec_inout__out();
};
	

#endif
