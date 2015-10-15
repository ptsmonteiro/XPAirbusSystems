#pragma once
#include "systems/AirbusComponent.h"
class ATA22_FMGC : public AirbusComponent
{
public:
	ATA22_FMGC(int);
	~ATA22_FMGC();

	void update();
};

