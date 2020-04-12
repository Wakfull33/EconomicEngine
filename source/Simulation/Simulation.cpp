#include "Simulation/Simulation.h"
#include <iostream>
#include "Engine/Parser/Parser.h"
#include "Engine/Parser/Json.h"


Simulation::Simulation()
	: Simulation(Time()) {
}

Simulation::Simulation(Time _Clock)
	: Clock(_Clock), DeltaTime(0.0f), SimulationActive(false), NbrCycles(10)/*Entities(std::vector<Entity>())*/{
}

Simulation::~Simulation() {
	//Entities.clear();
}

void Simulation::InitSimulation(){
	DataModel Result = Parser<Json>::Read("Data.json");
	Parser<Json>::RegisterSimulationParameters(this, Result);
}

void Simulation::ConsummeCycle() {


	
	
	//const std::chrono::duration<float> Duration = std::chrono::steady_clock::now() - Clock;
	//Clock = std::chrono::steady_clock::now();
	//DeltaTime = Duration.count();
	//std::cout << "Cycle: " << NbrCycles << std::endl;
	//std::cout << "DeltaTime: " << DeltaTime << std::endl;
	//std::cout << "Frame Per Second: " << 1.0f / DeltaTime << std::endl;
	//std::cout << "Nbr of Agents: " << Entities.size() << std::endl;
	//for (auto& Entity : Entities) {
	//	//Entity.Update(DeltaTime);
	//}
	//NbrCycles--;
	//if (NbrCycles <= 0) {
	//	SimulationActive = false;
	//}
}

void Simulation::EndSimulation(){


}
