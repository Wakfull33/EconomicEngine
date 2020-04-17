#include "Engine/Engine.h"
#include "Simulation/Simulation.h"
#include "Core/GameplayStatics.h"
#include "Engine/Parser/Json.h"
#include "Engine/Parser/Parser.h"
#include "Engine/Parser/CSV.h"


Engine::Engine() {
}

Engine::~Engine() {
}

Simulation* Engine::CreateSimulation() {
	Simulation* EconomicSimulation = new Simulation();
	GamePlayStatics::SetSimulation(EconomicSimulation);
	Parser<Json>::InitSimulationFromFile(EconomicSimulation, "../Files/json/datas.json", "../Files/json/parameters.json");
	EconomicSimulation->SimulationActive = true;
	return EconomicSimulation;
}

void Engine::EndSimulation(Simulation* _Simulation) {
	Parser<CSV>::Write(_Simulation, _Simulation->OutputFilePath);
}


