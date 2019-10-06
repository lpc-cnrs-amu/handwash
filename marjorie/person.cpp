#include <iomanip>
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
	percent_each_labels[INOUT_NO_ALARM] = 0;
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


unsigned Person::get_nb_SHA_taken_in()
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
void Person::incr_nb_SHA_30_sec_inout() { ++ nb_SHA_30_sec_inout; }
void Person::incr_nb_SHA_30_sec_in() 	{ ++ nb_SHA_30_sec_in;	  }
void Person::incr_nb_SHA_30_sec_out()	{ ++ nb_SHA_30_sec_out;   }

unsigned Person::get_nb_activity_inout_total()  { return nb_activities_inout;   }
unsigned Person::get_nb_activity_in_total() 	{ return nb_activities_in; 		}
unsigned Person::get_nb_activity_out_total() 	{ return nb_activities_out; 	}


void Person::calcul_percent()
{
	// in
	if( nb_activities_in != 0 )
	{
		percent_each_labels[IN_NO_ALARM] = 100 * nb_each_labels[IN_NO_ALARM] / (float)nb_activities_in;
		percent_each_labels[IN_AFTER_ALARM] = 100 * nb_each_labels[IN_AFTER_ALARM] / (float)nb_activities_in;
		percent_each_labels[IN_DURING_ALARM] = 100 * nb_each_labels[IN_DURING_ALARM] / (float)nb_activities_in;
		percent_each_labels[NOT_IN_NO_ALARM] = 100 * nb_each_labels[NOT_IN_NO_ALARM] / (float)nb_activities_in;
		percent_each_labels[NOT_IN_ALARM] = 100 * nb_each_labels[NOT_IN_ALARM] / (float)nb_activities_in;
		percent_SHA_30_sec_in = 100 * nb_SHA_30_sec_in / (float)nb_activities_in;
	}
	
	// out
	if( nb_activities_out != 0 )
	{
		percent_each_labels[OUT_NO_ALARM] = 100 * nb_each_labels[OUT_NO_ALARM] / (float)nb_activities_out;
		percent_each_labels[OUT_AFTER_ALARM] = 100 * nb_each_labels[OUT_AFTER_ALARM] / (float)nb_activities_out;
		percent_each_labels[OUT_DURING_ALARM] = 100 * nb_each_labels[OUT_DURING_ALARM] / (float)nb_activities_out;
		percent_each_labels[NOT_OUT_NO_ALARM] = 100 * nb_each_labels[NOT_OUT_NO_ALARM] / (float)nb_activities_out;
		percent_each_labels[NOT_OUT_ALARM] = 100 * nb_each_labels[NOT_OUT_ALARM] / (float)nb_activities_out;
		percent_SHA_30_sec_out = 100 * nb_SHA_30_sec_out / (float)nb_activities_out;
	}
	
	// inout
	if( nb_activities_inout != 0 )
	{
		percent_each_labels[INOUT_NO_ALARM] = 100 * nb_each_labels[INOUT_NO_ALARM] / (float)nb_activities_inout;
		percent_each_labels[INOUT_AFTER_ALARM] = 100 * nb_each_labels[INOUT_AFTER_ALARM] / (float)nb_activities_inout;
		percent_each_labels[INOUT_DURING_ALARM] = 100 * nb_each_labels[INOUT_DURING_ALARM] / (float)nb_activities_inout;
		percent_each_labels[NOT_INOUT_NO_ALARM] = 100 * nb_each_labels[NOT_INOUT_NO_ALARM] / (float)nb_activities_inout;
		percent_each_labels[NOT_INOUT_ALARM] = 100 * nb_each_labels[NOT_INOUT_ALARM] / (float)nb_activities_inout;
		percent_SHA_30_sec_inout = 100 * nb_SHA_30_sec_inout / (float)nb_activities_inout;
	}
	
	// abandon de l'activité
	unsigned nb_total_abandon = get_nb_total_abandon();
	if( nb_total_abandon != 0 )
	{
		percent_each_labels[ABANDON_IN] = 100 * nb_each_labels[ABANDON_IN] / (float)(nb_total_abandon+nb_activities_in);
		percent_each_labels[ABANDON_OUT] = 100 * nb_each_labels[ABANDON_OUT] / (float)(nb_total_abandon+nb_activities_out);
		percent_each_labels[ABANDON_INOUT] = 100 * nb_each_labels[ABANDON_INOUT] / (float)(nb_total_abandon+nb_activities_inout);
	}
	
	// cas généraux
	unsigned total_activities = nb_activities_inout + nb_activities_out + nb_activities_in;
	if( total_activities != 0 )
	{
		percent_each_labels[IMPOSSIBLE] = 100 * nb_each_labels[IMPOSSIBLE] / (float)total_activities;
	}
	if( nb_activities_in != 0 )
	{
		SHA_in_percent =  100 * get_nb_SHA_taken_in() / (float)nb_activities_in;
		SHA_not_taken_in_percent = 100 * get_nb_SHA_not_taken_in() / (float)nb_activities_in;
	}
	if( nb_activities_out != 0 )
	{
		SHA_out_percent = 100 * get_nb_SHA_taken_out() / (float)nb_activities_out;
		SHA_not_taken_out_percent = 100 * get_nb_SHA_not_taken_out() / (float)nb_activities_out;
	}
	if( nb_activities_inout != 0 )
	{
		SHA_inout_percent = 100 * get_nb_SHA_taken_inout() / (float)nb_activities_inout;
		SHA_not_taken_inout_percent = 100 * get_nb_SHA_not_taken_inout() / (float)nb_activities_inout;
	}
}

