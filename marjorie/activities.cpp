#include "activities.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <map>

using namespace std;

string label_to_str(Label label)
{
	switch(label)
	{
		case IN_NO_ALARM :
			return "IN_NO_ALARM";
			break;
		case IN_AFTER_ALARM:
			return "IN_AFTER_ALARM";
			break;
		case IN_DURING_ALARM:
			return "IN_DURING_ALARM";
			break;
		case OUT_NO_ALARM:
			return "OUT_NO_ALARM";
			break;
		case OUT_AFTER_ALARM:
			return "OUT_AFTER_ALARM";
			break;
		case OUT_DURING_ALARM:
			return "OUT_DURING_ALARM";
			break;	
		case INOUT_NO_ALARM:
			return "INOUT_NO_ALARM";
			break;
		case INOUT_AFTER_ALARM:
			return "INOUT_AFTER_ALARM";
			break;
		case INOUT_DURING_ALARM:
			return "INOUT_DURING_ALARM";
			break;	
		case NOT_IN_NO_ALARM:
			return "NOT_IN_NO_ALARM";
			break;
		case NOT_IN_ALARM:
			return "NOT_IN_ALARM";
			break;
		case NOT_OUT_NO_ALARM:
			return "NOT_OUT_NO_ALARM";
			break;
		case NOT_OUT_ALARM:
			return "NOT_OUT_ALARM";
			break;
		case NOT_INOUT_NO_ALARM:
			return "NOT_INOUT_NO_ALARM";
			break;
		case NOT_INOUT_ALARM:
			return "NOT_INOUT_ALARM";
			break;
		case ABANDON_IN:
			return "ABANDON_IN";
			break;
		case ABANDON_OUT:
			return "ABANDON_OUT";
			break;
		case ABANDON_INOUT:
			return "ABANDON_INOUT";
			break;
		case ABANDON:
			return "ABANDON";
			break;
		case IMPOSSIBLE:
			return "IMPOSSIBLE";
			break;
		default:
			return "NOT A LABEL";
			break;
	}	
}

Activities::~Activities()
{
	for(unsigned i=0; i<activities.size(); ++i)
	{
		activities[i]->~Activity();
		activities[i] = NULL;
	}
	activities.clear();
	cout << "Destroying all activities... " << endl;
}

unsigned Activities::get_nb_activities() { return activities.size(); }
int Activities::get_person(unsigned num_activity) { return activities[num_activity]->get_person(); }

/**
	* \brief Activity Constructor.
	*
	* \param filename : file containing every instances in csv format.
*/
Activities::Activities(char* filename, bool excel_csv)
{
	ifstream database(filename, ios::in);
	if(!database)
	{ 
		cerr << "Impossible to open the file " << filename << endl;
		exit(EXIT_FAILURE);
	}
	
	string line;
	int append_activity = 1;
	vector<Activity*> split_activity; 
	Activity* activity_tmp = new Activity();
	unsigned cpt_line = 0;
	
	while(std::getline(database, line))
	{
		// skip the header
		++cpt_line;
		if(cpt_line==1)
			continue;
			
		// add to the current activity if the event is in the current activity
		append_activity = activity_tmp->check_and_append_event_to_activity( new Event(line, excel_csv) );
		
		// ignore the event
		if(append_activity == -1)
			continue;
		
		// The event is in another activity
		if(append_activity == 0)
		{
			activity_tmp->activity_per_person(split_activity); 
			
			if(split_activity.size()==0)
				cout << "ERROR" << endl;
			else
			{
				for(unsigned nb_activities=0; nb_activities < split_activity.size(); ++nb_activities)
				{
					if(split_activity[nb_activities]->is_correct() && split_activity[nb_activities]->get_person() != 0)
						activities.push_back( new Activity(split_activity[nb_activities]) );
				}
			}
			
			
			activity_tmp->~Activity();
			activity_tmp = new Activity( new Event(line, excel_csv) );
		}
	}

	activity_tmp->activity_per_person(split_activity);
	if(split_activity.size()==0)
		cout << "ERROR" << endl;
	else
	{
		for(unsigned nb_activities=0; nb_activities < split_activity.size(); ++nb_activities)
		{
			if(split_activity[nb_activities]->is_correct() && split_activity[nb_activities]->get_person() != 0)
				activities.push_back( new Activity(split_activity[nb_activities]) );
		}
	}
	activity_tmp->~Activity();
	
	relabel_activities_entremelee();


	database.close();
}

