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
		std::map<Label, float> percent_each_labels;
		
		unsigned nb_activities_inout = 0;
		unsigned nb_activities_in = 0;
		unsigned nb_activities_out = 0;
		float SHA_in_percent =  0;
		float SHA_not_taken_in_percent = 0;
		float SHA_out_percent = 0;
		float SHA_not_taken_out_percent = 0;
		float SHA_inout_percent = 0;
		float SHA_not_taken_inout_percent = 0;
		
		
		
		
	public:
		Person();

		unsigned get_nb_label(Label label);

		unsigned get_nb_SHA_taken_in();
		unsigned get_nb_SHA_not_taken_in();

		unsigned get_nb_SHA_taken_out();
		unsigned get_nb_SHA_not_taken_out();

		unsigned get_nb_SHA_taken_inout();
		unsigned get_nb_SHA_not_taken_inout();
		unsigned get_nb_total_abandon();

		void incr_label(Label label);
		void incr_nb_activity_inout();
		void incr_nb_activity_in();
		void incr_nb_activity_out();

		unsigned get_nb_activity_inout_total();
		unsigned get_nb_activity_in_total();
		unsigned get_nb_activity_out_total();

		
		void write_person(unsigned id, std::ofstream& output);
		void print_person(unsigned id);
		
		void calcul_percent();
};
	

#endif
