#include "activities.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
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
	bool append_activity = true;
	vector<Activity*> split_activity; 
	Activity* activity_tmp = new Activity();
	unsigned cpt_line = 0;
	
	while(std::getline(database, line))
	{
		++cpt_line;
		if(cpt_line==1)
			continue;
			
		// add to the current activity
		append_activity = activity_tmp->check_and_append_event_to_activity( new Event(line, excel_csv) );
		
		if(!append_activity)
		{
			activity_tmp->activity_per_person(split_activity); 
			
			if(split_activity.size()==0)
				activities.push_back( new Activity(activity_tmp) );
			else
			{
				for(unsigned nb_activities=0; nb_activities < split_activity.size(); ++nb_activities)
					activities.push_back( new Activity(split_activity[nb_activities]) );
			}
			
			
			activity_tmp->~Activity();
			activity_tmp = new Activity( new Event(line, excel_csv) );
			append_activity = true;
		}
	}
	if(append_activity)
	{
		activity_tmp->activity_per_person(split_activity);
		
		if(split_activity.size()==0)
			activities.push_back( new Activity(activity_tmp) );
		else
		{
			for(unsigned nb_activities=0; nb_activities < split_activity.size(); ++nb_activities)
				activities.push_back( new Activity(split_activity[nb_activities]) );
		}
		
		
		activity_tmp->~Activity();
		activity_tmp = new Activity( new Event(line, excel_csv) );
	}

	database.close();
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

// Write ALL activities
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
		if(activities[i]->get_is_inout())
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
	
	if( (in_out_inout==0 && activities[num_activity]->is_abandon_inout()) ||
		(in_out_inout==1 && activities[num_activity]->is_abandon_in()) ||
		(in_out_inout==2 && activities[num_activity]->is_abandon_out()) )
	{
		output << '"' << 1 << '"' << sep;
	}
	else
		output << '"' << 0 << '"' << sep;
		
	// inout
	if(in_out_inout==0)
	{
		output << '"' << "inout" << '"' << sep
			   << '"' << activities[num_activity]->get_start_time() << '"' << sep
			   << '"' << activities[num_activity]->get_end_time() << '"' << sep
			   << '"' << activities[num_activity]->get_duration() << '"' << sep
			   << '"' << static_cast<int>(activities[num_activity]->get_alarm_index_inout() != -1) << '"' << sep 
			   << '"' << static_cast<int>(activities[num_activity]->get_SHA_index_inout() != -1) << '"' << sep
			   << '"' << static_cast<int>(activities[num_activity]->get_SHA_during_alarm_index_inout() != -1) << '"' << sep
			   << '"' << label_to_str(activities[num_activity]->get_label_inout()) 
			   << '"' <<  sep << endl;
	}
	// in
	else if(in_out_inout==1)
	{
		output << "in" << sep
			   << '"' << activities[num_activity]->get_start_time() << '"' << sep
			   << '"' << activities[num_activity]->get_end_time(true) << '"' << sep
			   << '"' << activities[num_activity]->get_duration(1) << '"' << sep
			   << '"' << static_cast<int>(activities[num_activity]->get_alarm_index_in() != -1) << '"' << sep 
			   << '"' << static_cast<int>(activities[num_activity]->get_SHA_index_in() != -1) << '"' << sep
			   << '"' << static_cast<int>(activities[num_activity]->get_SHA_during_alarm_index_in() != -1) << '"' << sep  
			   << '"' << label_to_str(activities[num_activity]->get_label_in()) 
			   << '"' <<  sep << endl;
	}
	// out
	else if(in_out_inout==2)
	{
		output << "out" << sep
			   << '"' << activities[num_activity]->get_start_time(true) << '"' << sep
			   << '"' << activities[num_activity]->get_end_time() << '"' << sep
			   << '"' << activities[num_activity]->get_duration(2) << '"' << sep
			   << '"' << static_cast<int>(activities[num_activity]->get_alarm_index_out() != -1) << '"' << sep
			   << '"' << static_cast<int>(activities[num_activity]->get_SHA_index_out() != -1) << '"' << sep
			   << '"' << static_cast<int>(activities[num_activity]->get_SHA_during_alarm_index_out() != -1) << '"' << sep
			   << '"' << label_to_str(activities[num_activity]->get_label_out()) 
			   << '"' <<  sep << endl;
	}
		
	++ unique_id;
}

