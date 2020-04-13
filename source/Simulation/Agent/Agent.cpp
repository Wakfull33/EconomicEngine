#include "Simulation/Agent/Agent.h"
#include "Simulation/Global/GameMode.h"

#include <algorithm>
#include <random>

Agent::Agent(int _Job)
	: Job(_Job){
}

void Agent::DoJob() {
	AgentModel agentModel = GameMode::Get()->AgentsManager->GetObject(Job);
	JobTool jobTool = agentModel.AgentJobTool;

	int ressources = ItemCount(agentModel.AgentConsum.Item, false).first;
	std::pair<bool, int> toolCheck = HasTool(jobTool.Item);
	
	if(toolCheck.first)
	{
		if (ressources >= agentModel.AgentConsum.MaxConsum)
		{
			for (int i = 0; i < agentModel.AgentProd.MaxProd; ++i)
				Inventory.push_back(agentModel.AgentProd.Item);
		}
		else if(ressources >= agentModel.AgentConsum.MinConsum)
		{
			for (int i = 0; i < agentModel.AgentProd.MinProd; ++i)
				Inventory.push_back(agentModel.AgentProd.Item);
		}

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0, 1);
		if (dis(gen) < jobTool.BreakingChance)
			Inventory.erase(Inventory.begin() + toolCheck.second + 1);
	}
	else
	{
		Inventory.push_back(agentModel.AgentProd.Item);
	}
}

std::pair<int, int> Agent::ItemCount(const int itemWanted, bool isTool)
{
	int countRessource = 0;
	int index = -1;
	for (int i = 0; i < Inventory.size(); ++i) {
		if (Inventory.at(i) == itemWanted) {
			++countRessource;
			if (isTool)
				index = i;
		}
	}

	return { countRessource, index };
}

std::pair<bool, int> Agent::HasTool(const int item)
{
	std::pair<int, int> itemCount = ItemCount(item, true);
	return std::pair<bool, int>(itemCount.first > 0 ? true : false, itemCount.second);
}

