#ifndef EVENT_HPP
#define EVENT_HPP
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "sha.hpp"
#include "time.hpp"
#define IN true
#define OUT false

enum Code
{
	CODE_SHOE_IN = 1,
	CODE_SHOE_OUT = 2,
	CODE_INSERTION_BOTTLE_SHA = 3,
	CODE_REMOVE_BOTTLE_SHA = 4,
	CODE_OPEN_DOOR = 5,
	CODE_CLOSE_DOOR = 6,
	CODE_ALARM = 7,
	CODE_SHA = 8,
	CODE_SHA_DURING_ALARM = 10,
	CODE_RESET_MACHINE = 15,
	CODE_INSERTION_USB_KEY = 16,
	CODE_EXCEEDING_DOSE_NUMBER_SHA = 37	
};



/**
 * \file event.hpp
*/


/** 
 * \class Event
 * \brief Class representing an event 
 * from the hygiene csv file (a line in the file). 
*/
class Event
{
	private:
		unsigned unique_id; 	// id for the line
		unsigned id_event;  	// id for the event corresponding to a code event (8 = SHA, 5 = door open, etc)
		bool in = true; 		// is the event in the "in" section or the "out" section ?
		unsigned id_puce;		// id of the puce (representing a person)
		unsigned id_chamber;	// id of the chamber
		Time* time_ = NULL;
		
		Sha* sha = NULL;
		int alarm = -1;
		
		static const std::vector<Code> correct_codes;
		
		void split_date();
		void split_time();

	public:
		Event(Event* event);
		Event(std::string line, bool excel_csv);
		
		void print_event();
		void print_event(std::ofstream& output);
		unsigned last_day_month();
		int ecart_time(Event* prec);
		
		void set_in(bool in_or_out);
	
		bool get_in();
		unsigned get_unique_id();
		unsigned get_id_puce();
		unsigned get_chamber();
		unsigned get_event();

		unsigned get_hour();
		unsigned get_minutes();
		unsigned get_seconds();

		unsigned get_year();
		unsigned get_month();
		unsigned get_day();

		std::string get_time();
		std::string get_date();
		
		void set_alarm(int puce);
		void set_SHA(unsigned code_sha, int person_id, bool sure);
		bool alarm_exist();
		int get_attribution_alarm();

		int get_sha_person_id();
		bool sha_exist();
		unsigned get_code_sha();
		Time* get_time_object();
		bool code_correct();
		bool is_sup_or_eq(Event* event_bis);
		bool is_inf_or_eq(Event* event_bis);
};
	

#endif
