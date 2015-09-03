#pragma once

#include "AirbusComponent.h"

class ATA34_RadioAlt : public AirbusComponent
{
public:
	ATA34_RadioAlt(int);
	~ATA34_RadioAlt();

	void update();
	int getAltitudeFt();
	
protected:

	int number;
	int altitudeFt;
};

