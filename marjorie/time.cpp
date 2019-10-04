#include "time.hpp"
#include <ctime>

using namespace std;
		
Time::Time() {}		
		
Time::Time(unsigned y, unsigned m, unsigned d, unsigned h, 
	unsigned min, unsigned s, string da, string t) : year(y), month(m), 
	day(d), hour(h), minutes(min), seconds(s), date(da), time_(t)
{
}

Time::Time(Time* copy)
{
	this->year = copy->year;
	this->month = copy->month;
	this->day = copy->day;
	this->hour = copy->hour;
	this->minutes = copy->minutes;
	this->seconds = copy->seconds;
	this->date = copy->date;
	this->time_ = copy->time_;
}


Time::~Time(){}

unsigned Time::get_hour() { return hour; }
unsigned Time::get_minutes() { return minutes; }
unsigned Time::get_seconds() { return seconds; }

unsigned Time::get_year() { return year; }
unsigned Time::get_month() { return month; }
unsigned Time::get_day() { return day; }

string Time::get_time() { return time_; }
string Time::get_date() { return date; }

void Time::set_date(string d) { date = d; }
void Time::set_time(string t) { time_ = t; }


void Time::split_date()
{
	string token;
	string date_tmp = date;
	string delimiter = "-";
	size_t pos = 0;
	unsigned cpt = 0;
	while( cpt < 3 )
	{
		if(cpt != 2)
			pos = date_tmp.find(delimiter);
		else
			pos =  std::string::npos ;
			
		token = date_tmp.substr(0, pos);
		if(cpt==0)
			year = stoi(token);
		else if(cpt==1)
			month = stoi(token);
		else if(cpt==2)
			day = stoi(token);
		++cpt;
		date_tmp.erase(0, pos + delimiter.length());
	}
}

void Time::split_time()
{
	string token;
	string time_tmp = time_;
	string delimiter = ":";
	size_t pos = 0;
	unsigned cpt = 0;
	while( cpt < 3 )
	{
		if(cpt != 2)
			pos = time_tmp.find(delimiter);
		else
			pos =  std::string::npos ;
		
		token = time_tmp.substr(0, pos);
		if(cpt==0)
			hour = stoi(token);
		else if(cpt==1)
			minutes = stoi(token);
		else if(cpt==2)
			seconds = stoi(token);
		++cpt;
		time_tmp.erase(0, pos + delimiter.length());
	}
}


int Time::ecart_time(Time* prec)
{
	struct tm prec_timeinfo;
	struct tm actual_timeinfo;
	
	strptime( (prec->date + prec->time_).c_str(), "%Y-%m-%d %H:%M:%S", &prec_timeinfo);
	strptime( (date + time_).c_str(), "%Y-%m-%d %H:%M:%S", &actual_timeinfo);
	prec_timeinfo.tm_isdst = -1;
	actual_timeinfo.tm_isdst = -1;

	return difftime(mktime ( &actual_timeinfo ), mktime ( &prec_timeinfo ));
}

bool Time::is_sup_or_eq(Time* event_bis)
{
	if(year > event_bis->year)
		return true;
	else if(year < event_bis->year)
		return false;
		
	if(month > event_bis->month)
		return true;
	else if(month < event_bis->month)
		return false;
		
	if(day > event_bis->day)
		return true;	
	else if(day < event_bis->day)
		return false;
		
	if(hour > event_bis->hour)
		return true;	
	else if(hour < event_bis->hour)
		return false;	
		
	if(minutes > event_bis->minutes)
		return true;	
	else if(minutes < event_bis->minutes)
		return false;	
		
	if(seconds >= event_bis->seconds)
		return true;	
	return false;
}
bool Time::is_inf_or_eq(Time* event_bis)
{
	if(year > event_bis->year)
		return false;
	else if(year < event_bis->year)
		return true;
		
	if(month > event_bis->month)
		return false;
	else if(month < event_bis->month)
		return true;
		
	if(day > event_bis->day)
		return false;	
	else if(day < event_bis->day)
		return true;
		
	if(hour > event_bis->hour)
		return false;	
	else if(hour < event_bis->hour)
		return true;	
		
	if(minutes > event_bis->minutes)
		return false;	
	else if(minutes < event_bis->minutes)
		return true;	
		
	if(seconds > event_bis->seconds)
		return false;	
	return true;
}

/*
unsigned Time::ecart_time(Time* time_prec)
{
	unsigned difference_seconds = 0;
	unsigned difference_mins = 0;
	
	unsigned sec = this->seconds;
	int min =  (int) this->minutes;
	int h =  (int) this->hour;
		
	if(h >= (int)time_prec->hour)
	{
		if(time_prec->seconds > sec)
		{
			-- min;
			if( min == -1 )
				min = 0;
			sec += 60;
		}

		difference_seconds = sec - time_prec->seconds;
		if((int)time_prec->minutes > min)
		{
			min += 60;
		}
		difference_mins = (min - time_prec->minutes) * 60;
		
		return difference_mins + difference_seconds;
	}
	else
	{
		if(time_prec->seconds > sec)
		{
			-- min;
			if( min == -1 )
				min = 0;
			sec += 60;
		}		
		
		difference_seconds = sec - time_prec->seconds;
		difference_mins = 60 - time_prec->minutes + min -1;
		
		return difference_seconds + difference_mins*60;
	}
	return -1;	
}
*/
