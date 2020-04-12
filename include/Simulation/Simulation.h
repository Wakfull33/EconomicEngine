#pragma once
#include <vector>
#include <chrono>

using Time = std::chrono::time_point<std::chrono::steady_clock>;

class AgentManager;

class Simulation {

public:

	////////VARIABLES///////////

	Time Clock;
	float DeltaTime;

	bool SimulationActive;
	unsigned int NbrCycles;
	AgentManager* SimulationAgentManager;

	////////FONCTIONS//////////
	///
	Simulation();
	Simulation(Time _Clock);
	~Simulation();

	void InitSimulation();
	void ConsummeCycle();
	void EndSimulation();
};

