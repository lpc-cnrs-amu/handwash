
#include "person.hpp"

using namespace std;

Person::Person()
{
		// occurrences
	// SHA pris dans le in
	nb_each_labels[IN_NO_ALARM] = 0;
	nb_each_labels[IN_AFTER_ALARM] = 0;
	nb_each_labels[IN_DURING_ALARM] = 0;
	// SHA pris dans le out
	nb_each_labels[OUT_NO_ALARM] = 0;
	nb_each_labels[OUT_AFTER_ALARM] = 0;
	nb_each_labels[OUT_DURING_ALARM] = 0;	
	// SHA pris dans le inout
	nb_each_labels[INOUT_NO_ALARM] = 0;
	nb_each_labels[INOUT_AFTER_ALARM] = 0;
	nb_each_labels[INOUT_DURING_ALARM] = 0;	
	
	// SHA pas pris dans le in
	nb_each_labels[NOT_IN_NO_ALARM] = 0;
	nb_each_labels[NOT_IN_ALARM] = 0;
	// SHA pas pris dans le out
	nb_each_labels[NOT_OUT_NO_ALARM] = 0;
	nb_each_labels[NOT_OUT_ALARM] = 0;
	// SHA pas pris dans le inout
	nb_each_labels[NOT_INOUT_NO_ALARM] = 0;
	nb_each_labels[NOT_INOUT_ALARM] = 0;
	
	// abandon de l'activité
	nb_each_labels[ABANDON_IN] = 0;
	nb_each_labels[ABANDON_OUT] = 0;
	nb_each_labels[ABANDON_INOUT] = 0;
	
	// cas impossible
	nb_each_labels[IMPOSSIBLE] = 0;
	
		// Percents
	// SHA pris dans le in
	percent_each_labels[IN_NO_ALARM] = 0;
	percent_each_labels[IN_AFTER_ALARM] = 0;
	percent_each_labels[IN_DURING_ALARM] = 0;
	// SHA pris dans le out
	percent_each_labels[OUT_NO_ALARM] = 0;
	percent_each_labels[OUT_AFTER_ALARM] = 0;
	percent_each_labels[OUT_DURING_ALARM] = 0;
	// SHA pris dans le inout
	percent_each_labels[INOUT_NO_ALARM = 0;
	percent_each_labels[INOUT_AFTER_ALARM] = 0;
	percent_each_labels[INOUT_DURING_ALARM] = 0;
	
	// SHA pas pris dans le in
	percent_each_labels[NOT_IN_NO_ALARM] = 0;
	percent_each_labels[NOT_IN_ALARM] = 0;
	// SHA pas pris dans le out
	percent_each_labels[NOT_OUT_NO_ALARM] = 0;
	percent_each_labels[NOT_OUT_ALARM] = 0;
	// SHA pas pris dans le inout
	percent_each_labels[NOT_INOUT_NO_ALARM] = 0;
	percent_each_labels[NOT_INOUT_ALARM] = 0;
	
	// abandon de l'activité
	percent_each_labels[ABANDON_IN] = 0;
	percent_each_labels[ABANDON_OUT] = 0;
	percent_each_labels[ABANDON_INOUT] = 0;
	
	// cas impossible
	percent_each_labels[IMPOSSIBLE] = 0;
}


unsigned Person::get_nb_label(Label label) { return nb_each_labels[label]; }


unsigned Person::get_nb_SHA_in() 
{ 
	return nb_each_labels[IN_NO_ALARM] + 
		   nb_each_labels[IN_AFTER_ALARM] + 
		   nb_each_labels[IN_DURING_ALARM]; 
}
unsigned Person::get_nb_SHA_not_taken_in() 
{ 
	return nb_each_labels[NOT_IN_NO_ALARM] + 
		   nb_each_labels[NOT_IN_ALARM];
}

unsigned Person::get_nb_SHA_taken_out() 
{ 
	return nb_each_labels[OUT_NO_ALARM] + 
		   nb_each_labels[OUT_AFTER_ALARM] + 
		   nb_each_labels[OUT_DURING_ALARM]; 
}
unsigned Person::get_nb_SHA_not_taken_out() 
{ 
	return nb_each_labels[NOT_OUT_NO_ALARM] + 
		   nb_each_labels[NOT_OUT_ALARM];
}

unsigned Person::get_nb_SHA_taken_inout() 
{ 
	return nb_each_labels[INOUT_NO_ALARM] + 
		   nb_each_labels[INOUT_AFTER_ALARM] + 
		   nb_each_labels[INOUT_DURING_ALARM]; 
}
unsigned Person::get_nb_SHA_not_taken_inout() 
{ 
	return nb_each_labels[NOT_INOUT_NO_ALARM] + 
		   nb_each_labels[NOT_INOUT_ALARM];
}
unsigned Person::get_nb_total_abandon()
{
	return nb_each_labels[ABANDON_IN] + 
		   nb_each_labels[ABANDON_OUT] + 
		   nb_each_labels[ABANDON_INOUT];
}


void Person::incr_label(Label label) 
{ 
	if( nb_each_labels.find(label) == nb_each_labels.end() )
		cerr << "undefined label" << endl;
	else
		++ nb_each_labels[label]; 
}


void Person::incr_nb_activity_inout() 	{ ++ nb_activities_inout; }
void Person::incr_nb_activity_in() 		{ ++ nb_activities_in; 	  }
void Person::incr_nb_activity_out() 	{ ++ nb_activities_out;   }

unsigned Person::get_nb_activity_inout_sure_total() { return nb_activities_inout;   }
unsigned Person::get_nb_activity_in_sure_total() 	{ return nb_activities_in; 		}
unsigned Person::get_nb_activity_out_sure_total() 	{ return nb_activities_out; 	}


void Person::calcul_percent()
{
	// in
	if( nb_activities_in != 0 )
	{
		percent_each_labels[IN_NO_ALARM] = nb_each_labels[IN_NO_ALARM] / (float)nb_activities_in;
		percent_each_labels[IN_AFTER_ALARM] = nb_each_labels[IN_AFTER_ALARM] / (float)nb_activities_in;
		percent_each_labels[IN_DURING_ALARM] = nb_each_labels[IN_DURING_ALARM] / (float)nb_activities_in;
		percent_each_labels[NOT_IN_NO_ALARM] = nb_each_labels[NOT_IN_NO_ALARM] / (float)nb_activities_in;
		percent_each_labels[NOT_IN_ALARM] = nb_each_labels[NOT_IN_ALARM] / (float)nb_activities_in;
	}
	
	// out
	if( nb_activities_out != 0 )
	{
		percent_each_labels[OUT_NO_ALARM] = nb_each_labels[OUT_NO_ALARM] / (float)nb_activities_out;
		percent_each_labels[OUT_AFTER_ALARM] = nb_each_labels[OUT_AFTER_ALARM] / (float)nb_activities_out;
		percent_each_labels[OUT_DURING_ALARM] = nb_each_labels[OUT_DURING_ALARM] / (float)nb_activities_out;
		percent_each_labels[NOT_OUT_NO_ALARM] = nb_each_labels[NOT_OUT_NO_ALARM] / (float)nb_activities_out;
		percent_each_labels[NOT_OUT_ALARM] = nb_each_labels[NOT_OUT_ALARM] / (float)nb_activities_out;
	}
	
	// inout
	if( nb_activities_inout != 0 )
	{
		percent_each_labels[INOUT_NO_ALARM] = nb_each_labels[INOUT_NO_ALARM] / (float)nb_activities_inout;
		percent_each_labels[INOUT_AFTER_ALARM] = nb_each_labels[INOUT_AFTER_ALARM] / (float)nb_activities_inout;
		percent_each_labels[INOUT_DURING_ALARM] = nb_each_labels[INOUT_DURING_ALARM] / (float)nb_activities_inout;
		percent_each_labels[NOT_INOUT_NO_ALARM] = nb_each_labels[NOT_INOUT_NO_ALARM] / (float)nb_activities_inout;
		percent_each_labels[NOT_INOUT_ALARM] = nb_each_labels[NOT_INOUT_ALARM] / (float)nb_activities_inout;
	}
	
	// abandon de l'activité
	unsigned nb_total_abandon = get_nb_total_abandon();
	if( nb_total_abandon != 0 )
	{
		percent_each_labels[ABANDON_IN] = nb_each_labels[ABANDON_IN] / (float)nb_total_abandon;
		percent_each_labels[ABANDON_OUT] = nb_each_labels[ABANDON_OUT] / (float)nb_total_abandon;
		percent_each_labels[ABANDON_INOUT] = nb_each_labels[ABANDON_INOUT] / (float)nb_total_abandon;
	}
	
	// cas généraux
	unsigned total_activities = get_nb_total_activities();
	if( total_activities != 0 )
	{
		percent_each_labels[IMPOSSIBLE] = nb_each_labels[IMPOSSIBLE] / (float)total_activities;
		SHA_in_percent =  get_nb_SHA_in() / (float)total_activities;
		SHA_not_taken_in_percent = get_nb_SHA_not_taken_in() / (float)total_activities;
		SHA_out_percent = get_nb_SHA_out() / (float)total_activities;
		SHA_not_taken_out_percent = get_nb_SHA_not_taken_out() / (float)total_activities;
		SHA_inout_percent = get_nb_SHA_inout() / (float)total_activities;
		SHA_not_taken_inout_percent = get_nb_SHA_not_taken_inout() / (float)total_activities;
	}
}

void Person::print_person()
{
	cout << 
		 << "nb_SHA_sure_in " << nb_SHA_sure_in << endl 
		 << "nb_SHA_sure_out" << nb_SHA_sure_out << endl

		 << "nb_SHA_possible_in" << nb_SHA_possible_in << endl
		 << "nb_SHA_possible_out" << nb_SHA_possible_out << endl

		 << "nb_SHA_sure_inout" << nb_SHA_sure_inout << endl
		 << "nb_SHA_possible_inout" << nb_SHA_possible_inout << endl;
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
