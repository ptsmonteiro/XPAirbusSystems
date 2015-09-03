#pragma once

#include "AirbusComponent.h"

// Display Management Computer
class ATA31_DMC : AirbusComponent
{
public:
	ATA31_DMC(int);
	~ATA31_DMC();

	void update();
};

