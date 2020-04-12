#pragma once
#include "json.hpp"
#include <string>
#include <fstream>
#include <vector>

class Simulation;
template <typename  T>
class Parser {

public:
	//Constructor and Destructor
	Parser() = default;
	Parser(std::string Path) {}
	Parser(const Parser& ConstructParser) {}
	~Parser() {}

	//Getter and Setter
	std::string GetPath() const;
	void SetPath(std::string& NewPath);
	
	//Operator
	Parser& operator=(const Parser& CopyParser);

	void InitSimulationFromData(Simulation* EconomicSimulation);
	

private:
	
	std::string FilePath;
	std::ifstream Reader;
	std::ofstream Writer;
};


/*class en template
 *get toutes les data du Json
 *trier les gold de base  --> avoir la sommes des gold
 *trier les metiers
 *trier les items
 *trier le nombres de cycles
 *trier le temps de
 *Envoyer le nombres d'agent en fonction du metier
 *Envoyer le nombres d'item
 *envoyer les gold par métiers
 *(discuter sur tous les parametres de la simulations)
 *
 *
 *
 *
 * 
 */