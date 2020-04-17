#include "Simulation/Agent/Agent.h"
#include "Simulation/Global/GameMode.h"

#include <algorithm>
#include <random>

Agent::Agent(int _Job)
	: Job(_Job){
	Inventory = std::vector<int>(GameMode::Get()->ItemsManager->GetRegistrySize(), 0);
	PreviousTurnResult.Job = GameMode::Get()->AgentsManager->GetObject(Job).JobName;
}

void Agent::UpdatePrice() {

	int Gold = GameMode::Get()->ItemsManager->GetObjectIndexByString("Gold");
	Inventory[Gold] += PreviousTurnResult.Profit;
	
	if (PreviousTurnResult.HasBuy) {
		if (PreviousTurnResult.Profit < 0) {
			belief.first -= 5;
			belief.second -= 10;
		}
	}
	else {
		//He has no offer for his price so he raised it up to match market price
		if (NeededToBuy) {
			belief.second += 10;
			belief.first += 5;
		}

	}


	if (PreviousTurnResult.HasSell) {
		if (PreviousTurnResult.Profit > 0) {
			sellBelief += 5;
		}
		else {
			sellBelief -= 5;
		}
	}
	else {
		sellBelief -= 10;
	}

	const AgentModel& agentModel = GameMode::Get()->AgentsManager->GetObject(Job);
	const ItemModel& itemProdModel = GameMode::Get()->ItemsManager->GetObject(agentModel.AgentProd.Item.Get());

	std::clamp(belief.first, 0, belief.second);
	std::clamp(sellBelief, static_cast<int>(itemProdModel.Price * 0.7), static_cast<int>(itemProdModel.Price * 1.3));

	PreviousTurnResult.HasBuy = false;
	PreviousTurnResult.HasSell = false;
	PreviousTurnResult.Profit = 0;
	NeededToBuy = false;
}


void Agent::DoJob() {
	const AgentModel& agentModel = GameMode::Get()->AgentsManager->GetObject(Job);
	const JobTool& jobTool = agentModel.AgentJobTool;

	//Get ressources
	int ressources = ItemCount(agentModel.AgentConsum.Item.Get());
	bool toolCheck = HasTool(jobTool.Item);

	int food = GameMode::Get()->ItemsManager->GetObjectIndexByString("Food");

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
				PreviousTurnResult.HasWork = false;
				return;
			}

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> dis(0, 1);
			if (dis(gen) < jobTool.BreakingChance)
				Inventory.erase(Inventory.begin() + jobTool.Item + 1);

			Inventory[food] -= 1;
			PreviousTurnResult.HasWork = true;
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
				PreviousTurnResult.HasWork = false;
			}
		}
	}
	else
	{

		PreviousTurnResult.HasWork = false;

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
				NeededToBuy = true;
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
			NeededToBuy = true;
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
		NeededToBuy = true;
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
		PreviousTurnResult.HasBuy = true;
		PreviousTurnResult.Profit -= (_ItemModel.Price*Transaction.Exchanged);
	}
	else {
		PreviousTurnResult.HasSell = true;
		PreviousTurnResult.Profit += (_ItemModel.Price*Transaction.Exchanged);
	}
}