#pragma once

#include "systems/AirbusComponent.h"

// Display Management Computer
class DMC : AirbusComponent
{
public:
	DMC(int);
	~DMC();

	void update();
};

