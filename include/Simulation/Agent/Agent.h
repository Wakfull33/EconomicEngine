#pragma once
#include "Core/StructUtils.h"
#include <vector>

class Agent{

public:

	Agent() = default;
	Agent(int _Job);
	~Agent() = default;

	void DoJob();
	
	int Job;
	std::vector<int> Inventory;
	
};

