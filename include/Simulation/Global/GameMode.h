#pragma once
#include "Simulation/ObjectManager.h"
#include "Core/StructUtils.h"
#include <vector>


class GameMode {

public:

	static GameMode* Get();

	unsigned int NbrCycles = 0;
	ObjectManager<AgentModel>* AgentsManager = nullptr;
	ObjectManager<ItemModel>* ItemsManager = nullptr;

	
private:

	GameMode() = default;

	static GameMode* m_GameMode;
	
};