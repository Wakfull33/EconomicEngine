#include "Engine/Engine.h"
#include "Engine/Parser.h"
#include "Simulation/Simulation.h"


Engine::Engine() {
	EngineParser = new Parser("Data.csv");
}

Engine::~Engine() {
	delete EngineParser;
	EngineParser = nullptr;
}

Simulation* Engine::CreateSimulation() {
	Simulation* EconomicSimulation = new Simulation(std::chrono::steady_clock::now());
	EngineParser->InitSimulationFromData(EconomicSimulation);
	EconomicSimulation->SimulationActive = true;
	return EconomicSimulation;
}


