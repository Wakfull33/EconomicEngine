#pragma once
#include "Core/StructUtils.h"
#include <vector>

class Agent{

public:

	Agent() = default;
	Agent(int _Job);
	~Agent() = default;

	

	int sellBelief;
	std::pair<int, int> buyBelief;


	bool NeededToBuy = false;
	bool IsDead = false;
	int Job;
	int Greediness;
	AgentCycleResult PreviousTurnResult;
	std::vector<int> Inventory;

	
	static int MaxGreediness;
	
	//Agent Life Cycle
	void DoLife();

	//Data Update
	void TradeEnd(bool IsBuyer, TradeModel& Transaction);

	//Inventory Utils
	int ItemCount(const int itemWanted);
	bool HasTool(const int tool);
};

