#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "activity.hpp"


/**
 * \file person.hpp
*/


/** 
 * \class Person
 * \brief 
*/
class Person
{
	private:
		//unsigned id_person;
		
		std::map<Label, unsigned> nb_each_labels;
		
		unsigned nb_activity_inout_total = 0;
		unsigned nb_activity_in_total = 0;
		unsigned nb_activity_out_total = 0;
		
	public:
		Person();

		unsigned get_nb_label(Label label);
		void incr_nb_label(Label label);

		void incr_nb_activity_inout_sure();
		void incr_nb_activity_in_sure();
		void incr_nb_activity_out_sure();
		
		unsigned get_nb_activity_inout_sure_total();
		unsigned get_nb_activity_in_sure_total();
		unsigned get_nb_activity_out_sure_total();
		
	
		unsigned get_nb_SHA_taken_sure_in() ;
		unsigned get_nb_SHA_not_taken_sure_in() ;
			
		unsigned get_nb_SHA_taken_sure_out() ;
		unsigned get_nb_SHA_not_taken_sure_out() ;
		
		unsigned get_nb_SHA_taken_sure_inout() ;
		unsigned get_nb_SHA_not_taken_sure_inout() ;
		

		void print_person();
		void write_file(std::ofstream& output);
};
	

#endif
