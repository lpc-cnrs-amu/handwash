
#include "person.hpp"

using namespace std;

Person::Person(
	unsigned SHA_sure_in,
	unsigned SHA_sure_out,
	
	unsigned SHA_possible_in,
	unsigned SHA_possible_out,
	
	unsigned SHA_sure_inout,
	unsigned SHA_possible_inout,
	
	bool not_taken_in,
	bool not_taken_out,
	bool not_taken_inout
) :
	nb_SHA_sure_in (SHA_sure_in),
	nb_SHA_sure_out (SHA_sure_out),

	nb_SHA_possible_in (SHA_possible_in),
	nb_SHA_possible_out (SHA_possible_out),

	nb_SHA_sure_inout (SHA_sure_inout),
	nb_SHA_possible_inout (SHA_possible_inout),
	
	nb_not_taken_in (not_taken_in),
	nb_not_taken_out (not_taken_out),
	nb_not_taken_inout (not_taken_inout)	
{

}


void Person::add_nb_SHA_sure_in(unsigned nb) { nb_SHA_sure_in += nb; }
void Person::add_nb_SHA_sure_out(unsigned nb) { nb_SHA_sure_out += nb; }

void Person::add_nb_SHA_possible_in(unsigned nb) { nb_SHA_possible_in += nb; }
void Person::add_nb_SHA_possible_out(unsigned nb) { nb_SHA_possible_out += nb; }

void Person::add_nb_SHA_sure_inout(unsigned nb) { nb_SHA_sure_inout += nb; }
void Person::add_nb_SHA_possible_inout(unsigned nb) { nb_SHA_possible_inout += nb; }

void Person::incr_not_taken_in() { ++nb_not_taken_in; }
void Person::incr_not_taken_out() { ++nb_not_taken_out; }
void Person::incr_not_taken_inout() { ++nb_not_taken_inout; }

void Person::print_person()
{
	cout << 
		"nb_SHA_sure_in " << nb_SHA_sure_in << endl <<
		"nb_SHA_sure_out" << nb_SHA_sure_out << endl <<

		"nb_SHA_possible_in" << nb_SHA_possible_in << endl <<
		"nb_SHA_possible_out" << nb_SHA_possible_out << endl <<

		"nb_SHA_sure_inout" << nb_SHA_sure_inout << endl <<
		"nb_SHA_possible_inout" << nb_SHA_possible_inout << endl; 
}

void Person::write_file(ofstream& output)
{
	output << 
		"nb_SHA_sure_in " << nb_SHA_sure_in << endl <<
		"nb_SHA_sure_out" << nb_SHA_sure_out << endl <<

		"nb_SHA_possible_in" << nb_SHA_possible_in << endl <<
		"nb_SHA_possible_out" << nb_SHA_possible_out << endl <<

		"nb_SHA_sure_inout" << nb_SHA_sure_inout << endl <<
		"nb_SHA_possible_inout" << nb_SHA_possible_inout << endl;
}
