#pragma once

#include "Core/StructUtils.h"
#include "Core/GameplayStatics.h"
#include "Simulation/Global/GameMode.h"
#include "Simulation/ObjectManager.h"
#include "Simulation/Event.h"


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
		CreateSimulationObjects(_Simulation, SimulationModel);
	}

	static void Write(std::string FilePath) {
		//TODO
	}
	
	static void RegisterParametersFromData(DataModel& Model){
		GameMode* SimulationGameMode = GamePlayStatics::GetGameMode();
		SimulationGameMode->NbrCycles = Model.NombreCycles;

		//TODO Register Item
		
		SimulationGameMode->AgentsManager = new ObjectManager<AgentModel>;
		for (auto& _AgentModel : Model.AgentModels){
			ObjectManager<AgentModel>::Register(_AgentModel);
		}
		for (auto& _EventModel : Model.EventModels) {
			ObjectManager<EventModel>::Register(_EventModel);
		}

		//
		
	}

	static void CreateSimulationObjects(Simulation* _Simulation, DataModel& Model) {
		GameMode* SimulationGameMode = GamePlayStatics::GetGameMode();
		//TODO Titi
		//
		//
		////////////////////////
		for (int i = 0; i < SimulationGameMode->EventsManager->GetRegistrySize(); i++) {
			Event* _Event = new Event(i);
			
			_Simulation->Events.push_back(_Event);
		}
		
	}
	
};

