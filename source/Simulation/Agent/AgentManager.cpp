#include "Simulation/Agent/AgentManager.h"
#include "Simulation/Agent/Agent.h"
#include <algorithm>

std::vector<AgentModel> AgentManager::AgentRegistry = std::vector<AgentModel>();

AgentManager::~AgentManager() {
}

void AgentManager::Register(AgentModel& NewAgent) {
	auto it = std::find(AgentRegistry.begin(), AgentRegistry.end(), NewAgent);
	if (it == AgentRegistry.end()) {
		AgentRegistry.push_back(NewAgent);
	}
}

Agent* AgentManager::CreateNewAgent(int Job){
	return new Agent(Job);
}



//
