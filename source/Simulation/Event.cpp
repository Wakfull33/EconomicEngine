#include "Simulation/Event.h"
#include "..\..\include\Simulation\Event.h"

Event::Event(int Id)
	: EventId(Id){
}

void Event::BroadCast(std::any& Params) {
	EventSignal.BroadCast(Params);
}
