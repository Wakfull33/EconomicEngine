#pragma once
#include "json.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <map>

class Simulation;
template <typename  T>
class Parser {

	
public:
	//Constructor and Destructor
	Parser() = default;
	Parser<T>::Parser(std::string Path);
	Parser<T>::Parser(const Parser& ConstructParser);
	Parser<T>:~Parser();

	//Getter and Setter
	std::string ::Parser<T>::GetPath() const;
	void Parser<T> ::SetPath(std::string& NewPath);
	
	//Operator
	Parser& Parser<T>::operator=(const Parser& CopyParser);

	void Parser<T>::RegisterEntities() const;
	void Parser<T>::InitSimulationFromData(Simulation* EconomicSimulation);
	

private:
	
	std::string FilePath;
	std::ifstream Reader;
	std::ofstream Writer;
};

/*class en template
 *get toutes les data du JsOn
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