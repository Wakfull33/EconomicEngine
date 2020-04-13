#pragma once
#include "Core/Signal.h"
#include <any>
#include <vector>

class Event {
public:
	Event() = default;
	Event(int Id);

	void BroadCast(std::any& Params);

private:
	int EventId;
	Signal<std::any&> EventSignal;

	
};
