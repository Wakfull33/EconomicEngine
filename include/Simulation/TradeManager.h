#pragma once

#include "Core/StructUtils.h"

#include <vector>

class TradeManager {

public:
	TradeManager() = default;

	void RegisterBid(TradeModel& trade) {
		const auto it = std::find(BidsRegistry.begin(), BidsRegistry.end(), trade);
		if (it == BidsRegistry.end()) {
			BidsRegistry.push_back(trade);
		}
	}

	void RegisterAsk(TradeModel& trade) {
		const auto it = std::find(AsksRegistry.begin(), AsksRegistry.end(), trade);
		if (it == AsksRegistry.end()) {
			AsksRegistry.push_back(trade);
		}
	}
	
	TradeModel& GetBidObject(int index) {
		return BidsRegistry[index];
	}
	
	TradeModel& GetAskObject(int index) {
		return AsksRegistry[index];
	}

	int GetBidsRegistrySize() {
		return BidsRegistry.size();
	}

	int GetAsksRegistrySize() {
		return AsksRegistry.size();
	}

	std::vector<TradeModel>& GetAsksRegistry() {
		return AsksRegistry;
	}
	
	std::vector<TradeModel>& GetBidsRegistry() {
		return BidsRegistry;
	}

private:

	std::vector<TradeModel> AsksRegistry;
	std::vector<TradeModel> BidsRegistry;

};