#include <iostream>
#include <string.h>
#include <chrono>
#include "activities.hpp"

using namespace std;
using namespace std::chrono;

int main(int argc, char** argv) 
{
	if(argc != 4)
	{
		cerr << "Usage: " << argv[0] << " filename (in csv format) excel_csv_or_not (1 or 0) filename_output" << endl; 
		exit(EXIT_FAILURE);
	}

	bool excel = false;
	if( !strcmp(argv[2],"1") )
		excel = true;
		
	vector<string> headers {"unique ID", "puce ID", "activity ID",
		"abandon", "statut", "start time", "end time", "duration",
		"alarm", "SHA", "SHA during alarm", "label"};
		
	auto start = high_resolution_clock::now();
	
	Activities act(argv[1], excel);
	act.write_csv_file(argv[3], excel, headers);
	
	auto stop = high_resolution_clock::now(); 
	auto duration = duration_cast<std::chrono::minutes>(stop - start);
	auto duration_seconds = duration_cast<std::chrono::seconds>(stop - start);
	auto duration_ms = duration_cast<std::chrono::milliseconds>(stop - start);
	
	cout << "Time taken : " << endl;
	cout << duration.count() << " minutes" << endl; 
	cout << "(so : " << duration_seconds.count() << " seconds, " << duration_ms.count() << " ms)" << endl; 
	
	return 0;
}
