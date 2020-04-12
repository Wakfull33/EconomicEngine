#include "Simulation/Agent/AgentManager.h"
#include "Simulation/Agent/Agent.h"
#include <algorithm>

std::vector<AgentModel> AgentManager::AgentRegistry = std::vector<AgentModel>();

AgentManager::~AgentManager() {
	Agents.clear();
}

void AgentManager::Register(AgentModel& NewAgent) {
	auto it = std::find(AgentRegistry.begin(), AgentRegistry.end(), NewAgent);
	if (it == AgentRegistry.end()) {
		AgentRegistry.push_back(NewAgent);
	}
}

void AgentManager::CreateNewAgent(int Job){
	Agent* NewAgent = new Agent(Job);
	Agents.push_back(NewAgent);
}



//
