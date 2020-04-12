#pragma once
#include "Core/StructUtils.h"
#include <vector>

class Agent;

class  AgentManager {
public:
	AgentManager() = default;
	~AgentManager();

	static void Register(AgentModel& NewAgent);

	Agent* CreateNewAgent(int Job);
	
private:
	
	static std::vector<AgentModel> AgentRegistry;
};

