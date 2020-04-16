#include "Simulation/Simulation.h"
#include <iostream>
#include "Engine/Parser/Parser.h"
#include "Engine/Parser/Json.h"


Simulation::Simulation(){
}



Simulation::~Simulation() {
	Agents.clear();
	Events.clear();
	CyclesEventRegistry.clear();
}

//void Simulation::InitSimulation(){
//	DataModel Result = Parser<Json>::Read("Data.json");
//	Parser<Json>::RegisterGameModeParameters(this, Result);
//}

void Simulation::ConsummeCycle() {
	
	for (auto& Agent: Agents) {
		Agent->DoJob();
	}
	std::cout <<ActualCycle << std::endl;
	std::cout << Agents.size() << std::endl;
	if (!CyclesEventRegistry[ActualCycle].empty()) {
		for (auto& Index : CyclesEventRegistry[ActualCycle]) {
			if (!Events[Index]->AsBegin) {
				Events[Index]->EventStart();
			}
			else {
				Events[Index]->EventEnd();
			}
		}
	}
	ActualCycle++;
	if (ActualCycle >= TotalNbrCycles) {
		EndSimulation();
	}
}

void Simulation::EndSimulation(){

	SimulationActive = false;
}
