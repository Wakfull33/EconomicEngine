#include "Simulation/TradeManager.h"
#include "Simulation/Agent/Agent.h"
#include "Simulation/Global/GameMode.h"
#include "Core/StructUtils.h"

void TradeManager::RegisterBid(const TradeModel& trade) {
	BidsRegistry.push_back(trade);
}

void TradeManager::RegisterAsk(const TradeModel& trade) {
	AsksRegistry.push_back(trade);
}

void TradeManager::ResolveTrades(){
	
	for (auto& ask : AsksRegistry)
	{
		int PriceWanted = ask.owner->buyBelief.first;
		const int ItemPrice = GameMode::Get()->ItemsManager->GetObject(ask.Item).Price;

		int it = 0;
		while(PriceWanted < ask.owner->buyBelief.second && !ask.Resolved)
		{
			if(it < BidsRegistry.size())
			{
				if (!BidsRegistry[it].Resolved && BidsRegistry[it].Item == ask.Item && ItemPrice <= ask.owner->buyBelief.first)
				{
					if (ask.Quantity >= BidsRegistry[it].Quantity)
					{
						ask.Quantity -= BidsRegistry[it].Quantity;
						ask.Exchanged += BidsRegistry[it].Quantity;
						ask.owner->Inventory[ask.Item] += BidsRegistry[it].Quantity;
						BidsRegistry[it].owner->Inventory[ask.Item] -= BidsRegistry[it].Quantity;
						BidsRegistry[it].Exchanged = BidsRegistry[it].Quantity;
						BidsRegistry[it].Resolved = true;
						ask.owner->TradeEnd(true, ask);
						BidsRegistry[it].owner->TradeEnd(false, BidsRegistry[it]);
					}
					else
					{
						BidsRegistry[it].owner->Inventory[ask.Item] -= ask.Quantity;
						BidsRegistry[it].Exchanged += ask.Quantity;
						BidsRegistry[it].Quantity -= ask.Quantity;
						ask.owner->Inventory[ask.Item] += ask.Quantity;
						ask.Exchanged += ask.Quantity;
						ask.Resolved = true;
						ask.owner->TradeEnd(true, ask);
						BidsRegistry[it].owner->TradeEnd(false, BidsRegistry[it]);
					}
				}
				++it;
			}
			else
			{
				it = 0;
				PriceWanted += 10;
			}
		}
	}
	AsksRegistry.clear();
	BidsRegistry.clear();
}