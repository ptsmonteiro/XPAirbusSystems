#pragma once

#include "AirbusComponent.h"

// Flight Warning Computer
class ATA31_FWC : AirbusComponent
{
public:
	ATA31_FWC(int);
	~ATA31_FWC();

	void update();
};

