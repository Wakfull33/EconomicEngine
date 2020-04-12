#include "Engine/Parser/Json.h"
#include <fstream>

Json::Json()
{
}

Json::~Json()
{
}

bool Json::IsFileValid(std::string FileName)
{
	return false;
}

DataModel Json::Read(std::string Path)
{
	
	jsonObject j_AgentTypes;
	std::ifstream in(Path);
	DataModel model;
	if (!in.fail())
	{
		
	}
	return model;
}
