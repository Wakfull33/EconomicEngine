#pragma once

class GameMode;
class Simulation;

class GamePlayStatics {

public:
	static GameMode* GetGameMode();

	static Simulation* GetSimulation();
	static void SetSimulation(Simulation* _Simulation);

private:

	static Simulation* m_Simulation;
};