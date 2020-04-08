#pragma once
#include <vector>
#include <chrono>

using Time = std::chrono::time_point<std::chrono::steady_clock>;

class Entity;

class Simulation {

public:

////////VARIABLES///////////
	
	Time Clock;
	float DeltaTime;
	
	bool SimulationActive;
	int NbrCycles;
	std::vector<Entity> Entities;

////////FONCTIONS//////////
///
	Simulation();
	Simulation(Time _Clock);
	~Simulation();
	
	void ConsummeCycle();
};

