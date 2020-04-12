#include "Engine/Engine.h"
#include "Simulation/Simulation.h"
#include "Core/GameplayStatics.h"
#include "Engine/Parser/Json.h"
#include "Engine/Parser/Parser.h"


Engine::Engine() {
}

Engine::~Engine() {
}

Simulation* Engine::CreateSimulation() {
	Simulation* EconomicSimulation = new Simulation(std::chrono::steady_clock::now());
	GamePlayStatics::SetSimulation(EconomicSimulation);
	Parser<Json>::InitSimulationFromFile(EconomicSimulation, "TODO");
	EconomicSimulation->SimulationActive = true;
	return EconomicSimulation;
}


