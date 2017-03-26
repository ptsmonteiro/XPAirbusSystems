#pragma once

#include "systems/AirbusComponent.h"

// Engine and Warning Display
class EWD : AirbusComponent
{
public:
	EWD(int);
	~EWD();

	void update();
};

