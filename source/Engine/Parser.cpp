#include "Engine/Parser.h"
#include "Simulation/Agent/Agent.h"
#include "Simulation/Simulation.h"
#include <iostream>
#include <sstream>


Parser::Parser()
	:Parser(""){
}

Parser::Parser(std::string Path)
	:FilePath(Path){
}

Parser::Parser(const Parser & ConstructParser) {
	FilePath = ConstructParser.FilePath;
}

Parser::~Parser() {
}

std::string Parser::GetPath() const{
	return FilePath;
}

void Parser::SetPath(std::string& NewPath) {
	FilePath = NewPath;
}

Parser& Parser::operator=(const Parser & CopyParser) {
	FilePath = CopyParser.FilePath;
	return *this;
}

void Parser::RegisterEntities() const{
	//std::string WoodCutterName = "Bucheron";
	//EngineFactory<Agent>::Register(WoodCutterName, &Agent::CreateAgentWithJob<WoodCutter>);
	//std::string FarmerName = "Fermier";
	//EngineFactory<Agent>::Register(FarmerName, &Agent::CreateAgentWithJob<Farmer>);
}

void Parser::InitSimulationFromData(Simulation * EconomicSimulation) {

	if (EconomicSimulation != nullptr) {
		
	}
	
	

	
}



