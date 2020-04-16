// EconomicEngine.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "Engine/Engine.h"
#include "Simulation/Simulation.h"
#include <iostream>
#include <chrono>



int main()
{
	Engine* EconomicEngine = new Engine();
	Simulation* EconomicSimulation = EconomicEngine->CreateSimulation();
	while (EconomicSimulation->SimulationActive) {
		EconomicSimulation->ConsummeCycle();
	}
	EconomicEngine->EndSimulation(EconomicSimulation);
	delete EconomicSimulation;
	delete EconomicEngine;
	EconomicSimulation = nullptr;
	EconomicEngine = nullptr;
	return 0;
}

