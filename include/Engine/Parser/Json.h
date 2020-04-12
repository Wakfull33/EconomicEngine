#pragma once
#include "Core/StructUtils.h"


class Json
{
public:
	Json();
	~Json();

	static bool IsFileValid(std::string FileName);

	static DataModel Read(std::string Path);
	
private:

};

