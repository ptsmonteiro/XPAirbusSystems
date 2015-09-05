#pragma once
#include "systems\AirbusComponent.h"
#include "core\core.h"

class ElectricSource
{
public:
	ElectricSource();
	~ElectricSource();

	virtual float getSourceLoad();
};
