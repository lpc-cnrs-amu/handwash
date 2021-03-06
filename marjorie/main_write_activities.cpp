#include <iostream>
#include <string.h>
#include <chrono>
#include "activities.hpp"

using namespace std;
using namespace std::chrono;

int main(int argc, char** argv) 
{
	if(argc != 5)
	{
		cerr << "Usage: " << argv[0] << " filename (in csv format) excel_csv_or_not (1 or 0) filename_output csv" << endl; 
		exit(EXIT_FAILURE);
	}

	bool excel = false;
	if( !strcmp(argv[2],"1") )
		excel = true;
		
	vector<string> headers {"unique ID", "puce ID", "room ID", "activity ID",
		"abort", "statut", "start time", "end time", "duration",
		"alarm", "SHA", "SHA during alarm", "SHA within 30 sec", "label"};
		
	auto start = high_resolution_clock::now();
	
	Activities act(argv[1], excel);
	cout << "All activities OK !" << endl;
	
	if( !strcmp(argv[4],"csv") )
		act.write_csv_file(argv[3], excel, headers);
	else
		act.write_activities_in_file(argv[3]);
	
	auto stop = high_resolution_clock::now(); 
	auto duration = duration_cast<std::chrono::minutes>(stop - start);
	auto duration_seconds = duration_cast<std::chrono::seconds>(stop - start);
	auto duration_ms = duration_cast<std::chrono::milliseconds>(stop - start);
	
	cout << "Time taken : " << endl;
	cout << duration.count() << " minutes" << endl; 
	cout << "(so : " << duration_seconds.count() << " seconds, " << duration_ms.count() << " ms)" << endl; 
	
	return 0;
}
