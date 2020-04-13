#pragma once
#include "Core/Signal.h"
#include "Core/StructUtils.h"
#include <vector>

class Event {
public:
	Event() = default;
	Event(int Id);

	bool CanHappen();
	void BroadCast();

	Signal<std::vector<AgentModel>&> AgentsSignal;
	Signal<std::vector<ItemModel>&> ItemsSignal;


private:
	
	int EventId;

	
};
