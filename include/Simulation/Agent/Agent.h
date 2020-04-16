#pragma once
#include "Core/StructUtils.h"
#include <vector>



class Agent{

public:

	Agent() = default;
	Agent(int _Job);
	~Agent() = default;
	
	void DoJob();
	std::pair<int, int> ItemCount(const int itemWanted, bool isTool);
	std::pair<bool, int> HasTool(const int item);
	
	int Job;
	AgentCycleResult PreviousTurnResult;
	std::vector<int> Inventory;
	
};

