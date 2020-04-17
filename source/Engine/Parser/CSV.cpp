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

void CSV::Write(std::vector<CycleResult>& Results, std::string DatasPath) {
	std::ofstream csv_File;
	csv_File.open(DatasPath);
	if (csv_File.is_open()){
		for (auto& _CycleResult : Results) {
			csv_File << "Resultats des agents :\n";
			csv_File << "JobName, HasWork, HasBuy, HasSell, AgentProfit\n";
			for (auto& AgentResult : _CycleResult._AgentCycleResult) {
				csv_File << AgentResult.Job;
				csv_File << AgentResult.HasWork;
				csv_File << AgentResult.HasBuy;
				csv_File << AgentResult.HasSell;
				csv_File << AgentResult.Profit;
				csv_File << "\n";
			}
			csv_File << "Resultats des items :\n";
			csv_File << "ItemName, PriceChange\n";
			for (auto& ItemResult : _CycleResult._ItemCycleResult) {
				csv_File << ItemResult.Item;
				csv_File << ItemResult.PriceFluctuation;
				csv_File << "\n";
			}
		}
		csv_File.close();
	}
	else {
		std::cout << "file couldnt be opened" << std::endl;
	}
}

