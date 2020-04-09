#pragma once
#include "GameObject.h"

class Job : public GameObject{
public:
	virtual ~Job() = default;
	
	virtual void DoJob() = 0;

	virtual void ShowJobInfo(){};
};

