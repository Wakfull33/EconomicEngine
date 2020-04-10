#include <random>

#include "Simulation/Items/Tools/Hoe.h"

Hoe::Hoe()
{

}

Hoe::~Hoe()
{

}

bool Hoe::Use()
{
	return ((double)rand() / (RAND_MAX)) < breakChance ? true : false;
}