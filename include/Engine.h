#pragma once

class Parser;
class Simulation;

class Engine {

public:

	Parser* EngineParser;
	
	Engine();
	~Engine();

	Simulation* CreateSimulation();
	
private:

};

