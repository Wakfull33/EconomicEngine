#include "Simulation/Event.h"
#include "..\..\include\Simulation\Event.h"

Event::Event(int Id)
	: EventId(Id){
	//TODO get gamemode
}

bool Event::CanHappen() {
	return false;
	//TODO check it the right cycle
}

void Event::BroadCast() {
	//TODO broadcast signal with information
}

