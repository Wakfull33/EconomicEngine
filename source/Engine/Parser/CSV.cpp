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


void CSV::Write(std::vector<CycleResult>& Results, std::string DatasPath)
{
	WriteProfit(Results, DatasPath);
	WriteMoney(Results, DatasPath);
	WriteItemProd(Results, DatasPath);
}


void CSV::WriteProfit(std::vector<CycleResult>& Results, std::string DatasPath) {
	std::ofstream csv_File;
	csv_File.open(DatasPath += "profit.csv");
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
			}
			csv_File << ',' << lastProfit / jobCount << std::endl;
		}
		csv_File.close();
	}
	else {
		std::cout << "file couldnt be opened" << std::endl;
	}
}

void CSV::WriteMoney(std::vector<CycleResult>& Results, std::string DatasPath) {
	std::ofstream csv_File;
	csv_File.open(DatasPath += "money.csv");
	if (csv_File.is_open()) {
		csv_File << "Resultats des agents :" << std::endl;
		csv_File << "Money :" << std::endl;
		csv_File << "Cycle, Farmer, Miner, Refiner, WoodCutter, Blacksmith" << std::endl;
		for (int i = 0; i < Results.size(); ++i) {
			csv_File << i + 1;
			int jobCount = 0;
			int lastMoney = 0;
			std::string lastJob = "";
			for (int j = 0; j < Results[i]._AgentCycleResult.size(); ++j) {
				if (lastJob == "" || lastJob == Results[i]._AgentCycleResult[j].Job)
				{
					lastJob = Results[i]._AgentCycleResult[j].Job;
					lastMoney += Results[i]._AgentCycleResult[j].Money;
					jobCount += 1;
				}
				else
				{
					csv_File << ',' << lastMoney / jobCount;
					if (j < Results[i]._AgentCycleResult.size())
					{
						lastJob = Results[i]._AgentCycleResult[j].Job;
						lastMoney = Results[i]._AgentCycleResult[j].Money;
						jobCount = 1;
					}
				}
			}
			csv_File << ',' << lastMoney / jobCount << std::endl;
		}
		csv_File.close();
	}
	else {
		std::cout << "file couldnt be opened" << std::endl;
	}
}

void CSV::WriteItemProd(std::vector<CycleResult>& Results, std::string DatasPath) {
	std::ofstream csv_File;
	csv_File.open(DatasPath += "production.csv");
	if (csv_File.is_open()) {
		csv_File << "Resultats des agents :" << std::endl;
		csv_File << "ItemProd :" << std::endl;
		csv_File << "Cycle, Farmer, Miner, Refiner, WoodCutter, Blacksmith" << std::endl;
		for (int i = 0; i < Results.size(); ++i) {
			csv_File << i + 1;
			int jobCount = 0;
			int lastProd = 0;
			std::string lastJob = "";
			for (int j = 0; j < Results[i]._AgentCycleResult.size(); ++j) {
				if (lastJob == "" || lastJob == Results[i]._AgentCycleResult[j].Job)
				{
					lastJob = Results[i]._AgentCycleResult[j].Job;
					lastProd += Results[i]._AgentCycleResult[j].ItemProd;
					jobCount += 1;
				}
				else
				{
					csv_File << ',' << lastProd / jobCount;
					if (j < Results[i]._AgentCycleResult.size())
					{
						lastJob = Results[i]._AgentCycleResult[j].Job;
						lastProd = Results[i]._AgentCycleResult[j].ItemProd;
						jobCount = 1;
					}
				}
			}
			csv_File << ',' << lastProd / jobCount << std::endl;
		}
		csv_File.close();
	}
	else {
		std::cout << "file couldnt be opened" << std::endl;
	}
}