#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <map>

class Entity;
class Simulation;
class Parser {

public:
	//Constructor and Destructor
	Parser();
	Parser(std::string Path);
	Parser(const Parser& ConstructParser);
	~Parser();

	//Getter and Setter
	std::string GetPath() const;
	void SetPath(std::string& NewPath);
	
	//Operator
	Parser& operator=(const Parser& CopyParser);

	void RegisterEntities() const;
	void InitSimulationFromData(Simulation* EconomicSimulation);
	

private:
	
	int* s;
	std::string FilePath;
	std::ifstream Reader;
	std::ofstream Writer;
};

