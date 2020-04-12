#pragma once
#include "Core/StructUtils.h"
#include "Librairy/json.hpp"

using jsonObject = nlohmann::json;


class Json
{
public:
	Json();
	~Json();

	static bool IsFileValid(std::string FileName);

	static DataModel Read(std::string Path);

	

	
	
private:

};

