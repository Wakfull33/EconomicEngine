#pragma once
#include "Core/StructUtils.h"
#include <map>
#include <vector>

class Agent;

class  AgentManager {
public:
	AgentManager() = default;
	~AgentManager();

	static void Register(AgentModel& NewAgent);

private:
	
	static std::vector<AgentModel> AgentRegistry;
	std::vector<Agent> Agents;
};

