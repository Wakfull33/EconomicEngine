#pragma once
#include "Core/StructUtils.h"
#include <vector>


class AgentManager;
class Agent;
class Event;

class Simulation {

public:

	////////VARIABLES///////////

	bool SimulationActive;
	bool CollectData;
	
	int ActualCycle = 0;
	int TotalNbrCycles;
	int DataCollectionOccurence;

	std::string OutputFilePath;
	
	std::vector<Agent*> Agents;
	std::vector<Event*> Events;
	std::vector<std::vector<int>> CyclesEventRegistry;
	std::vector<CycleResult> SimulationsResults;

	////////FONCTIONS//////////
	///
	Simulation();
	~Simulation();

	void ConsummeCycle();
	void EndSimulation();
};

