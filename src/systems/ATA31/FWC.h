#pragma once

#include "systems/AirbusComponent.h"

// Flight Warning Computer
class FWC : AirbusComponent
{
public:
	FWC(int);
	~FWC();

	void update();
};

