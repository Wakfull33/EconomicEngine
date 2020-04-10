#pragma once

#include "Core/Signal.h"


class God : public GameObject{
public:
	
	Signal<int> Signal;
};