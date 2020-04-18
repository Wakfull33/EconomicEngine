#pragma once
#include "Simulation/ObjectManager.h"
#include "Simulation/TradeManager.h"
#include "Core/StructUtils.h"
#include <vector>


class GameMode {

public:

	static GameMode* Get();
	static void Destroy();
	
	unsigned int NbrCycles = 0;
	ObjectManager<AgentModel>* AgentsManager = nullptr;
	ObjectManager<ItemModel>* ItemsManager = nullptr;
	TradeManager* TradeManager = nullptr;

	
private:

	GameMode() = default;
	~GameMode();

	static GameMode* m_GameMode;
	
};