#pragma once

#include "Core/StructUtils.h"

#include <vector>

class TradeManager {

public:
	TradeManager() = default;

	void RegisterBid(const TradeModel& trade);

	void RegisterAsk(const TradeModel& trade);

	void ResolveTrades();
	
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