#include "Tool.h"

class Hoe : public Tool
{
public:
	Hoe();
	virtual ~Hoe();
	virtual bool Use() override;

private:
	double breakChance = 0.1;
};