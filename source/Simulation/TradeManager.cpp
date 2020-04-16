#include "Simulation/TradeManager.h"
#include "Simulation/Agent/Agent.h"
#include "Simulation/Global/GameMode.h"
#include "Core/StructUtils.h"

void TradeManager::RegisterBid(TradeModel& trade) {
	BidsRegistry.push_back(trade);
}

void TradeManager::RegisterAsk(TradeModel& trade) {
	AsksRegistry.push_back(trade);
}

void TradeManager::ResolveTrades(){
	for (auto& ask : AsksRegistry)
	{
		int PriceWanted = ask.owner->belief.first;
		int ItemPrice = GameMode::Get()->ItemsManager->GetObject(ask.Item).Price;

		int it = 0;
		while(!ask.Resolved || PriceWanted < ask.owner->belief.second)
		{
			if(it < BidsRegistry.size())
			{
				if (!BidsRegistry[it].Resolved && BidsRegistry[it].Item == ask.Item && ItemPrice <= ask.owner->belief.first)
				{
					if (ask.Quantity >= BidsRegistry[it].Quantity)
					{
						ask.Quantity -= BidsRegistry[it].Quantity;
						ask.Exchanged += BidsRegistry[it].Quantity;
						ask.owner->Inventory[ask.Item] += BidsRegistry[it].Quantity;
						BidsRegistry[it].owner->Inventory[ask.Item] -= BidsRegistry[it].Quantity;
						BidsRegistry[it].Exchanged = BidsRegistry[it].Quantity;
						BidsRegistry[it].Resolved = true;
					}
					else
					{
						BidsRegistry[it].owner->Inventory[ask.Item] -= ask.Quantity;
						BidsRegistry[it].Exchanged += ask.Quantity;
						BidsRegistry[it].Quantity -= ask.Quantity;
						ask.owner->Inventory[it] += ask.Quantity;
						ask.Exchanged += ask.Quantity;
						ask.Resolved = true;
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
}