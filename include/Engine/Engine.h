#pragma once

class Simulation;

class Engine {

public:

	
	Engine();
	~Engine();

	Simulation* CreateSimulation();

	void EndSimulation(Simulation* _Simulation);
	
private:

};

