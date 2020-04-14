#include "Simulation/Simulation.h"
#include <iostream>
#include "Engine/Parser/Parser.h"
#include "Engine/Parser/Json.h"


Simulation::Simulation(){
}



Simulation::~Simulation() {
	//Entities.clear();
}

//void Simulation::InitSimulation(){
//	DataModel Result = Parser<Json>::Read("Data.json");
//	Parser<Json>::RegisterGameModeParameters(this, Result);
//}

void Simulation::ConsummeCycle() {


	if (!CyclesEventRegistry[NbrCycles].empty()) {
		for (auto& Index : CyclesEventRegistry[NbrCycles]) {
			if (!Events[Index]->AsBegin) {
				Events[Index]->EventStart();
			}
			else {
				Events[Index]->EventEnd();
			}
		}
	}
	NbrCycles++;
}

void Simulation::EndSimulation(){


}
