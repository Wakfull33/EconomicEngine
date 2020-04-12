#include "Core/GameplayStatics.h"
#include "Simulation/Global/GameMode.h"
#include "Simulation/Simulation.h"

Simulation* GamePlayStatics::m_Simulation = nullptr;

GameMode* GamePlayStatics::GetGameMode() {
	return GameMode::Get();
}

Simulation * GamePlayStatics::GetSimulation() {
	return m_Simulation;
}

void GamePlayStatics::SetSimulation(Simulation* _Simulation) {
	m_Simulation = _Simulation;
}


