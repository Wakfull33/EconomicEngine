#pragma once
#include <vector>

class AgentManager;

class GameMode {

public:

	static GameMode* Get();

	unsigned int NbrCycles = 0;
	AgentManager* AgentsManager = nullptr;

	
private:

	GameMode() = default;

	static GameMode* m_GameMode;
	
};