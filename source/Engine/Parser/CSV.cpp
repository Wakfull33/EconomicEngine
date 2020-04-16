#include "Engine/Parser/CSV.h"
#include <fstream>


CSV::CSV()
{
}

CSV::~CSV()
{
}


bool CSV::IsFileValid(std::string FileName) {
	return false;
}

void CSV::Write(std::string DatasPath){
	// test pour voir sans library csv
	std::ofstream csv_File;
	csv_File.open(DatasPath);
	csv_File << "a,b,c,\n";
	csv_File << "c,s,v,\n";
	csv_File << "1,2,3.456\n";
	csv_File << "semi;colon";
	csv_File.close();
	

}
