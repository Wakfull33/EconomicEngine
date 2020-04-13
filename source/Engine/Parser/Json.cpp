#include "Engine/Parser/Json.h"
#include <fstream>

Json::Json(){
}

Json::~Json(){
}

bool Json::IsFileValid(std::string FileName){
	return false;
}

DataModel Json::Read(std::string Path){
	
	jsonObject j_AgentTypes;
	std::ifstream in(Path);
	DataModel dataModel;
	if (!in.fail()){
		//ItemsTypes
		//TODO Titi
		//
		//AgentTypes
		auto AgentTypes = j_AgentTypes["agentTypes"];
		for (int i = 0 ; i < AgentTypes.size(); i++){
			AgentModel agentModel;
			agentModel.JobName = AgentTypes.at(i)["job"];
			agentModel.AgentProd = {
				0,AgentTypes.at(i)["produce"]["max"],AgentTypes.at(i)["produce"]["min"]
			};
			agentModel.AgentConsummation = {
				0,AgentTypes.at(i)["consume"]["max"],AgentTypes.at(i)["consume"]["min"]
			};
			agentModel.AgentJobTool = {
				0,AgentTypes.at(i)["tool"]["breaking"]
			};
			dataModel.AgentModels.push_back(agentModel);
		}
		//Event
		//TODO Benoit
	}
	return dataModel;
}
