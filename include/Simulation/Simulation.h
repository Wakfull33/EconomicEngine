#pragma once
#include <vector>
#include <chrono>

using Time = std::chrono::time_point<std::chrono::steady_clock>;

class AgentManager;
class Agent;

class Simulation {

public:

	////////VARIABLES///////////

	Time Clock;
	float DeltaTime;

	bool SimulationActive;
	std::vector<Agent*> Agents;

	////////FONCTIONS//////////
	///
	Simulation();
	Simulation(Time _Clock);
	~Simulation();

	void ConsummeCycle();
	void EndSimulation();
};

