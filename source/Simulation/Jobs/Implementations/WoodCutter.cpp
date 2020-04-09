#include "Simulation/Jobs/Implementations/WoodCutter.h"
#include <iostream>

WoodCutter* WoodCutter::WoodCutterJob = nullptr;

WoodCutter::WoodCutter() {
	
}


WoodCutter::~WoodCutter() {
}

void WoodCutter::DoJob() {
}

void WoodCutter::ShowJobInfo() {
	std::cout << "WoodCutter" << std::endl;
}

WoodCutter * WoodCutter::Get() {
	if (WoodCutterJob == nullptr) {
		WoodCutterJob = new WoodCutter();
	}
	return WoodCutterJob;
}


