#ifndef EVENT_HPP
#define EVENT_HPP
#include <string>

/**
 * \file event.hpp
*/


/** 
 * \class Event
 * \brief Class representing an event  
 * from the hygiene csv file. 
*/
class Event
{
	private:
		unsigned id_event; 
		bool in; // in(true) => vient de rentrer, in(false) => va sortir
		unsigned id_puce;
		unsigned id_chamber;
		unsigned year;
		unsigned month;
		unsigned day;
		unsigned hour;
		unsigned minutes;
		unsigned seconds;
		std::string date;
		std::string time;
		
		void split_time();
		void split_date();
		
	public:
		Event(unsigned id, unsigned puce, unsigned chamber, std::string d, std::string h, bool in_or_out);
		Event(Event* event);
		Event(std::string line, bool excel_csv);
		
		void print_event();
		unsigned last_day_month();

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
};
	

#endif
