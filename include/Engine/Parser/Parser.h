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
		//TODO Titi
	}
	
	static void RegisterParametersFromData(DataModel& Model){
		GameMode* SimulationGameMode = GamePlayStatics::GetGameMode();
		SimulationGameMode->NbrCycles = Model.NombreCycles;

		//TODO Titi Register Item
		
		SimulationGameMode->AgentsManager = new ObjectManager<AgentModel>;
		for (auto& _AgentModel : Model.AgentModels){
			ObjectManager<AgentModel>::Register(_AgentModel);
		}

		//
		
	}

	static void CreateSimulationObjects(Simulation* _Simulation, DataModel& Model) {
		GameMode* SimulationGameMode = GamePlayStatics::GetGameMode();
		//TODO Titi
		//
		//
		////////////////////////
		//TODO Benoit Add system with std::any and Add sytem for handling city if added

		for (auto& EventModel: Model.EventModels) {
			Event* _Event = new Event(EventModel);
			_Event->AgentsSignal.Connect<ObjectManager<AgentModel>>(&ObjectManager<AgentModel>::UpdateObjectsFromEvent);
			_Event->ItemsSignal.Connect<ObjectManager<ItemModel>>(&ObjectManager<ItemModel>::UpdateObjectsFromEvent);
			_Simulation->Events.push_back(_Event);
		}
		
	}
	
};

