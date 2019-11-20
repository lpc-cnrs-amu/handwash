#ifndef ACTIVITIES_HPP
#define ACTIVITIES_HPP

#include <vector>
#include "activity.hpp"

/**
 * \file activities.hpp
*/


/** 
 * \class Activities
 * \brief Class representing all activities   
 * from the hygiene csv file. 
*/
class Activities
{
	private:
		
		
		void relabel_act(Activity* act_1, Activity* act_2);
		void relabel_activities_entremelee();
		
		char write_headers(std::ofstream& output, bool excel, std::vector<std::string>& header);
		void write_row(std::ofstream& output, unsigned num_activity, 
			unsigned& unique_id, unsigned& activity_id, unsigned puce, 
			unsigned chamber, unsigned in_out_inout, char sep);
			
	public:
		std::vector< Activity* > activities; 
		Activities(char* filename, bool excel_csv);
		~Activities();
		
		void write_csv_file(char* filename, bool excel, std::vector<std::string>& header);
		void write_activities_in_file(char* filename);
		unsigned get_nb_activities();
		int get_person(unsigned num_activity);
};


#endif
