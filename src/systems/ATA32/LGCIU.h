#pragma once

#include "systems/AirbusComponent.h"

// Landing Gear Control Interface Unit
class LGCIU : public AirbusComponent
{
public:
	LGCIU(int);
	~LGCIU();

	void update();

	bool isGearCompressed();

protected:
	int number;
	bool gearCompressed = true;

};

