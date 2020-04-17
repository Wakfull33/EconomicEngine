#include "Simulation/Agent/Agent.h"
#include "Simulation/Global/GameMode.h"

#include <algorithm>
#include <random>

Agent::Agent(int _Job)
	: Job(_Job){
	//TODO Thomas / Allocate the size and init all the arrays value to 0;
	Inventory = std::vector<int>(GameMode::Get()->ItemsManager->GetRegistrySize(), 0);
}

void Agent::DoJob() {
	const AgentModel& agentModel = GameMode::Get()->AgentsManager->GetObject(Job);
	const JobTool& jobTool = agentModel.AgentJobTool;

	//Get ressources
	int ressources = ItemCount(agentModel.AgentConsum.Item.Get());
	bool toolCheck = HasTool(jobTool.Item);

	int food = 1;

	if (ItemCount(food) > 0)
	{
		if (toolCheck)
		{
			if (ressources >= agentModel.AgentConsum.MaxConsum)
			{
				for (int i = 0; i < agentModel.AgentProd.MaxProd; ++i) 
				{
					Inventory[agentModel.AgentProd.Item.Get()] += agentModel.AgentProd.MaxProd;
				}	
			}
			else if (ressources >= agentModel.AgentConsum.MinConsum)
			{
				for (int i = 0; i < agentModel.AgentProd.MinProd; ++i) 
				{
					Inventory[agentModel.AgentProd.Item.Get()] += agentModel.AgentProd.MinProd;
				}
			}
			else
			{
				PreviousTurnResult.AsWork = false;
				return;
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
				Inventory[agentModel.AgentProd.Item.Get()] += agentModel.AgentProd.MinProd;
			}
			else
			{
				PreviousTurnResult.AsWork = false;
			}
		}
	}
	else
	{
		//Todo Thomas / Il devrait crever plutot ou a la rigueur il doit perdre autre chose
		PreviousTurnResult.AsWork = false;
	}
}

void Agent::DoTrade()
{
	const AgentModel& agentModel = GameMode::Get()->AgentsManager->GetObject(Job);
	int itemConsum = agentModel.AgentConsum.Item.Get();
	int itemProd = agentModel.AgentProd.Item.Get();
	int itemCountNeeded = agentModel.AgentConsum.MaxConsum;
	int food = 1;

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
					itemCountNeeded - ItemCount(itemConsum),
					0,
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
				0,
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
			0,
			false
		});
	}
	#pragma endregion Ask

	if(ItemCount(itemProd) > 0)
	{
		GameMode::Get()->TradeManager->RegisterBid({
			this, itemProd, ItemCount(itemProd),0, false
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