void Person::print_person(unsigned id)
{
	cout << "\"" << id << "\";" 
	
		<< "\"" << nb_activities_in << "\";"
		<< "\"" << nb_activities_out << "\";"
		<< "\"" << nb_activities_inout << "\";"
			
		
		<< "\"" << std::fixed << std::setprecision(2) << SHA_in_percent << "\";"
		<< "\"" << get_nb_SHA_taken_in() << "\";"
		<< "\"" << std::fixed << std::setprecision(2) << SHA_out_percent << "\";"
		<< "\"" << get_nb_SHA_taken_out() << "\";"
		<< "\"" << std::fixed << std::setprecision(2) << SHA_inout_percent << "\";"
		<< "\"" << get_nb_SHA_taken_inout() << "\";"

		<< "\"" << std::fixed << std::setprecision(2) << SHA_not_taken_in_percent << "\";"
		<< "\"" << get_nb_SHA_not_taken_in() << "\";"
		<< "\"" << std::fixed << std::setprecision(2) << SHA_not_taken_out_percent << "\";"
		<< "\"" << get_nb_SHA_not_taken_out() << "\";"
		<< "\"" << std::fixed << std::setprecision(2) << SHA_not_taken_inout_percent << "\";"
		<< "\"" << get_nb_SHA_not_taken_inout() << "\";"
		
		<< "\"" << std::fixed << std::setprecision(2) << percent_each_labels[IN_NO_ALARM] << "\";"
		<< "\""<< nb_each_labels[IN_NO_ALARM] <<"\";"
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[IN_AFTER_ALARM]  <<"\";"
		<< "\""<< nb_each_labels[IN_AFTER_ALARM] <<"\";"
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[IN_DURING_ALARM] <<"\";" 
		<< "\""<< nb_each_labels[IN_DURING_ALARM] <<"\";" 
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[NOT_IN_NO_ALARM] <<"\";"
		<< "\""<< nb_each_labels[NOT_IN_NO_ALARM] <<"\";"
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[NOT_IN_ALARM] <<"\";"
		<< "\""<< nb_each_labels[NOT_IN_ALARM] <<"\";"
		
		<< "\"" << std::fixed << std::setprecision(2) << percent_each_labels[OUT_NO_ALARM] << "\";"
		<< "\""<< nb_each_labels[OUT_NO_ALARM] <<"\";"
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[OUT_AFTER_ALARM]  <<"\";"
		<< "\""<< nb_each_labels[OUT_AFTER_ALARM] <<"\";"
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[OUT_DURING_ALARM] <<"\";" 
		<< "\""<< nb_each_labels[OUT_DURING_ALARM] <<"\";" 
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[NOT_OUT_NO_ALARM] <<"\";"
		<< "\""<< nb_each_labels[NOT_OUT_NO_ALARM] <<"\";"
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[NOT_OUT_ALARM] <<"\";"
		<< "\""<< nb_each_labels[NOT_OUT_ALARM] <<"\";"
		
		<< "\"" << std::fixed << std::setprecision(2) << percent_each_labels[INOUT_NO_ALARM] << "\";"
		<< "\""<< nb_each_labels[INOUT_NO_ALARM] <<"\";"
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[INOUT_AFTER_ALARM]  <<"\";"
		<< "\""<< nb_each_labels[INOUT_AFTER_ALARM] <<"\";"
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[INOUT_DURING_ALARM] <<"\";" 
		<< "\""<< nb_each_labels[INOUT_DURING_ALARM] <<"\";" 
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[NOT_INOUT_NO_ALARM] <<"\";"
		<< "\""<< nb_each_labels[NOT_INOUT_NO_ALARM] <<"\";"
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[NOT_INOUT_ALARM] <<"\";"
		<< "\""<< nb_each_labels[NOT_INOUT_ALARM] <<"\";"
	
		<< "\"" << std::fixed << std::setprecision(2) << percent_each_labels[ABANDON_IN] << "\";"
		<< "\""<< nb_each_labels[ABANDON_IN] <<"\";"	
		<< "\"" << std::fixed << std::setprecision(2) << percent_each_labels[ABANDON_OUT] << "\";"
		<< "\""<< nb_each_labels[ABANDON_OUT] <<"\";"
		<< "\"" << std::fixed << std::setprecision(2) << percent_each_labels[ABANDON_INOUT] << "\";"
		<< "\""<< nb_each_labels[ABANDON_INOUT] <<"\";"

		<< "\"" << std::fixed << std::setprecision(2) << percent_SHA_30_sec_in << "\";"
		<< "\""<< nb_SHA_30_sec_in <<"\";"	
		<< "\"" << std::fixed << std::setprecision(2) << percent_SHA_30_sec_out << "\";"
		<< "\""<< nb_SHA_30_sec_out <<"\";"
		<< "\"" << std::fixed << std::setprecision(2) << percent_SHA_30_sec_inout << "\";"
		<< "\""<< nb_SHA_30_sec_inout <<"\";"
				
		<< "\"" << std::fixed << std::setprecision(2) << percent_each_labels[IMPOSSIBLE] << "\";"
		<< "\""<< nb_each_labels[IMPOSSIBLE] <<"\";"
		
		<< endl;
}

