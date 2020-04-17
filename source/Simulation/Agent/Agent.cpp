#include "Simulation/Agent/Agent.h"
#include "Simulation/Global/GameMode.h"

#include <algorithm>
#include <random>

int Agent::MaxGreediness = 10;

Agent::Agent(int _Job)
	: Job(_Job){
	Inventory = std::vector<int>(GameMode::Get()->ItemsManager->GetRegistrySize(), 0);
	PreviousTurnResult.Job = GameMode::Get()->AgentsManager->GetObject(Job).JobName;
	Greediness = rand() % MaxGreediness;//Get the agent greediness between 0.5 and 1
	//TODO Define Base BuyBelief and base SellBelief
}

void Agent::DoLife() {

	if (IsDead) {
		return;
	}
	
	const AgentModel& AgentJobModel = GameMode::Get()->AgentsManager->GetObject(Job);
	const Production& AgentProduction = AgentJobModel.AgentProd;
	const Consommation& AgentConsum = AgentJobModel.AgentConsum;
	const JobTool& AgentJobTool = AgentJobModel.AgentJobTool;
	const ItemModel& AgentItemProdModel = GameMode::Get()->ItemsManager->GetObject(AgentJobModel.AgentProd.Item.Get());

	const int ItemConsum = AgentConsum.Item.Get();
	const int ItemProd = AgentProduction.Item.Get();
	const int NbrConsumRessource = ItemCount(ItemConsum);
	const bool toolCheck = HasTool(AgentJobTool.Item);

	//1-------------------------------------------
	//Food Update
	//1-------------------------------------------
	//
	const int FoodIndex = GameMode::Get()->ItemsManager->GetObjectIndexByString("Food");
	Inventory[FoodIndex] += -1;
	const int NbrFood = ItemCount(FoodIndex);
	if (NbrFood < (MaxGreediness - Greediness) / 2) {
		if (NbrFood < -3) {
			IsDead = true;
		}
		NeededToBuy = true;
		GameMode::Get()->TradeManager->RegisterAsk( {
			this,
			FoodIndex,
			2,
			0,
			false
		});
	}

	//2-------------------------------------------
	//Price and Gold Update
	//2-------------------------------------------
	//TODO Add greediness in price fluctuation
	//
	const int GoldIndex = GameMode::Get()->ItemsManager->GetObjectIndexByString("Gold");
	Inventory[GoldIndex] += PreviousTurnResult.Profit;
	if (PreviousTurnResult.HasBuy) {
		if (PreviousTurnResult.Profit < 0) {
			buyBelief.first -= 5;
			buyBelief.second -= 10;
		}
	}
	else {
		//He has no offer for his price so he raised it up to match market price
		if (NeededToBuy) {
			buyBelief.second += 10;
			buyBelief.first += 5;
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

	buyBelief.first = std::clamp(buyBelief.first, 0, buyBelief.second);
	sellBelief = std::clamp(sellBelief, static_cast<int>(AgentItemProdModel.Price * 0.7), static_cast<int>(AgentItemProdModel.Price * 1.3));

	PreviousTurnResult.HasBuy = false;
	PreviousTurnResult.HasSell = false;
	PreviousTurnResult.Profit = 0;
	NeededToBuy = false;

	
	//3----------------------------------------
	//Job part
	//3----------------------------------------
	//
	
	if (toolCheck) {
		if (NbrConsumRessource >= AgentConsum.MaxConsum) {
			Inventory[ItemProd] += AgentProduction.MaxProd;
			Inventory[ItemConsum] -= AgentConsum.MaxConsum;
		}
		else if (NbrConsumRessource >= AgentConsum.MinConsum) {
			Inventory[ItemProd] += AgentProduction.MinProd;
			Inventory[ItemConsum] -= AgentConsum.MinConsum;
		}
		else {
			//TODO find utility for HasWork
			Inventory[ItemProd] += 1;
			PreviousTurnResult.HasWork = false;
			return;
		}

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0, 1);
		if (dis(gen) < AgentJobTool.BreakingChance) {
			Inventory[AgentJobTool.Item] += -1;
		}
		PreviousTurnResult.HasWork = true;
	}
	else {
		NeededToBuy = true;
		GameMode::Get()->TradeManager->RegisterAsk( {
			this,
			AgentJobTool.Item,
			1,
			0,
			false
		});
		if (NbrConsumRessource >= AgentConsum.MinConsum) {
			Inventory[ItemProd] += AgentProduction.MinProd;
			Inventory[ItemConsum] -= AgentConsum.MinConsum;
		}
		else {
			Inventory[ItemProd] += 1;
			PreviousTurnResult.HasWork = false;
		}
	}

	//4--------------------------------------
	//Trade Part
	//4--------------------------------------
	//
	if (ItemCount(ItemConsum) < AgentConsum.MaxConsum) {
		NeededToBuy = true;
		GameMode::Get()->TradeManager->RegisterAsk( {
			this,
			ItemConsum,
			AgentConsum.MaxConsum - ItemCount(ItemConsum),
			0,
			false
		});
	}
	if (ItemCount(ItemProd) > 0) {
		GameMode::Get()->TradeManager->RegisterBid({
			this,
			ItemProd,
			ItemCount(ItemProd),
			0,
			false
		});
	}
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


int Agent::ItemCount(const int itemWanted) {
	return Inventory[itemWanted];
}

bool Agent::HasTool(const int tool) {
	return ItemCount(tool) > 0 ? true : false;
}