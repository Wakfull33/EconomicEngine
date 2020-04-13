#pragma once
#include <vector>

class AgentModel;

class Agent{

public:

	Agent() = default;
	Agent(int _Job);
	~Agent() = default;
	
	void DoJob();
	std::pair<int, int> ItemCount(const int itemWanted, bool isTool);
	std::pair<bool, int> HasTool(const int item);
	
	int Job;
	std::vector<int> Inventory;
	
};

