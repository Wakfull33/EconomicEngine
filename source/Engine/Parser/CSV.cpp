#include "Engine/Parser/CSV.h"
#include "Simulation/Global/GameMode.h"
#include "Core/StructUtils.h"

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


void CSV::Write(std::vector<CycleResult>& Results, std::string DatasPath)
{
	std::string columns = GetJobColumns();
	WriteProfit(Results, DatasPath, columns);
	WriteMoney(Results, DatasPath, columns);
	WriteItemProd(Results, DatasPath, columns);
	WriteItemConsum(Results, DatasPath, columns);
	WriteFood(Results, DatasPath, columns);
}

void CSV::WriteProfit(std::vector<CycleResult>& Results, std::string DatasPath, std::string Columns) {
	std::ofstream csv_File;
	csv_File.open(DatasPath += "profit.csv");
	if (csv_File.is_open()) {
		csv_File << "Resultats des agents :" << std::endl;
		csv_File << "Profit moyen par métier :" << std::endl;
		csv_File << Columns << std::endl;
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

void CSV::WriteMoney(std::vector<CycleResult>& Results, std::string DatasPath, std::string Columns) {
	std::ofstream csv_File;
	csv_File.open(DatasPath += "money.csv");
	if (csv_File.is_open()) {
		csv_File << "Resultats des agents :" << std::endl;
		csv_File << "Argent moyen par métier :" << std::endl;
		csv_File << Columns << std::endl;
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

void CSV::WriteItemProd(std::vector<CycleResult>& Results, std::string DatasPath, std::string Columns) {
	std::ofstream csv_File;
	csv_File.open(DatasPath += "production.csv");
	if (csv_File.is_open()) {
		csv_File << "Resultats des agents :" << std::endl;
		csv_File << "Produits moyens par métier :" << std::endl;
		csv_File << Columns << std::endl;
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

void CSV::WriteItemConsum(std::vector<CycleResult>& Results, std::string DatasPath, std::string Columns) {
	std::ofstream csv_File;
	csv_File.open(DatasPath += "consummation.csv");
	if (csv_File.is_open()) {
		csv_File << "Resultats des agents :" << std::endl;
		csv_File << "Ressources moyennes par métier :" << std::endl;
		csv_File << Columns << std::endl;
		for (int i = 0; i < Results.size(); ++i) {
			csv_File << i + 1;
			int jobCount = 0;
			int lastConsum = 0;
			std::string lastJob = "";
			for (int j = 0; j < Results[i]._AgentCycleResult.size(); ++j) {
				if (lastJob == "" || lastJob == Results[i]._AgentCycleResult[j].Job)
				{
					lastJob = Results[i]._AgentCycleResult[j].Job;
					lastConsum += Results[i]._AgentCycleResult[j].ItemConsum;
					jobCount += 1;
				}
				else
				{
					csv_File << ',' << lastConsum / jobCount;
					if (j < Results[i]._AgentCycleResult.size())
					{
						lastJob = Results[i]._AgentCycleResult[j].Job;
						lastConsum = Results[i]._AgentCycleResult[j].ItemConsum;
						jobCount = 1;
					}
				}
			}
			csv_File << ',' << lastConsum / jobCount << std::endl;
		}
		csv_File.close();
	}
	else {
		std::cout << "file couldnt be opened" << std::endl;
	}
}

void CSV::WriteFood(std::vector<CycleResult>& Results, std::string DatasPath, std::string Columns) {
	std::ofstream csv_File;
	csv_File.open(DatasPath += "food.csv");
	if (csv_File.is_open()) {
		csv_File << "Resultats des agents :" << std::endl;
		csv_File << "Nourriture moyenne par métier:" << std::endl;
		csv_File << Columns << std::endl;
		for (int i = 0; i < Results.size(); ++i) {
			csv_File << i + 1;
			int jobCount = 0;
			int lastFood = 0;
			std::string lastJob = "";
			for (int j = 0; j < Results[i]._AgentCycleResult.size(); ++j) {
				if (lastJob == "" || lastJob == Results[i]._AgentCycleResult[j].Job)
				{
					lastJob = Results[i]._AgentCycleResult[j].Job;
					lastFood += Results[i]._AgentCycleResult[j].Food;
					jobCount += 1;
				}
				else
				{
					csv_File << ',' << lastFood / jobCount;
					if (j < Results[i]._AgentCycleResult.size())
					{
						lastJob = Results[i]._AgentCycleResult[j].Job;
						lastFood = Results[i]._AgentCycleResult[j].Food;
						jobCount = 1;
					}
				}
			}
			csv_File << ',' << lastFood / jobCount << std::endl;
		}
		csv_File.close();
	}
	else {
		std::cout << "file couldnt be opened" << std::endl;
	}
}

std::string CSV::GetJobColumns()
{
	std::string output = "Cycle";

	for(int i = 0; i < GameMode::Get()->AgentsManager->GetRegistrySize(); ++i)
	{
		output += ", " + GameMode::Get()->AgentsManager->GetObject(i).JobName;
	}

	return output;
}
