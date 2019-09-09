#ifndef EVENT_HPP
#define EVENT_HPP
#include <string>
#include <fstream>
#include <iostream>
#include "sha.hpp"
#define IN true
#define OUT false

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
		unsigned year;
		unsigned month;	
		unsigned day;
		unsigned hour;
		unsigned minutes;
		unsigned seconds;
		std::string date;		// date like 2018-01-17
		std::string time;		// time like 16:29:02.100
		
		Sha* sha = NULL;
		int alarm = -1;
		
		void split_time();
		void split_date();
		
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
};
	

#endif