void Person::write_person(unsigned id, ofstream& output)
{

	output << "\"" << id << "\";" 
		<< "\"" << nb_activities_in << "\";"
		<< "\"" << nb_activities_out << "\";"
		<< "\"" << nb_activities_inout << "\";"
		
		<< "\"" << std::fixed << std::setprecision(2) << SHA_in_percent << "\";"
		<< "\"" << get_nb_SHA_taken_in() << "\";"
		<< "\"" << std::fixed << std::setprecision(2) << SHA_out_percent << "\";"
		<< "\"" << get_nb_SHA_taken_out() << "\";"
		<< "\"" << std::fixed << std::setprecision(2) << SHA_inout_percent << "\";"
		<< "\"" << get_nb_SHA_taken_inout() << "\";"

		<< "\"" << std::fixed << std::setprecision(2) << SHA_not_taken_in_percent << "\";"
		<< "\"" << get_nb_SHA_not_taken_in() << "\";"
		<< "\"" << std::fixed << std::setprecision(2) << SHA_not_taken_out_percent << "\";"
		<< "\"" << get_nb_SHA_not_taken_out() << "\";"
		<< "\"" << std::fixed << std::setprecision(2) << SHA_not_taken_inout_percent << "\";"
		<< "\"" << get_nb_SHA_not_taken_inout() << "\";"
		
		<< "\"" << std::fixed << std::setprecision(2) << percent_each_labels[IN_NO_ALARM] << "\";"
		<< "\""<< nb_each_labels[IN_NO_ALARM] <<"\";"
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[IN_AFTER_ALARM]  <<"\";"
		<< "\""<< nb_each_labels[IN_AFTER_ALARM] <<"\";"
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[IN_DURING_ALARM] <<"\";" 
		<< "\""<< nb_each_labels[IN_DURING_ALARM] <<"\";" 
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[NOT_IN_NO_ALARM] <<"\";"
		<< "\""<< nb_each_labels[NOT_IN_NO_ALARM] <<"\";"
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[NOT_IN_ALARM] <<"\";"
		<< "\""<< nb_each_labels[NOT_IN_ALARM] <<"\";"
		
		<< "\"" << std::fixed << std::setprecision(2) << percent_each_labels[OUT_NO_ALARM] << "\";"
		<< "\""<< nb_each_labels[OUT_NO_ALARM] <<"\";"
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[OUT_AFTER_ALARM]  <<"\";"
		<< "\""<< nb_each_labels[OUT_AFTER_ALARM] <<"\";"
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[OUT_DURING_ALARM] <<"\";" 
		<< "\""<< nb_each_labels[OUT_DURING_ALARM] <<"\";" 
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[NOT_OUT_NO_ALARM] <<"\";"
		<< "\""<< nb_each_labels[NOT_OUT_NO_ALARM] <<"\";"
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[NOT_OUT_ALARM] <<"\";"
		<< "\""<< nb_each_labels[NOT_OUT_ALARM] <<"\";"
		
		<< "\"" << std::fixed << std::setprecision(2) << percent_each_labels[INOUT_NO_ALARM] << "\";"
		<< "\""<< nb_each_labels[INOUT_NO_ALARM] <<"\";"
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[INOUT_AFTER_ALARM]  <<"\";"
		<< "\""<< nb_each_labels[INOUT_AFTER_ALARM] <<"\";"
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[INOUT_DURING_ALARM] <<"\";" 
		<< "\""<< nb_each_labels[INOUT_DURING_ALARM] <<"\";" 
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[NOT_INOUT_NO_ALARM] <<"\";"
		<< "\""<< nb_each_labels[NOT_INOUT_NO_ALARM] <<"\";"
		<< "\""<< std::fixed << std::setprecision(2) << percent_each_labels[NOT_INOUT_ALARM] <<"\";"
		<< "\""<< nb_each_labels[NOT_INOUT_ALARM] <<"\";"
	
		<< "\"" << std::fixed << std::setprecision(2) << percent_each_labels[ABANDON_IN] << "\";"
		<< "\""<< nb_each_labels[ABANDON_IN] <<"\";"	
		<< "\"" << std::fixed << std::setprecision(2) << percent_each_labels[ABANDON_OUT] << "\";"
		<< "\""<< nb_each_labels[ABANDON_OUT] <<"\";"
		<< "\"" << std::fixed << std::setprecision(2) << percent_each_labels[ABANDON_INOUT] << "\";"
		<< "\""<< nb_each_labels[ABANDON_INOUT] <<"\";"
		
		<< "\"" << std::fixed << std::setprecision(2) << percent_SHA_30_sec_in << "\";"
		<< "\""<< nb_SHA_30_sec_in <<"\";"	
		<< "\"" << std::fixed << std::setprecision(2) << percent_SHA_30_sec_out << "\";"
		<< "\""<< nb_SHA_30_sec_out <<"\";"
		<< "\"" << std::fixed << std::setprecision(2) << percent_SHA_30_sec_inout << "\";"
		<< "\""<< nb_SHA_30_sec_inout <<"\";"
		
		
		<< "\"" << std::fixed << std::setprecision(2) << percent_each_labels[IMPOSSIBLE] << "\";"
		<< "\""<< nb_each_labels[IMPOSSIBLE] << "\""
		
		<< endl;

}
