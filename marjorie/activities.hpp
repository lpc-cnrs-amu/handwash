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
		std::vector< Activity* > activities; 
		
		char write_headers(std::ofstream& output, bool excel, std::vector<std::string>& header);
		void write_row(std::ofstream& output, unsigned num_activity, 
			unsigned& unique_id, unsigned& activity_id, unsigned puce, 
			unsigned chamber, unsigned in_out_inout, char sep);
			
	public:
		Activities(char* filename, bool excel_csv);
		~Activities();
		
		void write_csv_file(char* filename, bool excel, std::vector<std::string>& header);
};
	

#endif
