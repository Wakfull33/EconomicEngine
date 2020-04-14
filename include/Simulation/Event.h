#pragma once
#include "Core/Signal.h"
#include "Core/StructUtils.h"
#include <vector>

class GameMode;

class Event {
public:
	
	Event() = default;
	Event(EventModel& _Model);

	void BroadCast(bool IsStart);

	Signal<std::vector<AgentModel>&, bool> AgentsSignal;
	Signal<std::vector<ItemModel>&, bool> ItemsSignal;

	void EventStart();
	void EventEnd();

	bool AsBegin;
	int EventId;
	EventModel Model;

};
