#include "..\..\..\include\Simulation\Global\GameMode.h"

GameMode* GameMode::m_GameMode = nullptr;

GameMode* GameMode::Get() {
	if (m_GameMode == nullptr) {
		m_GameMode = new GameMode();
	}
	return m_GameMode;
}

void GameMode::Destroy() {
	delete m_GameMode;
}

GameMode::~GameMode() {
	delete AgentsManager;
	delete ItemsManager;
	delete TradeManager;
}
