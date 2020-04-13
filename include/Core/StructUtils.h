#pragma once
#include <string>
#include <vector>
#include <any>

struct Production {
	int Item;
	int MaxProd;
	int MinProd;
};

struct Consommation {
	int Item;
	int MaxConsum;
	int MinConsum;
};

struct JobTool {
	int Item;
	float BreakingChance;
};

struct AgentModel {
	
	std::string JobName;
	Production AgentProd;
	Consommation AgentConsummation;
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
};

struct EventModel {
	
	std::string EventName;
	bool Recurrent;
	bool Temporary;
	int EventDuration;
	int OccurenceCycle;
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
	
	std::vector<AgentModel> AgentModels;
	std::vector<ItemModel> ItemModels;
	std::vector<EventModel> EventModels;
	std::vector<std::pair<std::string, int>> NbrAgentsPerModels;
	unsigned int NombreCycles;
};