#pragma once

#include "Core/StructUtils.h"
#include "Core/GameplayStatics.h"
#include "Simulation/Global/GameMode.h"
#include "Simulation/ObjectManager.h"
#include "Simulation/Event.h"
#include "Simulation/Agent/Agent.h"
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

	static void Write(Simulation* _Simulation, std::string FilePath) {
		T::Write(_Simulation->SimulationsResults, FilePath);
	}
	
	static void RegisterParametersFromData(Simulation* _Simulation, DataModel& Model){
		GameMode* SimulationGameMode = GamePlayStatics::GetGameMode();
		_Simulation->TotalNbrCycles = Model.NombreCycles;
		_Simulation->CollectData = Model.DataCollected;
		_Simulation->DataCollectionOccurence = Model.DataCollectionOccurence;
		_Simulation->OutputFilePath = Model.OutputFile;
		_Simulation->CyclesEventRegistry = std::vector<std::vector<int>>(_Simulation->TotalNbrCycles, std::vector<int>());
		SimulationGameMode->ItemsManager = new ObjectManager<ItemModel>;
		for (auto& _ItemModel : Model.ItemModels) {
			SimulationGameMode->ItemsManager->Register(_ItemModel);
		}
		SimulationGameMode->AgentsManager = new ObjectManager<AgentModel>;
		for (auto& _AgentModel : Model.AgentModels){
			SimulationGameMode->AgentsManager->Register(_AgentModel);
		}
	}

	static void CreateSimulationObjects(Simulation* _Simulation, DataModel& Model) {
		GameMode* SimulationGameMode = GamePlayStatics::GetGameMode();
		
		for (auto& NbrAgent : Model.NbrAgentsPerModels) {
			auto Registry = SimulationGameMode->AgentsManager->GetRegistry();
			auto iterator = std::find(Registry.begin(), Registry.end(), NbrAgent.first);
			const int GoldIndex = SimulationGameMode->ItemsManager->GetObjectIndexByString("Gold");
			if (iterator != Registry.end()) {
				for (int i = 0; i < NbrAgent.second; i++) {
					Agent* _Agent = new Agent(iterator - Registry.begin());
					_Agent->Inventory[GoldIndex] = iterator->StartGold;
					_Simulation->Agents.push_back(_Agent);
				}
			}	
		}
		
		for (int i = 0; i < Model.EventModels.size(); i++) {
			
			Event* _Event = new Event(Model.EventModels[i]);
			
			if (_Event->Model.Recurrent) {
				int NextTurnOccurence = _Event->Model.OccurenceCycle;
				while (NextTurnOccurence < _Simulation->TotalNbrCycles) {
					_Simulation->CyclesEventRegistry[NextTurnOccurence].push_back(i);
					if (_Event->Model.Temporary) {
						const int EventEnd = NextTurnOccurence + _Event->Model.EventDuration;
						if (EventEnd > _Simulation->TotalNbrCycles - 1) {
							_Simulation->CyclesEventRegistry[_Simulation->TotalNbrCycles - 1].push_back(i);
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
					if (EventEnd > _Simulation->TotalNbrCycles - 1) {
						_Simulation->CyclesEventRegistry[_Simulation->TotalNbrCycles - 1].push_back(i);
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

		//PreAllocation of memory for cycle result
		CycleResult _CycleResult;
		const int NbrCyclesResultsSaved = _Simulation->TotalNbrCycles / _Simulation->DataCollectionOccurence;
		_CycleResult._AgentCycleResult.reserve(_Simulation->Agents.size());
		_CycleResult._ItemCycleResult.reserve(SimulationGameMode->ItemsManager->GetRegistrySize());
		_Simulation->SimulationsResults = std::vector<CycleResult>(NbrCyclesResultsSaved, _CycleResult);
	}
};

