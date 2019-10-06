#include <algorithm>
#include <ctime>
#include "event.hpp"
#define SECOND_MAX 10

using namespace std;


const vector<Code> Event::correct_codes( 
	{CODE_OPEN_DOOR, CODE_CLOSE_DOOR, CODE_ALARM, CODE_SHA_DURING_ALARM,
	CODE_SHA, CODE_SHOE_IN, CODE_SHOE_OUT, CODE_INSERTION_BOTTLE_SHA,
	CODE_REMOVE_BOTTLE_SHA,	CODE_RESET_MACHINE,	CODE_INSERTION_USB_KEY,
	CODE_EXCEEDING_DOSE_NUMBER_SHA});

Event::Event(Event* event)
{
	this->unique_id = event->unique_id;
	this->id_event = event->id_event;
	this->in = event->in; 
	this->id_puce = event->id_puce;
	this->id_chamber = event->id_chamber;
	this->alarm = event->alarm;
	if(event->sha != NULL)
		this->sha = new Sha(event->sha);
	if(event->time_ != NULL)
		this->time_ = new Time(event->time_);
}

unsigned Event::get_id_puce() {	return id_puce; }
unsigned Event::get_unique_id() { return unique_id; }
unsigned Event::get_chamber() { return id_chamber; }
unsigned Event::get_event() { return id_event; }

unsigned Event::get_hour() { return time_->get_hour(); }
unsigned Event::get_minutes() { return time_->get_minutes(); }
unsigned Event::get_seconds() { return time_->get_seconds(); }

unsigned Event::get_year() { return time_->get_year(); }
unsigned Event::get_month() { return time_->get_month(); }
unsigned Event::get_day() { return time_->get_day(); }

string Event::get_time() { return time_->get_time(); }
string Event::get_date() { return time_->get_date(); }
void Event::split_date() { time_->split_date(); }
void Event::split_time() { time_->split_time(); }


bool Event::get_in() { return in; }

unsigned Event::get_code_sha() { return sha->get_code_sha(); }

void Event::set_in(bool in_or_out) { in = in_or_out; }

void Event::set_SHA(unsigned code_sha, int person_id, bool sure)
{
	if(sha == NULL)
		sha = new Sha(code_sha, person_id, sure);
	else
		sha->set_SHA(code_sha, person_id, sure);
}
void Event::set_alarm(int puce) { alarm = puce; }
bool Event::alarm_exist() { return alarm != -1; }
int Event::get_attribution_alarm() { return alarm; }

int Event::get_sha_person_id() 
{ 
	if( sha == NULL )
		return -2;
	return sha->get_person_id(); 
}
bool Event::sha_exist() { return sha != NULL; }
Time* Event::get_time_object() { return time_; }

bool Event::code_correct()
{
	return find(correct_codes.begin(), correct_codes.end(), id_event) != correct_codes.end();
}


int Event::ecart_time(Event* prec)
{
	return time_->ecart_time(prec->time_);
}
int Event::ecart_time(Time* prec)
{
	return time_->ecart_time(prec);
}

/** renvoie l'écart de temps en secondes entre l'event appelé et son precedent*/
/*
float Event::ecart_time(Event* prec, int unity)
{	
	unsigned difference_seconds = 0;
	unsigned difference_mins = 0;
	unsigned difference_hour = 0;
	
	unsigned sec = this->get_seconds();
	int min =  (int) this->get_minutes();
	int h =  (int) this->get_hour();
		
	if(h >= (int)prec->get_hour())
	{
		if(prec->get_seconds() > sec)
		{
			-- min;
			if( min == -1 )
				min = 0;
			sec += 60;
		}

		difference_seconds = sec - prec->get_seconds();
		if((int)prec->get_minutes() > min)
		{
			min += 60;
		}
		difference_mins = (min - prec->get_minutes()) * 60;
		
		return difference_mins + difference_seconds;
	}
	else
	{
		if(prec->get_seconds() > sec)
		{
			-- min;
			if( min == -1 )
				min = 0;
			sec += 60;
		}		
		
		difference_seconds = sec - prec->get_seconds();
		difference_mins = 60 - prec->get_minutes() + min -1;
		difference_hour = 24 - prec->get_hour() + h -1;

		return difference_seconds + difference_mins*60;

			
	}
	return -1;
}
*/


bool Event::is_sup_or_eq(Event* event_bis)
{
	return time_->is_sup_or_eq(event_bis->time_);
}
bool Event::is_inf_or_eq(Event* event_bis)
{
	return time_->is_inf_or_eq(event_bis->time_);
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
			time_ = new Time();
			pos_date = token.find(" ");
			time_->set_date(token.substr(0, pos_date));
			time_->split_date();
			token.erase(0, pos_date + 1);
			time_->set_time(token);
			time_->split_time();
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
		 << get_year() << "] month: ["
		 << get_month() << "] day: ["
		 << get_day() << "] hour: ["
		 << get_hour() << "] minutes: ["
		 << get_minutes() << "] seconds: ["
		 << get_seconds() << "] date: ["
		 << get_date() << "] time: ["
		 << get_time() << "]\n";
}

void Event::print_event(ofstream& output)
{
	output << "\tevent id: [" << unique_id << "]"
		 << " code event: [" << id_event << "] in: ["
		 << in << "] id_puce: ["
		 << id_puce << "] id_chamber: ["
		 << id_chamber << "] year: ["
		 << get_year() << "] month: ["
		 << get_month() << "] day: ["
		 << get_day() << "] hour: ["
		 << get_hour() << "] minutes: ["
		 << get_minutes() << "] seconds: ["
		 << get_seconds() << "] date: ["
		 << get_date() << "] time: ["
		 << get_time() << "]\n";
}

//Gives the last day of a month
unsigned Event::last_day_month()
{
	switch(get_month())
	{
		case 1:
			return 31;
			break;
		case 2:
			if(get_year()%4==0)
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
			cerr << "WARNING ! unidentified month : " << get_month() << endl;
			return 0;
			break;
	}
}


