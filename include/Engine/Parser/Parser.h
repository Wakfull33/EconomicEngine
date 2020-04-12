#pragma once

#include "Core/StructUtils.h"
#include "Simulation/Agent/AgentManager.h"
#include <iostream>


template<class T>
class Parser
{
public:

	Parser(){
	}
	~Parser(){	
	}

	static DataModel Read(std::string FilePath){
		return T::Read(FilePath);
	}

	static DataModel Write(std::string FilePath) {
		return T::Write(FilePath);
	}
	
	static void RegisterSimulationParameters(Simulation* Simulation, DataModel& Model){
		Simulation->NbrCycles = Model.NombreCycles;
		Simulation->SimulationAgentManager = new AgentManager();
		for (auto& AgentModel : Model.AgentModels){
			AgentManager::Register(AgentModel);
		}
		// ici dois faire la loop
	}

	
	
};

