#include <random>

#include "Simulation/Items/Tools/Axe.h"

Axe::Axe()
{

}

Axe::~Axe()
{

}

bool Axe::Use()
{
	return ((double)rand() / (RAND_MAX)) < breakChance ? true : false;
}