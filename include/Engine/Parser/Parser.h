#pragma once

#include "Core/StructUtils.h"
#include "Core/GameplayStatics.h"
#include "Simulation/Global/GameMode.h"
#include "Simulation/ObjectManager.h"
#include <iostream>


template<class T>
class Parser
{
public:

	Parser(){
	}
	~Parser(){	
	}

	static void InitSimulationFromFile(Simulation* _Simulation, std::string FilePath){
		DataModel SimulationModel = T::Read(FilePath);
		RegisterParametersFromData(SimulationModel);
		CreateSimulationAgents(_Simulation, SimulationModel);
	}

	static void Write(std::string FilePath) {
		//TODO
	}
	
	static void RegisterParametersFromData(DataModel& Model){
		GameMode* SimulationGameMode = GamePlayStatics::GetGameMode();
		SimulationGameMode->NbrCycles = Model.NombreCycles;
		SimulationGameMode->AgentsManager = new ObjectManager<AgentModel>;
		for (auto& _AgentModel : Model.AgentModels){
			ObjectManager<AgentModel>::Register(_AgentModel);
		}
		
	}

	static void CreateSimulationAgents(Simulation* _Simulation, DataModel& Model) {
		//TODO Titi
	}
	
};

