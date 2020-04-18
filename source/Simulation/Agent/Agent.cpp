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
	sellBelief = 0.0f;
	buyBelief = {0.0f,0.1f};
}

void Agent::DoLife() {

	//if (IsDead) {
	//	return;
	//}
	
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
	//Price and Gold Update
	//1-------------------------------------------
	//TODO Add greediness in price fluctuation
	//
	const int GoldIndex = GameMode::Get()->ItemsManager->GetObjectIndexByString("Gold");
	Inventory[GoldIndex] += PreviousTurnResult.Profit;
	if (PreviousTurnResult.HasBuy) {
		if (PreviousTurnResult.Profit < 0) {
			buyBelief.first -= 0.05f;
			buyBelief.second -= 0.1f;
		}
	}
	else {
		//He has no offer for his price so he raised it up to match market price
		if (NeededToBuy) {
			buyBelief.second += 0.1f;
			buyBelief.first += 0.05f;
		}
	}

	if (PreviousTurnResult.HasSell) {
		if (PreviousTurnResult.Profit > 0) {
			sellBelief += 0.05f;
		}
		else {
			sellBelief -= 0.05f;
		}
	}
	else {
		sellBelief -= 0.1f;
	}

	
	if (buyBelief.first < -0.5f) {
		buyBelief.first = -0.5f;
	}
	else if (buyBelief.first > 0.5) {
		buyBelief.first = 0.5f;
	}

	if (buyBelief.second < 0.0f) {
		buyBelief.second = 0.0f;
	}
	else if (buyBelief.second > 1.0) {
		buyBelief.second = 1.0f;
	}

	if (sellBelief < -0.5f) {
		sellBelief = -0.5f;
	}
	else if (sellBelief > 0.5) {
		sellBelief = 0.5f;
	}

	PreviousTurnResult.HasBuy = false;
	PreviousTurnResult.HasSell = false;
	PreviousTurnResult.Profit = 0;
	NeededToBuy = false;

	
	//2-------------------------------------------
	//Food Update
	//2-------------------------------------------
	//
	const int FoodIndex = GameMode::Get()->ItemsManager->GetObjectIndexByString("Food");
	Inventory[FoodIndex] += -1;
	const int NbrFood = ItemCount(FoodIndex);
	if (NbrFood < (MaxGreediness - Greediness) / 2) {
		if (NbrFood < -3) {
			IsDead = true;
		}
		NeededToBuy = true;
		const float BasePrice = GameMode::Get()->ItemsManager->GetObject(FoodIndex).Price;
		GameMode::Get()->TradeManager->RegisterAsk( {
			this,
			FoodIndex,
			BasePrice + BasePrice * buyBelief.first,
			2,
			0,
			0,
			false
		});
	}

	

	
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
			Inventory[ItemProd] += 1;
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
		const float BasePrice = GameMode::Get()->ItemsManager->GetObject(AgentJobTool.Item).Price;
		GameMode::Get()->TradeManager->RegisterAsk( {
			this,
			AgentJobTool.Item,
			BasePrice + BasePrice * buyBelief.first,
			1,
			0,
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
		const float BasePrice = GameMode::Get()->ItemsManager->GetObject(ItemConsum).Price;
		GameMode::Get()->TradeManager->RegisterAsk( {
			this,
			ItemConsum,
			BasePrice + BasePrice * buyBelief.first,
			AgentConsum.MaxConsum - ItemCount(ItemConsum),
			0,
			0,
			false
		});
	}
	if (ItemCount(ItemProd) > 0) {
		const float BasePrice = GameMode::Get()->ItemsManager->GetObject(ItemProd).Price;
		GameMode::Get()->TradeManager->RegisterBid({
			this,
			ItemProd,
			BasePrice + BasePrice * sellBelief,
			ItemCount(ItemProd),
			0,
			0,
			false
		});
	}
}

void Agent::TradeEnd(bool IsBuyer, TradeModel& Transaction) {
	const auto ItemProd = GameMode::Get()->AgentsManager->GetObject(Transaction.owner->Job).AgentProd.Item.Get();
	const ItemModel& _ItemModel = GameMode::Get()->ItemsManager->GetObject(Transaction.Item);
	if (IsBuyer) {
		PreviousTurnResult.HasBuy = true;
		PreviousTurnResult.Profit -= Transaction.Price* Transaction.TempExchanged;
	}
	else {
		PreviousTurnResult.HasSell = true;
		PreviousTurnResult.Profit += Transaction.Price* Transaction.TempExchanged;
	}
	PreviousTurnResult.Money = Transaction.owner->Inventory[1];
	PreviousTurnResult.ItemProd = Transaction.owner->Inventory[ItemProd];
}

int Agent::ItemCount(const int itemWanted) {
	return Inventory[itemWanted];
}

bool Agent::HasTool(const int tool) {
	return ItemCount(tool) > 0 ? true : false;
}