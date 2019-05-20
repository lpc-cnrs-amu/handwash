#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <map>


/**
 * \file person.hpp
*/


/** 
 * \class Person
 * \brief 
*/
class Person
{
	public:
		//unsigned id_person;
		
		unsigned nb_SHA_sure_in = 0;
		unsigned nb_SHA_sure_out = 0;
		
		unsigned nb_SHA_possible_in = 0;
		unsigned nb_SHA_possible_out = 0;
		
		unsigned nb_SHA_sure_inout = 0;
		unsigned nb_SHA_possible_inout = 0;		
		
		unsigned nb_not_taken_in = 0;
		unsigned nb_not_taken_out = 0;
		unsigned nb_not_taken_inout = 0;
		
		unsigned nb_SHA_inout_sure_total = 0;
		unsigned nb_SHA_inout_possible_total = 0;
		unsigned nb_SHA_in_sure_total = 0;
		unsigned nb_SHA_out_sure_total = 0;
		unsigned nb_SHA_in_possible_total = 0;	
		unsigned nb_SHA_out_possible_total = 0;
		
	
		Person(	unsigned SHA_sure_in = 0,
				unsigned SHA_sure_out = 0,
				
				unsigned SHA_possible_in = 0,
				unsigned SHA_possible_out = 0,
				
				unsigned SHA_sure_inout = 0,
				unsigned SHA_possible_inout = 0,
				
				bool not_taken_in = false,
				bool not_taken_out = false,
				bool not_taken_inout = false);

		void add_nb_SHA_sure_in			(unsigned nb);
		void add_nb_SHA_sure_out		(unsigned nb);

		void add_nb_SHA_possible_in		(unsigned nb);
		void add_nb_SHA_possible_out	(unsigned nb);

		void add_nb_SHA_sure_inout		(unsigned nb);
		void add_nb_SHA_possible_inout	(unsigned nb);
		
		void incr_not_taken_in();
		void incr_not_taken_out();
		void incr_not_taken_inout();

		
		void incr_nb_SHA_inout_sure_total();
		void incr_nb_SHA_inout_possible_total();
		void incr_nb_SHA_in_sure_total();
		void incr_nb_SHA_out_sure_total();
		void incr_nb_SHA_in_possible_total();	
		void incr_nb_SHA_out_possible_total();



		void print_person();
		void write_file(std::ofstream& output);
};
	

#endif


