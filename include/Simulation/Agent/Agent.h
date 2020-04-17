#pragma once
#include "Core/StructUtils.h"
#include <vector>

class Agent{

public:

	Agent() = default;
	Agent(int _Job);
	~Agent() = default;
	
	void DoJob();
	void UpdatePrice();
	void DoTrade();
	void TradeEnd(bool IsBuyer, TradeModel& Transaction);
	int ItemCount(const int itemWanted);
	bool HasTool(const int tool);

	std::pair<int, int> belief;
	int sellBelief;

	bool NeededToBuy = false;
	int Job;
	AgentCycleResult PreviousTurnResult;
	std::vector<int> Inventory;
	
};

