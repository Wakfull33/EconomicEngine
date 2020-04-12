#pragma once
#include <string>

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
};
