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
		
		const float ItemPrice = GameMode::Get()->ItemsManager->GetObject(ask.Item).Price;
		const float PriceMaxWanted = ItemPrice + ask.owner->buyBelief.second * ItemPrice;

		int it = 0;
		while(ask.Price <= PriceMaxWanted && !ask.Resolved)
		{
			if(it < BidsRegistry.size())
			{
				if (!BidsRegistry[it].Resolved && BidsRegistry[it].Item == ask.Item && BidsRegistry[it].Price <= ItemPrice)
				{
					if (ask.Quantity >= BidsRegistry[it].Quantity)
					{
						ask.Exchanged += BidsRegistry[it].Quantity;
						BidsRegistry[it].Exchanged += BidsRegistry[it].Quantity;

						ask.TempExchanged = BidsRegistry[it].Quantity;
						BidsRegistry[it].TempExchanged = BidsRegistry[it].Quantity;

						ask.owner->Inventory[ask.Item] += BidsRegistry[it].Quantity;
						BidsRegistry[it].owner->Inventory[ask.Item] -= BidsRegistry[it].Quantity;
						
						BidsRegistry[it].Resolved = true;

					}
					else
					{
						ask.Exchanged += ask.Quantity;
						BidsRegistry[it].Exchanged += ask.Quantity;

						ask.TempExchanged = ask.Quantity;
						BidsRegistry[it].TempExchanged = ask.Quantity;
						
						ask.owner->Inventory[ask.Item] += ask.Quantity;
						BidsRegistry[it].owner->Inventory[ask.Item] -= ask.Quantity;

						ask.Resolved = true;
						
					}
					ask.Quantity -= ask.TempExchanged;
					BidsRegistry[it].Quantity -= BidsRegistry[it].TempExchanged;
					//Trade End
					ask.owner->TradeEnd(true, ask);
					BidsRegistry[it].owner->TradeEnd(false, BidsRegistry[it]);
				}
				++it;
			}
			else
			{
				it = 0;
				ask.Price += 5;
			}
		}
	}
	AsksRegistry.clear();
	BidsRegistry.clear();
}