bool sort_activities_by_person_then_start_time( Activity *act_1, Activity *act_2 )
{
    return (act_1->get_person() < act_2->get_person()) ||
           (act_1->get_person() == act_2->get_person() && act_1->is_start_time_inf( act_2 ));
}

void Activities::relabel_activities_entremelee()
{
	std::sort( activities.begin(), activities.end(), sort_activities_by_person_then_start_time );
	for(unsigned i=0; i<activities.size(); ++i)
	{
		if(i+1 < activities.size() && activities[i]->get_person() == activities[i+1]->get_person())
			relabel_act(activities[i], activities[i+1]);
	}
}

void Activities::relabel_act(Activity* act_1, Activity* act_2)
{
	Label label = ABANDON;
	/*if(act_1->get_person() == 530 && act_1->get_chamber() == 10 && act_1->get_start_time_date()=="2018-01-06" && act_1->get_start_time_time()=="19:23:42.000")
		act_1->print_activity();*/	
	if(act_2->is_end_time_inf(act_1) || act_2->is_start_time_inf_end_time(act_1))
	{
		if(act_1->get_is_inout() || act_1->is_abandon_inout())
		{
			act_1->set_message_abandon_inout("activite entremelee");
			act_1->set_is_inout(false);
			act_1->set_is_abandon_inout(true);
		}
			
		else if( (act_1->get_is_in() || act_1->is_abandon_in()) && (act_1->get_is_out() || act_1->is_abandon_out()))
		{
			act_1->set_message_abandon_in("activite entremelee");
			act_1->set_message_abandon_out("activite entremelee");
			act_1->set_is_in(false);
			act_1->set_is_abandon_in(true);
			act_1->set_is_out(false);
			act_1->set_is_abandon_out(true);
		}
		
		else
		{
			cout << "\t !!! IMPOSSIBLE !!! " << endl;
			act_1->print_activity();
			label = IMPOSSIBLE;
		}
			
		act_1->clear_label();
		act_1->set_label(label);
		if(act_1->get_person() == 530 && act_1->get_chamber() == 10 && act_1->get_start_time_date()=="2018-01-06" && act_1->get_start_time_time()=="19:23:42.000")
			cout << act_1->get_message_abandon_in() << " " << act_1->get_message_abandon_out() << endl;
	}
}


// Write ALL activities
void Activities::write_activities_in_file(char* filename)
{
	ofstream output(filename, ios::out | ios::trunc);
	if(!output)
	{
		cerr << "Impossible to open the file " << filename << endl;
		exit(EXIT_FAILURE);		
	}
	
	unsigned alone = 0;
	unsigned several_persons = 0;
	
	for(unsigned i=0; i<activities.size(); ++i)
	{	
		activities[i]->write_file(output);
		if(activities[i]->is_alone())
			++ alone;
		else
			++ several_persons;
	}

	cout << "nb activities alone = " << alone << endl;
	cout << "nb activities several persons = " << several_persons << endl;
	cout << "nb activities = " << alone + several_persons << endl;
	output.close();
}



char Activities::write_headers(ofstream& output, bool excel, vector<string>& header)
{
	char sep = ',';
	if(excel)
		sep = ';';
	for(unsigned i=0; i<header.size(); ++i)
		if(i != header.size()-1)
			output << header[i] + sep;
		else
			output << header[i] << endl;
	return sep;
}


