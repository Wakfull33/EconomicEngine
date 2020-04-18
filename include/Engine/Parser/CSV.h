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
	static void WriteProfit(std::vector<CycleResult>& Results, std::string DatasPath);
	static void WriteMoney(std::vector<CycleResult>& Results, std::string DatasPath);
	static void WriteItemProd(std::vector<CycleResult>& Results, std::string DatasPath);
	static void WriteItemConsum(std::vector<CycleResult>& Results, std::string DatasPath);
	static void WriteFood(std::vector<CycleResult>& Results, std::string DatasPath);

	static std::string BoolToString(bool value);

	
private:

};

