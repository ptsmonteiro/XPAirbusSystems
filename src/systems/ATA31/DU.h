#pragma once

#include "systems/AirbusComponent.h"

// Display Unit
class DU : AirbusComponent
{
public:
	DU(int);
	~DU();

	void update();
};

