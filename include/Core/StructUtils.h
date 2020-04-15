#pragma once
#include <string>
#include <vector>
#include <any>

struct Production {
	int Item;
	int MaxProd;
	int MinProd;

	friend Production& operator-(Production& Object1, const Production& Object2) {
		Object1.MaxProd -= Object2.MaxProd;
		Object1.MinProd -= Object2.MinProd;
		return Object1;
	}

	friend Production& operator+(Production& Object1, const Production& Object2) {
		Object1.MaxProd += Object2.MaxProd;
		Object1.MinProd += Object2.MinProd;
		return Object1;
	}
};

struct Consommation {
	int Item;
	int MaxConsum;
	int MinConsum;

	friend Consommation& operator-(Consommation& Object1, const Consommation& Object2) {
		Object1.MaxConsum -= Object2.MaxConsum;
		Object1.MinConsum -= Object2.MinConsum;
		return Object1;
	}

	friend Consommation& operator+(Consommation& Object1, const Consommation& Object2) {
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

	friend bool operator==(const AgentModel& Model1, const AgentModel& Model2){
		if (Model1.JobName == Model2.JobName) {
			return true;
		}
		return false;
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