#pragma once
#include "Core/Types.h"
#include <string>
#include <vector>

struct Production {
	ValKeeper<int> Item;
	int MaxProd;
	int MinProd;

	friend Production& operator-(Production& Object1, const Production& Object2) {
		Object1.Item.Restore();
		Object1.MaxProd -= Object2.MaxProd;
		Object1.MinProd -= Object2.MinProd;
		return Object1;
	}

	friend Production& operator+(Production& Object1, const Production& Object2) {
		Object1.Item.Set(Object2.Item.Get());
		Object1.MaxProd += Object2.MaxProd;
		Object1.MinProd += Object2.MinProd;
		return Object1;
	}
};

struct Consommation {
	
	ValKeeper<int>Item;
	int MaxConsum;
	int MinConsum;

	friend Consommation& operator-(Consommation& Object1, const Consommation& Object2) {
		Object1.Item.Restore();
		Object1.MaxConsum -= Object2.MaxConsum;
		Object1.MinConsum -= Object2.MinConsum;
		return Object1;
	}

	friend Consommation& operator+(Consommation& Object1, const Consommation& Object2) {
		Object1.Item.Set(Object2.Item.Get());
		Object1.MaxConsum += Object2.MaxConsum;
		Object1.MinConsum += Object2.MinConsum;
		return Object1;
	}
};

struct JobTool {
	int Item;
	float BreakingChance;
};

struct AgentModel {
	
	std::string JobName;
	Production AgentProd;
	Consommation AgentConsum;
	JobTool AgentJobTool;
	int StartGold;

	friend bool operator==(const AgentModel& Model1, const AgentModel& Model2){
		if (Model1.JobName == Model2.JobName) {
			return true;
		}
		return false;
	}

	friend bool operator==(const AgentModel& Model1, const std::string& Name) {
		if (Model1.JobName == Name) {
			return true;
		}
		return false;
	}

	friend bool operator!=(const AgentModel& Model1, const std::string& Name) {
		return !(Model1 == Name);
	}

	friend bool operator!=(const AgentModel& Model1, const AgentModel& Model2) {
		return !(Model1 == Model2);
	}

	friend AgentModel& operator+(AgentModel& Object1, const AgentModel& Object2) {
		
		Object1.AgentProd = Object1.AgentProd + Object2.AgentProd;
		Object1.AgentConsum = Object1.AgentConsum + Object2.AgentConsum;
		return Object1;
	}

	friend AgentModel& operator-(AgentModel& Object1, const AgentModel& Object2) {
		Object1.AgentProd = Object1.AgentProd - Object2.AgentProd;
		Object1.AgentConsum = Object1.AgentConsum - Object2.AgentConsum;
		return Object1;
	}
};



struct ItemModel {
	
	std::string ItemName;
	float Price;

	friend bool operator==(const ItemModel& Item1, const ItemModel& Item2) {
		if (Item1.ItemName == Item2.ItemName) {
			return true;
		}
		return false;
	}

	friend bool operator==(const ItemModel& Item1, const std::string& LookingName) {
		if (Item1.ItemName == LookingName) {
			return true;
		}
		return false;
	}

	friend bool operator!=(const ItemModel& Item1, const std::string& LookingName) {
		return !(Item1 == LookingName);
	}
	
	friend bool operator!=(const ItemModel& Item1, const ItemModel& Item2) {
		return !(Item1 == Item2);
	}

	friend ItemModel& operator-(ItemModel& Item1, const ItemModel& Item2) {
		Item1.Price -= Item2.Price;
		return Item1;
	}

	friend ItemModel& operator+(ItemModel& Item1, const ItemModel& Item2) {
		Item1.Price += Item2.Price;
		return Item1;
	}
};


struct EventModel {
	
	std::string EventName;
	int OccurenceCycle;
	bool Temporary;
	int EventDuration;
	bool Recurrent;
	int CyclesSpacing;
	std::vector<AgentModel> AgentsModelImpacted;
	std::vector<ItemModel> ItemsModelImpacted;

	friend bool operator==(const EventModel& Event1, const EventModel& Event2) {
		if (Event1.EventName == Event2.EventName) {
			return true;
		}
		return false;
	}

	friend bool operator!=(const EventModel& Event1, const EventModel& Event2) {
		return !(Event1 == Event2);
	}
};

	
struct DataModel {

	bool DataCollected;
	unsigned char DataCollectionOccurence;
	unsigned int NombreCycles;
	std::string OutputFile;
	std::vector<AgentModel> AgentModels;
	std::vector<ItemModel> ItemModels;
	std::vector<EventModel> EventModels;
	std::vector<std::pair<std::string, int>> NbrAgentsPerModels;

};

struct TradeModel{
	class Agent* owner;
	int Item;
	float Price;
	int Quantity;
	int Exchanged;
	int TempExchanged;
	bool Resolved;
};

struct AgentCycleResult {
	bool HasWork = false;
	bool HasBuy = false;
	bool HasSell = false;
	float Profit = 0.0f;
	int Money = 0;
	int ItemProd = 0;
	std::string Job;
};

struct ItemCycleResult {
	float PriceFluctuation;
	std::string Item;
};

struct CycleResult {
	std::vector<AgentCycleResult> _AgentCycleResult;
	std::vector<ItemCycleResult> _ItemCycleResult;
};