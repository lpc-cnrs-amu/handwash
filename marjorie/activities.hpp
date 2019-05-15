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

	public:
		Activities(char* filename, bool excel_csv);
		~Activities();
		
		void write_file(char* filename);
};
	

#endif
