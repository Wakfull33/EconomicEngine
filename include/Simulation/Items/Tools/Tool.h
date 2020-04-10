#include "Simulation/Items/Item.h"

class Tool : public Item
{
public:

	Tool() = default;

	virtual bool Use();
	virtual ~Tool();

private:
	double breakChance;
};