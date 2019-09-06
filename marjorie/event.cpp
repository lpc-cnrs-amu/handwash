
#include "event.hpp"
#define SECOND_MAX 10

using namespace std;


Event::Event(Event* event)
{
	this->unique_id = event->unique_id;
	this->id_event = event->id_event;
	this->in = event->in; 
	this->id_puce = event->id_puce;
	this->id_chamber = event->id_chamber;
	this->year = event->year;
	this->month = event->month;
	this->day = event->day;
	this->hour = event->hour;
	this->minutes = event->minutes;
	this->seconds = event->seconds;
	this->date = event->date;
	this->time = event->time;
}

unsigned Event::get_id_puce() {	return id_puce; }
unsigned Event::get_unique_id() { return unique_id; }
unsigned Event::get_chamber() { return id_chamber; }
unsigned Event::get_event() { return id_event; }

unsigned Event::get_hour() { return hour; }
unsigned Event::get_minutes() { return minutes; }
unsigned Event::get_seconds() { return seconds; }

unsigned Event::get_year() { return year; }
unsigned Event::get_month() { return month; }
unsigned Event::get_day() { return day; }

string Event::get_time() { return time; }
string Event::get_date() { return date; }

bool Event::get_in() { return in; }

unsigned Event::get_code_sha() { return sha->get_code_sha(); }

void Event::set_in(bool in_or_out) { in = in_or_out; }

void Event::set_SHA(unsigned person_id, bool sure)
{
	if(sha == NULL)
		sha = new Sha(person_id, sure)
	else
		sha->set_SHA(person_id, sure)
}
void Event::set_alarm(unsigned puce) { alarm = puce; }
bool Event::alarm_exist() { return alarm != -1; }
int Event::get_attribution_alarm() { return alarm; }

int Event::get_sha_person_id() 
{ 
	if( sha == NULL )
		return -2;
	return sha->get_person_id(); 
}
bool Event::sha_exist() { return sha != NULL; }


/** renvoie l'écart de temps en secondes entre l'event appelé et son precedent*/
int Event::ecart_time(Event* prec)
{	
	unsigned difference_seconds = 0;
	unsigned difference_mins = 0;
	
	unsigned sec = this->seconds;
	int min =  (int) this->minutes;
	int h =  (int) this->hour;
		
	if(h >= (int)prec->hour)
	{
		if(prec->seconds > sec)
		{
			-- min;
			if( min == -1 )
				min = 0;
			sec += 60;
		}

		difference_seconds = sec - prec->seconds;
		if((int)prec->minutes > min)
		{
			min += 60;
		}
		difference_mins = (min - prec->minutes) * 60;
		
		return difference_mins + difference_seconds;
	}
	else
	{
		if(prec->seconds > sec)
		{
			-- min;
			if( min == -1 )
				min = 0;
			sec += 60;
		}		
		
		difference_seconds = sec - prec->seconds;
		difference_mins = 60 - prec->minutes + min -1;
		
		return difference_seconds + difference_mins;
	}
	return -1;
}







Event::Event(string line, bool excel_csv)
{
	string token;
	string delimiter = ",";
	if(excel_csv)
		delimiter = ";";
	size_t pos = 0;
	size_t pos_date = 0;
	unsigned cpt=0;
	
	while (cpt < 7 && (pos = line.find(delimiter)) != std::string::npos) 
	{
		token = line.substr(0, pos);
		
		// Remove "" (first and last letter in token)
		if(token[0]=='"' && token[token.length()-1]=='"')
			token = token.substr(1, token.length() - 2);
		
		if(cpt==0)
			unique_id = stoi( token );
			
		else if(cpt==1)
			id_puce = stoi( token );
		
		else if(cpt==5)
			id_chamber = stoi( token );
		
		else if(cpt==6)
			id_event = stoi( token );
		
		else if(cpt==3)
		{
			pos_date = token.find(" ");
			date = token.substr(0, pos_date);
			split_date();
			token.erase(0, pos_date + 1);
			time = token;
			split_time();
		}
		
		
		line.erase(0, pos + delimiter.length());
		++cpt;
	}
	
	//print_event();
}

void Event::print_event()
{
	cout << "event id: [" << unique_id << "]"
		 << " code event: [" << id_event << "] in: ["
		 << in << "] id_puce: ["
		 << id_puce << "] id_chamber: ["
		 << id_chamber << "] year: ["
		 << year << "] month: ["
		 << month << "] day: ["
		 << day << "] hour: ["
		 << hour << "] minutes: ["
		 << minutes << "] seconds: ["
		 << seconds << "] date: ["
		 << date << "] time: ["
		 << time << "]\n";
}

void Event::print_event(ofstream& output)
{
	output << "\tevent id: [" << unique_id << "]"
		 << " code event: [" << id_event << "] in: ["
		 << in << "] id_puce: ["
		 << id_puce << "] id_chamber: ["
		 << id_chamber << "] year: ["
		 << year << "] month: ["
		 << month << "] day: ["
		 << day << "] hour: ["
		 << hour << "] minutes: ["
		 << minutes << "] seconds: ["
		 << seconds << "] date: ["
		 << date << "] time: ["
		 << time << "]\n";
}



void Event::split_date()
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

void Event::split_time()
{
	string token;
	string time_tmp = time;
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

//Gives the last day of a month
unsigned Event::last_day_month()
{
	switch(month)
	{
		case 1:
			return 31;
			break;
		case 2:
			if(year%4==0)
				return 29;
			return 28;
			break;		
		case 3:
			return 31;
			break;
		case 4:
			return 30;
			break;
		case 5:
			return 31;
			break;
		case 6:
			return 30;
			break;
		case 7:
			return 31;
			break;
		case 8:
			return 31;
			break;
		case 9:
			return 30;
			break;
		case 10:
			return 31;
			break;
		case 11:
			return 30;
			break;
		case 12:
			return 31;
			break;
		default:
			cerr << "WARNING ! unidentified month : " << month << endl;
			return 0;
			break;
	}
}


