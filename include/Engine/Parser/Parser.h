#pragma once

#include "Core/StructUtils.h"
#include "Core/GameplayStatics.h"
#include "Simulation/Global/GameMode.h"
#include "Simulation/ObjectManager.h"
#include "Simulation/Event.h"
#include <vector>


template<class T>
class Parser
{
public:

	Parser(){
	}
	~Parser(){	
	}

	static void InitSimulationFromFile(Simulation* _Simulation, std::string DatasFilePath, std::string ParametersFilePath){
		DataModel SimulationParamtersModel = T::Read(DatasFilePath, ParametersFilePath);
		RegisterParametersFromData(_Simulation, SimulationParamtersModel);
		CreateSimulationObjects(_Simulation, SimulationParamtersModel);
	}

	static void Write(std::string FilePath) {
		//TODO Titi
	}
	
	static void RegisterParametersFromData(Simulation* _Simulation, DataModel& Model){
		GameMode* SimulationGameMode = GamePlayStatics::GetGameMode();
		_Simulation->TotalNbrCycles = Model.NombreCycles;

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

		for (int i = 0; i < Model.EventModels.size(); i++) {
			
			Event* _Event = new Event(Model.EventModels[i]);
			
			if (_Event->Model.Recurrent) {
				int NextTurnOccurence = _Event->Model.OccurenceCycle;
				while (NextTurnOccurence < _Simulation->TotalNbrCycles) {
					_Simulation->CyclesEventRegistry[NextTurnOccurence].push_back(i);
					if (_Event->Model.Temporary) {
						const int EventEnd = NextTurnOccurence + _Event->Model.EventDuration;
						if (EventEnd > _Simulation->TotalNbrCycles) {
							_Simulation->CyclesEventRegistry[_Simulation->TotalNbrCycles].push_back(i);
						}
						else {
							_Simulation->CyclesEventRegistry[EventEnd].push_back(i);
						}
					}
					NextTurnOccurence += _Event->Model.CyclesSpacing;
				}
			}
			else {
				_Simulation->CyclesEventRegistry[_Event->Model.OccurenceCycle].push_back(i);
				if (_Event->Model.Temporary) {
					const int EventEnd = _Event->Model.OccurenceCycle + _Event->Model.EventDuration;
					if (EventEnd > _Simulation->TotalNbrCycles) {
						_Simulation->CyclesEventRegistry[_Simulation->TotalNbrCycles].push_back(i);
					}
					else {
						_Simulation->CyclesEventRegistry[EventEnd].push_back(i);
					}
				}
			}

			_Event->AgentsSignal.Connect<ObjectManager<AgentModel>>(&ObjectManager<AgentModel>::UpdateObjectsFromEvent);
			_Event->ItemsSignal.Connect<ObjectManager<ItemModel>>(&ObjectManager<ItemModel>::UpdateObjectsFromEvent);
			
			_Simulation->Events.push_back(_Event);
		}	
	}
};

