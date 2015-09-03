#pragma once

#include "AirbusComponent.h"

// Engine and Warning Display
class ATA31_EWD : AirbusComponent
{
public:
	ATA31_EWD(int);
	~ATA31_EWD();

	void update();
};

