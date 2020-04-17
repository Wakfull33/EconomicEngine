#include "Engine/Parser/Json.h"
#include "Core/Types.h"
#include <fstream>
#include <iostream>

Json::Json(){
}

Json::~Json(){
}

bool Json::IsFileValid(std::string FileName){
	return false;
}

DataModel Json::Read(std::string DatasPath, std::string ParametersPath){
	
	DataModel _DataModel;
	jsonObject j_Data;
	std::ifstream in(DatasPath);
	if (!in.fail()){
		in >> j_Data;
		std::cout << "File is open" << std::endl;

		//ItemsTypes
		auto ItemTypes = j_Data["ItemTypes"];
		for (int i = 0; i < ItemTypes.size(); i++) {
			ItemModel _ItemModel = { ItemTypes.at(i)["ItemName"], ItemTypes.at(i)["ItemPrice"]};
			_DataModel.ItemModels.push_back(_ItemModel);
		}
		//AgentTypes
		auto AgentTypes = j_Data["AgentTypes"];
		for (int i = 0 ; i < AgentTypes.size(); i++){
			AgentModel agentModel;
			agentModel.JobName = AgentTypes.at(i)["job"];
			agentModel.AgentProd = { ValKeeper<int>(AgentTypes.at(i)["produce"]["item"]),AgentTypes.at(i)["produce"]["max"],AgentTypes.at(i)["produce"]["min"]};
			agentModel.AgentConsum = { ValKeeper<int>(AgentTypes.at(i)["consume"]["item"]),AgentTypes.at(i)["consume"]["max"],AgentTypes.at(i)["consume"]["min"]};
			agentModel.AgentJobTool = { AgentTypes.at(i)["tool"]["item"],AgentTypes.at(i)["tool"]["breaking"]};
			agentModel.StartGold = AgentTypes.at(i)["startGold"];
			_DataModel.AgentModels.push_back(agentModel);
		}
		//Event
		auto Events = j_Data["Events"];
		std::cout << "Events size : " << Events.size() << std::endl;
		for (int i = 0; i < Events.size(); i++) {
			EventModel _EventModel;
			_EventModel.EventName = Events.at(i)["EventName"];
			_EventModel.OccurenceCycle = Events.at(i)["EventCycleOccurence"];
			_EventModel.Temporary = Events.at(i)["EventIsTemporary"];
			_EventModel.EventDuration = Events.at(i)["EventDuration"];
			_EventModel.Recurrent = Events.at(i)["EventIsRecurrent"];
			_EventModel.CyclesSpacing = Events.at(i)["EventCyclesSpacing"];
			auto AgentTypesImpacted = Events.at(i)["AgentTypesImpacted"];
			for (int j = 0; j < AgentTypesImpacted.size(); j++) {
				AgentModel _AgentModel;
				_AgentModel.JobName = AgentTypesImpacted.at(j)["JobImpacted"];
				_AgentModel.AgentProd = { ValKeeper<int>(AgentTypesImpacted.at(j)["ProductionOffset"]["item"]),AgentTypesImpacted.at(j)["ProductionOffset"]["MaxOffset"],AgentTypesImpacted.at(j)["ProductionOffset"]["MinOffset"] };
				_AgentModel.AgentConsum = { ValKeeper<int>(AgentTypesImpacted.at(j)["ConsumeOffset"]["item"]),AgentTypesImpacted.at(j)["ConsumeOffset"]["MaxOffset"],AgentTypesImpacted.at(j)["ConsumeOffset"]["MinOffset"] };
				_AgentModel.AgentJobTool = { AgentTypesImpacted.at(j)["ToolOffset"]["item"],AgentTypesImpacted.at(j)["ToolOffset"]["BreakingOffset"] };
				_AgentModel.StartGold = 0;
				_EventModel.AgentsModelImpacted.push_back(_AgentModel);
			}
			auto ItemsImpacted = Events.at(i)["ItemsImpacted"];
			for (int j = 0; j < ItemsImpacted.size(); j++) {
				ItemModel _ItemModel = { ItemsImpacted.at(j)["ItemName"], ItemsImpacted.at(j)["PriceOffset"] };
				_EventModel.ItemsModelImpacted.push_back(_ItemModel);
			}
			_DataModel.EventModels.push_back(_EventModel);
		}
	}
	in.close();
	in.open(ParametersPath);
	if (!in.fail()) {
		in >> j_Data;
		auto SimulationConfig = j_Data["SimulationConfig"];
		_DataModel.NombreCycles = SimulationConfig["NombreCycles"];
		_DataModel.DataCollected = SimulationConfig["DataCollected"];
		_DataModel.DataCollectionOccurence = SimulationConfig["DataCollectionOccurence"];
		_DataModel.OutputFile = SimulationConfig["OutputFile"];

		auto AgentsInitList = j_Data["AgentsInitList"];
		for (int i = 0; i < AgentsInitList.size(); i++) {
			_DataModel.NbrAgentsPerModels.push_back(std::make_pair(AgentsInitList.at(i)["class"], AgentsInitList.at(i)["quantity"]));
		}
	}
	
	return _DataModel;
}
