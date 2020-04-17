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

std::string CSV::BoolToString(bool value)
{
	return value == true ? "True" : "False";
}


void CSV::Write(std::vector<CycleResult>& Results, std::string DatasPath) {
	std::ofstream csv_File;
	csv_File.open(DatasPath, std::ios_base::app);
	if (csv_File.is_open()) {
		csv_File << "Resultats des agents :" << std::endl;
		csv_File << "Profit :" << std::endl;
		csv_File << "Cycle, Farmer, Miner, Refiner, WoodCutter, Blacksmith" << std::endl;
		for (int i = 0; i < Results.size(); ++i) {
			csv_File << i + 1;
			int jobCount = 0;
			int lastProfit = 0;
			std::string lastJob = "";
			for (int j = 0; j < Results[i]._AgentCycleResult.size(); ++j) {
				if (lastJob == "" || lastJob == Results[i]._AgentCycleResult[j].Job)
				{
					lastJob = Results[i]._AgentCycleResult[j].Job;
					lastProfit += Results[i]._AgentCycleResult[j].Profit;
					jobCount += 1;
				}
				else
				{
					csv_File << ',' << lastProfit / jobCount;
					if (j < Results[i]._AgentCycleResult.size())
					{
						lastJob = Results[i]._AgentCycleResult[j].Job;
						lastProfit = Results[i]._AgentCycleResult[j].Profit;
						jobCount = 1;
					}
				}
				//
				//csv_File << Results[i]._AgentCycleResult[j].Job << ',' << BoolToString(Results[i]._AgentCycleResult[j].HasWork)
				//<< ',' << BoolToString(Results[i]._AgentCycleResult[j].HasBuy) << ','
				//<< BoolToString(Results[i]._AgentCycleResult[j].HasSell) << ',' << Results[i]._AgentCycleResult[j].Profit
				//<< std::endl;
			}
			csv_File << ',' << lastProfit / jobCount << std::endl;
		}
		csv_File.close();
	}
	else {
		std::cout << "file couldnt be opened" << std::endl;
	}
}