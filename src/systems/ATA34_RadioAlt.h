#pragma once

#include "AirbusComponent.h"

class ATA34_RadioAlt : public AirbusComponent
{
public:
	ATA34_RadioAlt(int);
	~ATA34_RadioAlt();

	virtual BaseMessage* update();
	
protected:

	int number;
};

