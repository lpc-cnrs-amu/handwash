#include <iostream>
#include <string.h>
#include "activities.hpp"

using namespace std;

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
	Activities act(argv[1], excel);
	act.write_file(argv[3]);

	return 0;
}
