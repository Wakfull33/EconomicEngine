#include "Simulation/Event.h"
#include "Simulation/Global/GameMode.h"
#include "Core/GameplayStatics.h"

Event::Event(EventModel& _Model)
	: Model(_Model){
}


void Event::BroadCast(bool IsStart) {
	AgentsSignal.BroadCast(Model.AgentsModelImpacted, IsStart);
	ItemsSignal.BroadCast(Model.ItemsModelImpacted, IsStart);
}

void Event::EventStart() {
	AsBegin = true;
	BroadCast(AsBegin);
}

void Event::EventEnd() {
	AsBegin = false;
	BroadCast(AsBegin);
}

