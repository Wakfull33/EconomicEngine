#pragma once
#include "Core/StructUtils.h"
#include <vector>

class Agent;

class  AgentManager {
public:
	AgentManager() = default;
	~AgentManager();

	static void Register(AgentModel& NewAgent);

	void CreateNewAgent(int Job);
	
private:
	
	static std::vector<AgentModel> AgentRegistry;
	std::vector<Agent*> Agents;
};

