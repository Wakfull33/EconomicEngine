#include "Simulation/Items/Tools/Tool.h"

class Axe : public Tool
{
public:
	Axe();
	virtual ~Axe();
	virtual bool Use() override;

private:
	double breakChance = 0.1;
};