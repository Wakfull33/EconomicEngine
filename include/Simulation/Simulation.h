#pragma once
#include <vector>
#include <chrono>

using Time = std::chrono::time_point<std::chrono::steady_clock>;

class AgentManager;
class Agent;
class Event;

class Simulation {

public:

	////////VARIABLES///////////

	bool SimulationActive;
	bool CollectData;
	
	int ActualCycle;
	int TotalNbrCycles;
	int DataCollectionOccurence;

	std::string OutputFilePath;
	
	std::vector<Agent*> Agents;
	std::vector<Event*> Events;
	std::vector<std::vector<int>> CyclesEventRegistry;

	////////FONCTIONS//////////
	///
	Simulation();
	~Simulation();

	void ConsummeCycle();
	void EndSimulation();
};

