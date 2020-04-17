#include "Simulation/Agent/Agent.h"
#include "Simulation/Global/GameMode.h"

#include <algorithm>
#include <random>

Agent::Agent(int _Job)
	: Job(_Job){
	Inventory = std::vector<int>(GameMode::Get()->ItemsManager->GetRegistrySize(), 0);
	PreviousTurnResult.Job = GameMode::Get()->AgentsManager->GetObject(Job).JobName;
}


//TODO Benoit / Reset la struct de fin de cycle de l'agent en debut du prochain apres que l'agent est tout analysé de son precedent tour


void Agent::DoJob() {
	const AgentModel& agentModel = GameMode::Get()->AgentsManager->GetObject(Job);
	const JobTool& jobTool = agentModel.AgentJobTool;

	//Get ressources
	int ressources = ItemCount(agentModel.AgentConsum.Item.Get());
	bool toolCheck = HasTool(jobTool.Item);

	int food = GameMode::Get()->ItemsManager->GetObjectIndexByString("Food");;

	if (ItemCount(food) > 0)
	{
		if (toolCheck)
		{
			if (ressources >= agentModel.AgentConsum.MaxConsum)
			{
				for (int i = 0; i < agentModel.AgentProd.MaxProd; ++i) 
				{
					//TODO Thomas / Not gonna work you push back the id of the item at the end of the inventory and not the quantity at the index of the item;
					Inventory.push_back(agentModel.AgentProd.Item.Get());
				}	
			}
			else if (ressources >= agentModel.AgentConsum.MinConsum)
			{
				for (int i = 0; i < agentModel.AgentProd.MinProd; ++i) 
				{
					//TODO Thomas / Not gonna work you push back the id of the item at the end of the inventory and not the quantity at the index of the item;
					Inventory.push_back(agentModel.AgentProd.Item.Get());
				}	
			}
			else
			{
				PreviousTurnResult.AsWork = false;
			}

			//TODO Thomas / tu testes quand meme si son objet doit etre cassé meme si il a pas travaillé;
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> dis(0, 1);
			if (dis(gen) < jobTool.BreakingChance)
				Inventory.erase(Inventory.begin() + jobTool.Item + 1);

			Inventory[food] -= 1;
			//TODO Thomas / regarde 11 lignes au dessus;
			PreviousTurnResult.AsWork = true;
		}
		else
		{
			if (ressources >= agentModel.AgentConsum.MinConsum)
			{
				Inventory[food] -= 1;
				//TODO Thomas / tu lui push back son item a nouveau;
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
		//Todo Thomas / Handle Death
		PreviousTurnResult.AsWork = false;
	}
}

void Agent::DoTrade()
{
	const AgentModel& agentModel = GameMode::Get()->AgentsManager->GetObject(Job);
	int itemConsum = agentModel.AgentConsum.Item.Get();
	int itemProd = agentModel.AgentProd.Item.Get();
	int itemCountNeeded = agentModel.AgentConsum.MaxConsum;
	int food = GameMode::Get()->ItemsManager->GetObjectIndexByString("Food");

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

void Agent::TradeEnd(bool IsBuyer, TradeModel& Transaction) {
	
	const ItemModel& _ItemModel = GameMode::Get()->ItemsManager->GetObject(Transaction.Item);
	if (IsBuyer) {
		PreviousTurnResult.AsBuy = true;
		PreviousTurnResult.Profit -= (_ItemModel.Price*Transaction.Exchanged);
	}
	else {
		PreviousTurnResult.AsSell = true;
		PreviousTurnResult.Profit += (_ItemModel.Price*Transaction.Exchanged);
	}
}