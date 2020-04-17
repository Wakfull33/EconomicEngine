#pragma once
#include "Core/StructUtils.h"
#include "Librairy/dsv_filter.hpp"



class CSV
{
public:
	CSV();
	~CSV();

	static bool IsFileValid(std::string FileName);

	static void Write(std::vector<CycleResult>& Results, std::string DatasPath);

	static std::string BoolToString(bool value);

	
private:

};

