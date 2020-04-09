#pragma once
#include "GameObject.h"

class Entity: public GameObject{

public:

	Entity() = default;
	
	virtual ~Entity();
	
	virtual void Begin();
	
	virtual void Update(float dt);
};
