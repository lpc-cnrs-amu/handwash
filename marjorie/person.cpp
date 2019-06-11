
#include "person.hpp"

using namespace std;

Person::Person():
{
	nb_each_labels[IN_NO_ALARM] = 0;
	nb_each_labels[IN_AFTER_ALARM] = 0;
	nb_each_labels[IN_DURING_ALARM] = 0;
	nb_each_labels[OUT_NO_ALARM] = 0;
	nb_each_labels[OUT_AFTER_ALARM] = 0;
	nb_each_labels[OUT_DURING_ALARM] = 0;
	nb_each_labels[INOUT_NO_ALARM] = 0;
	nb_each_labels[INOUT_AFTER_ALARM] = 0;
	nb_each_labels[INOUT_DURING_ALARM] = 0;
	nb_each_labels[IN_POSSIBLE_NO_ALARM] = 0;
	nb_each_labels[IN_POSSIBLE_AFTER_ALARM] = 0;
	nb_each_labels[IN_POSSIBLE_DURING_ALARM] = 0;
	nb_each_labels[OUT_POSSIBLE_NO_ALARM] = 0;
	nb_each_labels[OUT_POSSIBLE_AFTER_ALARM] = 0;
	nb_each_labels[OUT_POSSIBLE_DURING_ALARM] = 0;
	nb_each_labels[INOUT_POSSIBLE_NO_ALARM] = 0;
	nb_each_labels[INOUT_POSSIBLE_AFTER_ALARM] = 0;
	nb_each_labels[INOUT_POSSIBLE_DURING_ALARM] = 0;
	nb_each_labels[NOT_IN_NO_ALARM] = 0;
	nb_each_labels[NOT_IN_ALARM] = 0;
	nb_each_labels[NOT_OUT_NO_ALARM] = 0;
	nb_each_labels[NOT_OUT_ALARM] = 0;
	nb_each_labels[NOT_INOUT_NO_ALARM] = 0;
	nb_each_labels[NOT_INOUT_ALARM] = 0;
}


unsigned Person::get_nb_label(Label label) { return nb_each_labels[label]; }
unsigned Person::get_nb_activity_taken_sure_in() 
{ 
	return nb_each_labels[IN_NO_ALARM] + 
		   nb_each_labels[IN_AFTER_ALARM] + 
		   nb_each_labels[IN_DURING_ALARM]; 
}
unsigned Person::get_nb_activity_not_taken_sure_in() 
{ 
	return nb_each_labels[NOT_IN_NO_ALARM] + 
		   nb_each_labels[NOT_IN_ALARM];
}
unsigned Person::get_nb_activity_taken_possible_in()
{
	return nb_each_labels[IN_POSSIBLE_NO_ALARM] + 
		   nb_each_labels[IN_POSSIBLE_AFTER_ALARM] + 
		   nb_each_labels[IN_POSSIBLE_DURING_ALARM];	
}

unsigned Person::get_nb_activity_taken_sure_out() 
{ 
	return nb_each_labels[OUT_NO_ALARM] + 
		   nb_each_labels[OUT_AFTER_ALARM] + 
		   nb_each_labels[OUT_DURING_ALARM]; 
}
unsigned Person::get_nb_activity_not_taken_sure_out() 
{ 
	return nb_each_labels[NOT_OUT_NO_ALARM] + 
		   nb_each_labels[NOT_OUT_ALARM];
}
unsigned Person::get_nb_activity_taken_possible_out()
{
	return nb_each_labels[OUT_POSSIBLE_NO_ALARM] + 
		   nb_each_labels[OUT_POSSIBLE_AFTER_ALARM] + 
		   nb_each_labels[OUT_POSSIBLE_DURING_ALARM];	
}

unsigned Person::get_nb_activity_taken_sure_inout() 
{ 
	return nb_each_labels[INOUT_NO_ALARM] + 
		   nb_each_labels[INOUT_AFTER_ALARM] + 
		   nb_each_labels[INOUT_DURING_ALARM]; 
}
unsigned Person::get_nb_activity_not_taken_sure_inout() 
{ 
	return nb_each_labels[NOT_INOUT_NO_ALARM] + 
		   nb_each_labels[NOT_INOUT_ALARM];
}
unsigned Person::get_nb_activity_taken_possible_inout()
{
	return nb_each_labels[INOUT_POSSIBLE_NO_ALARM] + 
		   nb_each_labels[INOUT_POSSIBLE_AFTER_ALARM] + 
		   nb_each_labels[INOUT_POSSIBLE_DURING_ALARM];	
}


void Person::incr_nb_label(Label label) 
{ 
	if ( nb_each_labels.find(label) == nb_each_labels.end() )
		cerr << "undefined label" << endl;
	else
		++ nb_each_labels[label]; 
	
}


void Person::incr_nb_activity_inout_sure() { ++ nb_activity_inout_sure_total; }
void Person::incr_nb_activity_inout_possible() { ++ nb_activity_inout_possible_total; }
void Person::incr_nb_activity_in_sure() { ++ nb_activity_in_sure_total; }
void Person::incr_nb_activity_out_sure() { ++ nb_activity_out_sure_total; }
void Person::incr_nb_activity_in_possible() { ++ nb_activity_in_possible_total; }
void Person::incr_nb_activity_out_possible() { ++ nb_activity_out_possible_total; }


unsigned Person::get_nb_activity_inout_sure_total() { return nb_activity_inout_sure_total; }
unsigned Person::get_nb_activity_inout_possible_total() { return nb_activity_inout_possible_total; }
unsigned Person::get_nb_activity_in_sure_total() { return nb_activity_in_sure_total; }
unsigned Person::get_nb_activity_out_sure_total() { return nb_activity_out_sure_total; }
unsigned Person::get_nb_activity_in_possible_total() { return nb_activity_in_possible_total; }
unsigned Person::get_nb_activity_out_possible_total() { return nb_activity_out_possible_total; }


void Person::print_person()
{/*
	cout << 
		"nb_SHA_sure_in " << nb_SHA_sure_in << endl <<
		"nb_SHA_sure_out" << nb_SHA_sure_out << endl <<

		"nb_SHA_possible_in" << nb_SHA_possible_in << endl <<
		"nb_SHA_possible_out" << nb_SHA_possible_out << endl <<

		"nb_SHA_sure_inout" << nb_SHA_sure_inout << endl <<
		"nb_SHA_possible_inout" << nb_SHA_possible_inout << endl; */
}

void Person::write_file(ofstream& output)
{/*
	output << 
		"nb_SHA_sure_in " << nb_SHA_sure_in << endl <<
		"nb_SHA_sure_out" << nb_SHA_sure_out << endl <<

		"nb_SHA_possible_in" << nb_SHA_possible_in << endl <<
		"nb_SHA_possible_out" << nb_SHA_possible_out << endl <<

		"nb_SHA_sure_inout" << nb_SHA_sure_inout << endl <<
		"nb_SHA_possible_inout" << nb_SHA_possible_inout << endl;*/
}
