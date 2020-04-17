// EconomicEngine.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "Engine/Engine.h"
#include "Simulation/Simulation.h"
#include <iostream>
#include <chrono>
#include <sstream>


std::string format_duration(std::chrono::milliseconds ms) {
	using namespace std::chrono;
	auto secs = duration_cast<seconds>(ms);
	ms -= duration_cast<milliseconds>(secs);
	auto mins = duration_cast<minutes>(secs);
	secs -= duration_cast<seconds>(mins);
	auto hour = duration_cast<hours>(mins);
	mins -= duration_cast<minutes>(hour);

	std::stringstream ss;
	ss << hour.count() << " Hours : " << mins.count() << " Minutes : " << secs.count() << " Seconds : " << ms.count() << " Milliseconds";
	return ss.str();
}

int main()
{
	auto start = std::chrono::high_resolution_clock::now();

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
	
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::cout << "Simulation duration:    " << format_duration(duration) << std::endl;

	return 0;
}

