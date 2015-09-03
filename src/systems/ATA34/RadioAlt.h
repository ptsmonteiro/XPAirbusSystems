#pragma once

#include "systems/AirbusComponent.h"

class RadioAlt : public AirbusComponent
{
public:
	RadioAlt(int);
	~RadioAlt();

	void update();
	int getAltitudeFt();
	
protected:

	int number;
	int altitudeFt;
};