void Activities::write_csv_file(char* filename, bool excel, vector<string>& header)
{
	ofstream output(filename, ios::out | ios::trunc);
	if(!output)
	{
		cerr << "Impossible to open the file " << filename << endl;
		exit(EXIT_FAILURE);		
	}
	
	char sep = write_headers(output, excel, header);	
	
	unsigned unique_id = 1;
	unsigned activity_id = 1;
	unsigned chamber;
	int puce;
	
	for(unsigned i=0; i<activities.size(); ++i)
	{
		puce = activities[i]->get_person();
		if(puce == 0)
			continue;
		chamber = activities[i]->get_chamber();
		
		// inout activity => only one row
		if(activities[i]->get_is_inout() || activities[i]->is_abandon_inout())
		{	
			write_row(output, i, unique_id, 
				activity_id, puce, chamber, 0, sep);
			++ activity_id;	
		}
		// in and out => 2 rows
		else
		{
			write_row(output, i, unique_id, 
				activity_id, puce, chamber, 1, sep);
			write_row(output, i, unique_id, 
				activity_id, puce, chamber, 2, sep);	
			++ activity_id;				
		}
		
	}
	output.close();
}


void Activities::write_row(ofstream& output, unsigned num_activity, 
	unsigned& unique_id, unsigned& activity_id, unsigned puce, 
	unsigned chamber, unsigned in_out_inout, char sep)
{
	output << '"' << unique_id << '"' << sep
		   << '"' << puce << '"' << sep
		   << '"' << chamber << '"' << sep
		   << '"' << activity_id << '"' << sep;	
		
	// inout
	if(in_out_inout==0)
	{
		output << '"' << activities[num_activity]->get_message_abandon_inout() << '"' << sep
			   << '"' << "inout" << '"' << sep
			   << '"' << activities[num_activity]->get_start_time() << '"' << sep
			   << '"' << activities[num_activity]->get_end_time() << '"' << sep
			   << '"' << activities[num_activity]->get_duration() << '"' << sep
			   << '"' << static_cast<int>(activities[num_activity]->get_alarm_index_inout() != -1) << '"' << sep 
			   << '"' << static_cast<int>(activities[num_activity]->get_SHA_index_inout() != -1) << '"' << sep
			   << '"' << static_cast<int>(activities[num_activity]->get_SHA_during_alarm_index_inout() != -1) << '"' << sep
			   << '"' << label_to_str(activities[num_activity]->get_label_inout()) 
			   << '"' << endl;
	}
	// in
	else if(in_out_inout==1)
	{
		output << '"' << activities[num_activity]->get_message_abandon_in() << '"' << sep
			   << '"' << "in" << '"' << sep
			   << '"' << activities[num_activity]->get_start_time() << '"' << sep
			   << '"' << activities[num_activity]->get_end_time(true) << '"' << sep
			   << '"' << activities[num_activity]->get_duration(1) << '"' << sep
			   << '"' << static_cast<int>(activities[num_activity]->get_alarm_index_in() != -1) << '"' << sep 
			   << '"' << static_cast<int>(activities[num_activity]->get_SHA_index_in() != -1) << '"' << sep
			   << '"' << static_cast<int>(activities[num_activity]->get_SHA_during_alarm_index_in() != -1) << '"' << sep  
			   << '"' << label_to_str(activities[num_activity]->get_label_in()) 
			   << '"' << endl;
	}
	// out
	else if(in_out_inout==2)
	{
		output << '"' << activities[num_activity]->get_message_abandon_out() << '"' << sep
			   << '"' << "out" << '"' << sep
			   << '"' << activities[num_activity]->get_start_time(true) << '"' << sep
			   << '"' << activities[num_activity]->get_end_time() << '"' << sep
			   << '"' << activities[num_activity]->get_duration(2) << '"' << sep
			   << '"' << static_cast<int>(activities[num_activity]->get_alarm_index_out() != -1) << '"' << sep
			   << '"' << static_cast<int>(activities[num_activity]->get_SHA_index_out() != -1) << '"' << sep
			   << '"' << static_cast<int>(activities[num_activity]->get_SHA_during_alarm_index_out() != -1) << '"' << sep
			   << '"' << label_to_str(activities[num_activity]->get_label_out()) 
			   << '"' << endl;
	}
		
	++ unique_id;
}

