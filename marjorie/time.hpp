#ifndef TIME_HPP
#define TIME_HPP
#include <string>
#include <fstream>
#include <iostream>

class Time
{
	private:
		unsigned year;
		unsigned month;	
		unsigned day;
		unsigned hour;
		unsigned minutes;
		unsigned seconds;
		std::string date;		// date like 2018-01-17
		std::string time_;		// time like 16:29:02.000
	public:
		Time(unsigned y, unsigned m, unsigned d, unsigned h, 
			unsigned min, unsigned s, std::string da, std::string t);
		Time(Time* copy);
		Time();
		~Time();
		void split_time();
		void split_date();

		unsigned get_hour();
		unsigned get_minutes();
		unsigned get_seconds();

		unsigned get_year();
		unsigned get_month();
		unsigned get_day();

		std::string get_time();
		std::string get_date();
		
		void set_date(std::string d);
		void set_time(std::string t);
		int ecart_time(Time* prec);
		bool is_sup_or_eq(Time* event_bis);
		bool is_inf_or_eq(Time* event_bis);
};

#endif
