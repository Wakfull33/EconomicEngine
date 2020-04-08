#include "Farmer.h"
#include <iostream>

Farmer* Farmer::FarmerJob = nullptr;

Farmer::Farmer() {

}

Farmer::~Farmer() {
}

void Farmer::DoJob() {
}

void Farmer::ShowJobInfo() {
	std::cout << "Farmer" << std::endl;
}

Farmer* Farmer::Get() {
	if (FarmerJob == nullptr) {
		FarmerJob = new Farmer();
	};
	return FarmerJob;
}


