#pragma once

#include "AirbusComponent.h"

// Display Unit
class ATA31_DU : AirbusComponent
{
public:
	ATA31_DU(int);
	~ATA31_DU();

	void update();
};

