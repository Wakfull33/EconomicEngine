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

	int ressources = ItemCount(agentModel.AgentConsum.Item.Get());
	int food;
	bool toolCheck = ItemCount(jobTool.Item) > 0 ? true : false;

	if (ItemCount(food) > 0)
	{
		if (toolCheck)
		{
			if (ressources >= agentModel.AgentConsum.MaxConsum)
			{
				for (int i = 0; i < agentModel.AgentProd.MaxProd; ++i)
					Inventory.push_back(agentModel.AgentProd.Item.Get());
			}
			else if (ressources >= agentModel.AgentConsum.MinConsum)
			{
				for (int i = 0; i < agentModel.AgentProd.MinProd; ++i)
					Inventory.push_back(agentModel.AgentProd.Item.Get());
			}
			else
			{
				PreviousTurnResult.AsWork = false;
			}

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> dis(0, 1);
			if (dis(gen) < jobTool.BreakingChance)
				Inventory.erase(Inventory.begin() + jobTool.Item + 1);

			Inventory[food] -= 1;
			PreviousTurnResult.AsWork = true;
		}
		else
		{
			if (ressources >= agentModel.AgentConsum.MinConsum)
			{
				Inventory[food] -= 1;
				Inventory.push_back(agentModel.AgentProd.Item.Get());
			}
			else
			{
				PreviousTurnResult.AsWork = false;
			}
		}
	}
	else
	{
		PreviousTurnResult.AsWork = false;
	}
}

void Agent::DoTrade()
{
	AgentModel agentModel = GameMode::Get()->AgentsManager->GetObject(Job);
	int itemConsum = agentModel.AgentConsum.Item.Get();
	int itemProd = agentModel.AgentProd.Item.Get();
	int itemCountNeeded = agentModel.AgentConsum.MaxConsum;
	int food;

	#pragma region Ask
	if (ItemCount(food) > 0)
	{
		if (HasTool(agentModel.AgentJobTool.Item))
		{
			if (ItemCount(itemConsum) < itemCountNeeded)
			{
				GameMode::Get()->TradeManager->RegisterAsk({
					this,
					itemConsum,
					ItemCount(itemConsum) - itemCountNeeded,
					false
				});
			}
		}
		else
		{
			GameMode::Get()->TradeManager->RegisterAsk({
				this,
				agentModel.AgentJobTool.Item,
				1,
				false
			});
		}
	}
	else
	{
		GameMode::Get()->TradeManager->RegisterAsk({
			this,
			food,
			3,
			false
		});
	}
	#pragma endregion Ask

	if(ItemCount(itemProd) > 0)
	{
		GameMode::Get()->TradeManager->RegisterBid({
			this, itemProd, ItemCount(itemProd), false
		});
	}
}

int Agent::ItemCount(const int itemWanted)
{
	return Inventory[itemWanted];
}

bool Agent::HasTool(const int tool)
{
	return ItemCount(tool) > 0 ? true : false;
}